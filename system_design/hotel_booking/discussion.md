# Design a Hotel Booking System

Source: [Hotel Booking (CalibreOS)](https://www.calibreos.com/learn/hld-hotel-booking)

## One-Liner
Design a date-range inventory reservation system that handles fan-out writes (one booking = N row updates), configurable overbooking buffers, and high-concurrency peak loads for the "last room" scenario.

## Functional Requirements
- Search hotels by location, dates, guest count, amenities, and price range
- Check real-time room availability for a date range (exact -- no false positives)
- Temporary hold on rooms during payment (Redis TTL-based, ~10 min)
- Confirm booking after successful payment with idempotent writes and audit trail
- Cancel bookings and process refunds per policy; restore inventory
- Hotel partner API to manage room counts, pricing, and availability blocks

## Non-Functional Requirements
- Search latency: p99 < 300ms; booking latency: p99 < 2s end-to-end
- Search availability: 99.9% (stale data tolerable during degraded mode)
- Booking path: 99.99% (must not lose confirmed reservations)
- Zero oversell guarantee: never exceed max_bookable_rooms on any date
- Scale: 1.5M room-nights/day avg, 10x peak during holidays, 28M listings
- Durability: confirmed bookings replicated across 3 AZs

## Key Scale Questions
- 28M properties, ~84M (room_type, date) pairs per day, ~30B inventory rows for 365-day window
- Average 17 room-nights/sec; a 3-night stay writes 3 rows atomically (~51 row updates/sec avg)
- Peak: 50-100x average load concentrated on popular hotels for specific dates
- Search QPS: ~520/sec avg, ~5,000 QPS during holiday spikes
- Inventory read:write ratio ~1,000:1 (justifies read-optimized search + write-optimized booking split)
- Storage: ~3TB raw inventory data; ~20-30TB with replication and indexes

## Core Components
- **Search Service**: Elasticsearch-powered geo-search with amenity/price filters; serves stale-but-fast results
- **Availability Service**: reads authoritative inventory from relational DB; returns real-time room counts
- **Booking Service**: orchestrates hold -> payment -> confirm -> release flow with ACID guarantees
- **Inventory Service**: manages per-night inventory rows; handles fan-out decrements atomically
- **Pricing Service**: separate bounded context for date/channel/demand-based pricing (not embedded in inventory)
- **Payment Service**: Stripe integration with idempotency keys and webhook-based confirmation
- **Hold Cache (Redis)**: temporary room holds with TTL; atomic DECRBY for thundering herd prevention
- **Sync Pipeline (Kafka -> ES)**: eventual consistency bridge from inventory DB to Elasticsearch

## Key Design Decisions

### Inventory Data Model: Per-Night Rows vs Booking Overlaps
- **Per-night rows (correct)**: one row per (hotel_id, room_type_id, date) with pre-computed `available_rooms`. Availability check: `SELECT MIN(available_rooms) WHERE date IN (...)` -- O(N) where N = nights, always a small constant
- **Booking overlaps (wrong at scale)**: compute availability by counting overlapping bookings -- full scan per check, degrades with booking history growth
- Tradeoff: per-night model requires fan-out writes (1 booking = N row updates) but reads are constant-time

### Reservation Strategy: Optimistic Locking + Redis Hold
- **Pessimistic locking (SELECT FOR UPDATE)**: never appropriate -- checkout window (~10s) is too long for row locks; cascades into connection pool exhaustion
- **Optimistic locking (CAS on version)**: good for low-to-medium contention; version check on UPDATE, losers get instant failure and retry
- **Redis hold + DB CAS (production standard)**: soft reservation in Redis with TTL during payment; only confirmed winners hit the DB. Separates speculative holds from committed writes

### Search vs Booking Data Model Split
- **Elasticsearch for search**: optimized for geo-queries, filters, full-text; refresh interval ~1s; cannot participate in ACID transactions
- **Relational DB for booking**: authoritative source of truth; transactional consistency for inventory decrements
- **Accepted tradeoff**: search results may show stale availability (false positives tolerated; false negatives are revenue loss). Final availability check always reads from DB

### Overbooking Buffer
- Hotels legally oversell based on historical no-show rates (2-5% for leisure travel)
- Inventory table stores `total_rooms`, `available_rooms`, and `max_bookable_rooms` separately
- `max_bookable = total_rooms + floor(total_rooms * overbooking_pct)` -- configurable per property
- Platform enforces a maximum overbooking percentage (e.g., 10%)

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/hotels/search?location=&check_in=&check_out=&guests= | Search hotels with filters (reads from Elasticsearch) |
| GET | /api/hotels/{id}/availability?check_in=&check_out= | Check real-time room availability (reads from DB) |
| POST | /api/bookings/hold | Create temporary hold on rooms (writes to Redis) |
| POST | /api/bookings/{id}/confirm | Confirm booking after payment (ACID write to DB) |
| POST | /api/bookings/{id}/cancel | Cancel booking, restore inventory, process refund |
| GET | /api/bookings/{id} | Get booking details and status |

## Database Schema
| Table | Column | Type | Notes |
|-------|--------|------|-------|
| room_types | room_type_id | UUID | PK |
| room_types | hotel_id | UUID | FK to hotels |
| room_types | name | TEXT | "King Deluxe", "Double Standard" |
| room_types | total_rooms | INT | Physical room count |
| room_types | amenities | JSONB | {"wifi": true, "balcony": false} |
| inventory | hotel_id + room_type_id + date | COMPOSITE PK | Per-night availability row |
| inventory | available_rooms | INT | Current bookable count |
| inventory | max_bookable | INT | total_rooms + overbooking buffer |
| inventory | version | BIGINT | Optimistic locking counter |
| bookings | booking_id | UUID | PK |
| bookings | hotel_id / room_type_id / user_id | UUID | Foreign keys |
| bookings | check_in / check_out | DATE | Date range (check_out is exclusive) |
| bookings | status | TEXT | HELD / CONFIRMED / CANCELLED |
| bookings | idempotency_key | TEXT | UNIQUE; prevents double-booking |
| bookings | payment_ref | TEXT | Stripe PaymentIntent ID |

## Deep Dive Topics
- **Thundering herd (last-room problem)**: 10K users booking 1 remaining room. Redis atomic DECRBY resolves in-memory; only 1 winner reaches DB. Fallback: request queue serialization per hotel+date
- **Fan-out write atomicity**: N-night booking must update exactly N inventory rows. `rowsAffected == nights_count` check triggers rollback on partial failure
- **Hot shard concentration**: 80% of holiday bookings hit same 50 hotels. Detect via monitoring; move hot properties to dedicated shards; application-level rate limiting per hotel
- **Payment-DB inconsistency**: payment succeeds but DB decrement fails. Idempotent retry via webhook; compensation job detects orphaned PaymentIntents and issues refund
- **Redis hold expiry during payment**: pre-check TTL before submitting to payment gateway; fail early if TTL < 60s
- **Event sourcing for inventory ledger**: every inventory change as immutable event; balances derived by replay; full audit trail for chargebacks (E6+ scope)
- **Multi-channel rate management**: same room has different prices per OTA; pricing is a separate service with its own bounded context

## Follow-Up Variations
- How would you handle multi-room bookings (e.g., a family booking 3 rooms of different types in one transaction)?
- What changes if we add real-time dynamic pricing that adjusts room rates every minute based on demand?
- How would you design the system for a hotel chain with 10K properties vs a global OTA with 28M listings?
- How do you handle a bulk inventory import from a hotel that updates 365 days of availability in one request?
- What happens when a payment gateway is down for 30 minutes during peak booking season?
