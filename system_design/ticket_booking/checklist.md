# Design a Ticket Booking System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the event scale: small venues (100-500 seats) or large stadiums (50K-100K seats)?
  - [ ] Should users be able to pick specific seats (seat map selection) or accept auto-assignment?
  - [ ] Is there a waitlist when an event is sold out? How does waitlist notification work?
- [ ] List functional requirements (3-5 items):
  - [ ] Users can browse events and view available seats (seat map)
  - [ ] Users can select seats and hold them temporarily while completing the purchase
  - [ ] Users can complete the booking with a payment
  - [ ] Handle concurrent booking attempts without double-booking seats
  - [ ] Support waitlist for sold-out events
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: seat selection must feel real-time (<200ms to see available seats)
  - [ ] High availability: system must not go down during high-demand events (flash sales)
  - [ ] Consistency: no double-booking under any circumstances (strong consistency for seat inventory)
  - [ ] Scalability: handle 100K+ concurrent users trying to book the same event
  - [ ] Fairness: prevent bots and scalpers from gaming the system
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~100K users trying to book simultaneously for a popular event
  - [ ] ~50K requests/sec at peak during on-sale
  - [ ] ~1M events/year, ~100 seats/event average
  - [ ] ~100M bookings/year

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Booking Service] -> [Inventory Service] -> [DB + Cache] -> [Payment Service] -> [Notification Service]
- [ ] Identify the main operations and their access patterns:
  - [ ] `GET /api/events/{id}/seats` — fetch available seats (read, extremely high QPS during on-sale)
  - [ ] `POST /api/hold` — hold selected seats temporarily (write, high QPS, needs locking)
  - [ ] `POST /api/bookings` — confirm booking and charge payment (write, moderate QPS)
  - [ ] `POST /api/waitlist` — join waitlist for sold-out event (write, low QPS)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read:Write ratio ~5:1 during normal times, ~1:1 during on-sale (lots of hold requests)
  - [ ] Cache seat availability in Redis for fast reads
  - [ ] Cache event metadata and seat map layout
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain inventory locking strategy:
  - [ ] Two-phase approach: HOLD then CONFIRM
  - [ ] HOLD: atomically reserve seats for N seconds (e.g., 5-10 min) using distributed lock or Redis atomic operation
  - [ ] CONFIRM: after payment success, convert hold to permanent booking
  - [ ] RELEASE: if payment fails or hold expires, seats are released back to available pool
  - [ ] Alternative: optimistic locking with version numbers on seat records
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `GET /api/events` -> `[{"id": "...", "name": "...", "date": "...", "available_seats": 42}]`
  - [ ] `GET /api/events/{id}/seats` -> `{"sections": [...], "seats": [{"id": "A1", "status": "available", "price": 50}, ...]}`
  - [ ] `POST /api/hold` -> `{"hold_id": "...", "expires_at": "...", "seats": ["A1", "A2"]}`
  - [ ] `POST /api/bookings` -> `{"booking_id": "...", "status": "confirmed"}`
  - [ ] `POST /api/waitlist` -> `{"waitlist_id": "...", "position": 42}`
- [ ] Sketch the database schema:
  - [ ] Table `events`: `id`, `name`, `venue`, `date`, `total_seats`, `status`
  - [ ] Table `seats`: `id`, `event_id (FK)`, `section`, `row`, `number`, `status (available/held/booked)`, `price`, `version`
  - [ ] Table `holds`: `id`, `user_id`, `event_id`, `seats (JSON)`, `created_at`, `expires_at`, `status (active/released/confirmed)`
  - [ ] Table `bookings`: `id`, `user_id`, `event_id`, `seats (JSON)`, `payment_id`, `total_amount`, `status`, `created_at`
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] SQL (MySQL/Postgres with row-level locking): strong consistency for seat inventory, transactions for hold+book
  - [ ] Redis for seat availability cache and hold state (fast atomic operations, TTL for expiration)
  - [ ] Use SQL as source of truth, Redis as fast cache layer
- [ ] Walk through the main booking flow end-to-end:
  - [ ] User browses events -> selects event -> views seat map (from Redis cache) -> selects seats -> POST /hold -> Inventory Service atomically marks seats as held in Redis + DB (transaction) -> returns hold_id with expiration -> user completes payment -> Payment Service charges -> on success, Booking Service converts hold to confirmed booking -> seats permanently marked as booked -> release any remaining held seats after TTL

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss idempotency and duplicate prevention:
  - [ ] Idempotency key on every booking request (client-generated UUID)
  - [ ] Check idempotency key before processing: if seen before, return previous result
  - [ ] Prevent duplicate charges and duplicate bookings
- [ ] Explain oversell prevention:
  - [ ] Use Redis atomic operations (SETNX or Lua script) for hold creation
  - [ ] Database-level constraint: unique constraint on (event_id, seat_id, status) or optimistic locking with version check
  - [ ] If Redis says available but DB says taken (race condition): retry or return error to user
  - [ ] Account for a small buffer of intentional oversell (e.g., 1-2%) with graceful compensation (upgrade seats, refund)
- [ ] Handle high-demand flash sale:
  - [ ] Queue-based approach: all requests go into a queue, processed sequentially (fair but slow UX)
  - [ ] Virtual waiting room: users enter a waiting room, admitted in batches to prevent overload
  - [ ] Pre-auth: require payment method on file before entering seat selection
  - [ ] CDN/cache the seat map and event page to absorb read traffic
- [ ] Handle seat map rendering under load:
  - [ ] Use WebSocket or SSE for real-time seat availability updates
  - [ ] Batch availability updates (not every single seat change, but aggregate every 1-2 seconds)
  - [ ] Render seat map on client side with periodic polling or push updates
  - [ ] Static assets (venue layout, seat coordinates) served from CDN
- [ ] Address payment integration and failure handling:
  - [ ] Payment timeout: if payment service doesn't respond in time, release hold
  - [ ] Payment failure: release hold, notify user, allow retry
  - [ ] Payment success but booking fails: idempotency key allows safe retry, refund if necessary
- [ ] Discuss monitoring and observability:
  - [ ] Real-time seat availability and hold count per event
  - [ ] Booking conversion rate (holds -> confirmed bookings)
  - [ ] Hold expiration rate (users who hold but don't complete purchase)
  - [ ] Queue depth and processing time during on-sale
  - [ ] Payment success/failure rate

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
