# Design a Ticket Booking System

## One-Liner
High-concurrency system for reserving, holding, and purchasing event tickets with strong inventory consistency.

## Functional Requirements
- Browse events and view available seats/sections
- Select and hold seats for a limited time window
- Complete purchase with payment
- Release held seats on timeout
- Prevent overselling and double booking

## Non-Functional Requirements
- Handle flash sale spikes (millions of users for popular events)
- Strong consistency on inventory (zero overselling)
- Low-latency seat selection and booking flow
- High availability during peak demand

## Key Scale Questions
- Millions of concurrent users for popular events
- 50,000-100,000 seats per venue
- Flash sale: 100,000 requests/sec during opening minutes
- Hold window: 5-10 minutes before auto-release
- Event duration: ticket sales open for days to weeks

## Core Components
- **Event Catalog Service**: event listings, venue layout, seat map
- **Inventory Service**: real-time seat availability, locking, release
- **Booking Service**: orchestrate hold -> pay -> confirm flow
- **Payment Service**: payment processing, refund handling
- **Hold Timer Service**: scheduled release of expired holds
- **Queue Service**: virtual waiting room for high-demand events
- **Notification Service**: booking confirmation, ticket delivery

## Key Design Decisions

### Concurrency Control for Inventory
- **Option A: Pessimistic locking (SELECT FOR UPDATE)**: Lock seat row in DB during hold. Strongly consistent, poor throughput under contention
- **Option B: Optimistic concurrency (version column)**: Read, check availability, update with version check. Higher throughput, retry on conflict, fair under load
- **Option C: Pre-allocated inventory pools**: Divide seats across server instances. No contention, but unfair distribution and complex rebalancing

### Flash Sale / High-Demand Handling
- **Option A: Virtual waiting room (queue)**: All users enter a queue, processed sequentially. Fair, manageable load, but adds latency
- **Option B: Request throttling + retry**: Accept random subset of requests, reject others with retry. Simple, but poor UX
- **Option C: Pre-sale + lottery system**: Users register interest, winners get booking window. Eliminates flash sale entirely

### Hold and Release Mechanism
- **Option A: TTL in Redis**: Set seat status with TTL, auto-expire on timeout. Simple, eventual (Redis may expire slightly late)
- **Option B: Scheduled job**: Periodic scan for expired holds and release. Exact timing, but adds DB load
- **Option C: Delay queue (Kafka delayed messages)**: Send release message with delay equal to hold window. Reliable, decoupled

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/events | List available events |
| GET | /api/events/{id}/seats | Get seat map with availability |
| POST | /api/events/{id}/hold | Hold selected seats |
| POST | /api/events/{id}/confirm | Confirm purchase (pay + finalize) |
| GET | /api/bookings/{id} | Get booking status and ticket |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| seat_id | VARCHAR | PK, composite (event_id + section + row + number) |
| event_id | BIGINT | Partition key |
| status | VARCHAR | available, held, sold |
| held_by | VARCHAR | User/session holding the seat |
| held_until | TIMESTAMP | Hold expiration time |
| version | INT | Optimistic concurrency version |
| price | DECIMAL | Seat price |

## Deep Dive Topics
- Idempotency key pattern: prevent double-booking from retries (client generates unique key per request)
- Two-phase commit: hold seats (phase 1) -> confirm payment and finalize (phase 2) -> compensate on failure
- Oversell detection: periodic reconciliation job to catch any inventory drift
- Payment hold/release: authorize payment on hold, capture on confirm, void on timeout

## Follow-Up Variations
- How would you handle seat selection for a concert with general admission (no assigned seats)?
- What happens if the payment service is down during a flash sale?
- How would you support waitlists and automatic upsell when better seats become available?
- How do you handle ticket transfers and resale?
