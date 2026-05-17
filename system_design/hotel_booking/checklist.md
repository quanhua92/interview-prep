# Design a Hotel Booking System -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the scale target? (10K hotels vs 28M listings like Booking.com)
  - [ ] Do hotels have multiple room types? (almost always yes -- inventory is keyed by hotel_id + room_type_id + date)
  - [ ] What is the cancellation policy? (free cancellation, non-refundable, partial refund)
  - [ ] Is overbooking in scope? (most production systems support configurable overbooking per property)
  - [ ] What channels are in scope? (direct website only, or multi-OTA with rate parity?)
  - [ ] What is the consistency requirement for search? (eventual consistency in search is fine; booking path must be exact)
  - [ ] What payment models are needed? (pay now, pay at property, partial deposit)
- [ ] List functional requirements (3-5 items):
  - [ ] Search hotels by location, dates, guests, filters
  - [ ] Check real-time room availability for a date range
  - [ ] Temporary hold on rooms during payment
  - [ ] Confirm booking after payment; cancel and refund
  - [ ] Hotel partner API to manage inventory and pricing
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Search latency: p99 < 300ms
  - [ ] Booking latency: p99 < 2s end-to-end
  - [ ] Search availability: 99.9% (stale data ok)
  - [ ] Booking path: 99.99% (no lost reservations)
  - [ ] Zero oversell: never exceed max_bookable_rooms
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~28M listings, ~84M (room_type, date) pairs per day
  - [ ] ~1.5M room-nights/day avg (~17/sec), 10x peak on holidays
  - [ ] ~520 search QPS avg, ~5K QPS peak
  - [ ] Inventory read:write ratio ~1,000:1
  - [ ] ~30B inventory rows for 365-day window (~3TB raw, ~20-30TB with replication)

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Search Service (ES)] / [Booking Service -> Inventory DB + Redis Hold]
- [ ] Identify the main operations and their access patterns:
  - [ ] `GET /api/hotels/search` -- search hotels (read, high QPS, from Elasticsearch)
  - [ ] `GET /api/hotels/{id}/availability` -- check real-time availability (read, moderate QPS, from DB)
  - [ ] `POST /api/bookings/hold` -- create temporary hold (write to Redis, moderate QPS)
  - [ ] `POST /api/bookings/{id}/confirm` -- confirm after payment (ACID write to DB, lower QPS)
  - [ ] `POST /api/bookings/{id}/cancel` -- cancel and refund (write to DB + payment gateway)
- [ ] Note the search-vs-booking data model split:
  - [ ] Elasticsearch for search (geo-queries, filters, full-text; stale but fast)
  - [ ] Relational DB for booking (transactional consistency; authoritative availability)
  - [ ] Kafka sync pipeline bridges the two (eventual consistency, ~30-60s lag)
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain inventory data model choice and justify:
  - [ ] Per-night rows: one row per (hotel_id, room_type_id, date) with pre-computed available_rooms
  - [ ] Availability check: SELECT MIN(available_rooms) across all nights -- O(N), always small
  - [ ] Tradeoff: fan-out writes (1 booking = N row updates), but reads are constant-time
  - [ ] Why NOT booking overlaps: requires full scan of overlapping bookings, degrades at scale
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `GET /api/hotels/search?location=...&check_in=...&check_out=...` -> list of hotels with prices
  - [ ] `GET /api/hotels/{id}/availability?check_in=...&check_out=...` -> room types with available counts
  - [ ] `POST /api/bookings/hold` -> `{"hold_id": "...", "expires_at": "..."}`
  - [ ] `POST /api/bookings/{id}/confirm` -> `{"booking_id": "...", "status": "CONFIRMED"}`
  - [ ] `POST /api/bookings/{id}/cancel` -> `{"booking_id": "...", "status": "CANCELLED", "refund_amount": ...}`
- [ ] Sketch the database schema:
  - [ ] Table `room_types`: `room_type_id`, `hotel_id`, `name`, `total_rooms`, `amenities`, `max_guests`
  - [ ] Table `inventory`: `hotel_id` + `room_type_id` + `date` (composite PK), `available_rooms`, `max_bookable`, `version`
  - [ ] Table `bookings`: `booking_id`, `hotel_id`, `room_type_id`, `user_id`, `check_in`, `check_out`, `status`, `idempotency_key`, `payment_ref`
  - [ ] Shard inventory by hotel_id -- all date rows for a hotel on the same shard
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] Inventory: relational DB (PostgreSQL) for ACID guarantees on fan-out decrements
  - [ ] Search: Elasticsearch for geo-search, filters, faceted aggregation
  - [ ] Holds: Redis for fast atomic operations with TTL
- [ ] Walk through the main flow end-to-end:
  - [ ] Search: user searches -> Search Service queries ES -> returns hotels with approximate availability
  - [ ] Hold: user selects room -> Booking Service checks DB availability -> creates Redis hold (10 min TTL)
  - [ ] Payment: user pays -> Payment Service processes via Stripe -> webhook confirms
  - [ ] Confirm: Booking Service decrements inventory (fan-out UPDATE with version check) + inserts booking row in one ACID transaction
  - [ ] If payment fails or hold expires: Redis key auto-expires; no DB write needed

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss locking strategy for the reservation write:
  - [ ] Pessimistic (SELECT FOR UPDATE): never appropriate -- checkout window too long, cascades into connection exhaustion
  - [ ] Optimistic (version CAS): good for moderate contention; instant failure, retry with backoff
  - [ ] Redis DECRBY + DB CAS (production standard): Redis gates DB access; only winners hit DB at 100K ops/sec
  - [ ] Request queue serialization: extreme peak events; serial processing per hotel+date; adds latency but zero contention
- [ ] Explain the thundering herd / last-room problem:
  - [ ] 10K users book 1 remaining room; Redis atomic DECRBY resolves in memory; 1 winner reaches DB
  - [ ] Overbooking buffer reduces contention window (200 rooms with 5% buffer -> 210 max bookable)
  - [ ] Application-level rate limiting per hotel as circuit breaker
- [ ] Explain fan-out write atomicity:
  - [ ] N-night booking updates exactly N inventory rows; check rowsAffected == nights_count
  - [ ] Partial booking is worse than no booking; rollback and retry on mismatch
  - [ ] Hot shard concentration on popular hotels: monitoring, dedicated shards, rate limiting
- [ ] Address failure modes:
  - [ ] Payment succeeds but DB decrement fails: idempotent retry via webhook; compensation job refunds orphaned payments
  - [ ] Redis hold expires during payment: pre-check TTL > 60s before submitting to gateway
  - [ ] Elasticsearch stale availability: acceptable false positives; fast-path Redis filter for fully-booked hotels
  - [ ] Hot shard: detect via monitoring, move hot properties, app-level rate limiting per hotel
- [ ] Discuss the overbooking model:
  - [ ] max_bookable = total_rooms + floor(total_rooms * overbooking_pct), configurable per property
  - [ ] Platform enforces maximum (e.g., 10%); validate against historical no-show rates
  - [ ] Alert when bookings exceed physical capacity by > 3 std devs from no-show rate

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
