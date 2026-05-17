# Design a Parking Lot System (LLD)

Source: [LLD Case Study: Parking Lot System (CalibreOS)](https://www.calibreos.com/learn/lld-parking-lot)

## One-Liner
Model a multi-floor parking lot with vehicle/spot type matching, extensible pricing, advance reservations, EV charging, and thread-safe concurrent spot allocation.

## Requirements

### Functional
- Vehicles (motorcycle, car, truck, EV) enter, get assigned a compatible spot, and leave after paying
- Multi-floor lot with different spot types: Compact, Standard, Large, EV (with charger)
- Spot-upsize policy: a car can use a Large spot if no Standard spots remain
- Pricing calculated at exit based on duration, vehicle type, time-of-day, and EV charging consumption
- Advance reservations with a hold window (spot released if driver does not arrive within 15 min)
- EV spots have chargers; charging cost billed separately from parking fee

### Non-Functional
- Concurrent access: two drivers must never be assigned the same spot (double-booking)
- Extensibility: adding a new vehicle type, pricing rule, or spot category should require adding a class, not editing existing ones (OCP)
- Single-server (in-process locking) or multi-server (optimistic DB locking) deployment

### Clarifying Questions to Ask
- Single floor or multi-floor? (determines if Floor is a first-class entity)
- Can a car park in a large spot? (spot-upsize policy affects findAvailableSpot)
- Pricing model: flat hourly, tiered, peak surcharge, or all of the above? (determines Strategy complexity)
- Reservations: advance booking with hold window? (separate lifecycle from Ticket)
- EV charging: exclusive to EVs or open to non-EVs? Separate billing? (adds EVCharger entity)
- Concurrency model: single server (threading) or distributed (DB-backed)? (changes locking strategy)
- Output: domain model only, or also API/receipts/notifications? (scopes the design)

## Key Concepts

### Domain Objects vs Service Objects
**Domain objects** (real-world things with identity and state):
- `ParkingLot` -- the physical facility (Singleton)
- `Floor` -- a level within the lot, contains spots
- `ParkingSpot` (abstract) -- subtypes: `CompactSpot`, `StandardSpot`, `LargeSpot`, `EVSpot`
- `Vehicle` (abstract) -- subtypes: `Motorcycle`, `Car`, `Truck`, `ElectricVehicle`
- `Ticket` -- proof of active parking session (entry_time, vehicle, spot)
- `Reservation` -- advance claim on a spot (separate lifecycle from Ticket)
- `Payment` -- immutable record of money collected
- `EVCharger` -- attached to EVSpot, owns charging session lifecycle independently

**Service objects** (encapsulate behavior):
- `PricingStrategy` (interface) -- takes a Ticket, returns a fee
- `SpotFinder` (interface) -- locates best available spot for a vehicle (swappable algorithm)
- `ReservationManager` -- handles reservation lifecycle and expiry
- `PaymentProcessor` -- interfaces with external payment gateway

### Why Ticket and Reservation Are Separate
- A Reservation can exist without a Ticket (driver reserved but has not arrived)
- A Ticket can exist without a Reservation (walk-in parking)
- When a reserved driver arrives, the system fulfills the Reservation and creates a new Ticket

## Decisions

### Design Patterns

| Pattern | Where | Why |
|---------|-------|-----|
| Singleton | ParkingLot | Global shared resource; all threads see same state. For multi-lot networks, use a registry/flyweight instead |
| Strategy | PricingStrategy, SpotFinder | Pricing rules and spot-selection algorithms change independently. Injectable at runtime, enables isolated unit testing |
| Decorator | PeakHourSurcharge, EVChargingAddon | Compose pricing rules without if-chains. `EVChargingAddon(PeakHourSurcharge(HourlyFlat()))` -- each component has single responsibility, new rules add new classes |
| Factory Method | SpotFactory | Returns correct ParkingSpot subtype without caller knowing which class is instantiated. Lot initialization reads config without hardcoding type checks |
| Observer | SpotAvailabilityNotifier | When a spot frees up (leave or reservation expiry), ReservationManager, mobile app, and analytics get notified without ParkingSpot holding explicit references |

### Concurrency Strategy (the question that separates mid from senior)

The core problem: two threads call `park()` simultaneously for the last available spot. Without synchronization, both read `is_available == True`, both proceed, and both park in the same spot (double-booking).

| Strategy | Granularity | Throughput | When to Use |
|----------|-------------|------------|-------------|
| Global lock on ParkingLot | Entire lot | ~100 ops/sec (serialized) | Never -- toy implementations only |
| Per-floor lock | One floor | O(floors) x 100 ops/sec | Mostly-idle lots, simple code |
| Per-spot lock (pessimistic) | One spot | Near-linear with spot count | Single-server, in-process threading (default interview answer) |
| Optimistic locking (version column) | Row-level in DB | Near-linear, retry on conflict | Multi-server deployment, DB-backed state |
| Redis SETNX (distributed) | Spot key in Redis | ~50K ops/sec | Microservice architecture, distributed parking network |

**Best interview answer:** "Per-spot locking for single-server (lock granularity matches the contention unit). For multi-server, optimistic locking with a version column and a retry loop in the service layer."

### Pricing Strategy Selection

| Strategy | Calculation | Use As |
|----------|-------------|--------|
| HourlyFlat | hours x rate_per_vehicle_type | Base layer |
| TieredHourly | first-hour flat + increments per 30 min | Base layer (urban garages) |
| PeakHourSurcharge | base_fee x multiplier if entry in peak window | Decorator wrapping any base |
| EVChargingAddon | base_fee + kWh x rate_per_kWh | Decorator wrapping any base |
| FlatRate | fixed fee regardless of duration | Base layer (airports, events) |

## Deep Dives

### The Lock Granularity Trap
Global lock: every `park()` and `leave()` serializes through one mutex. At 500 concurrent arrivals, throughput collapses. Per-spot lock: `ParkingSpot.park()` acquires its own lock, checks availability, parks if free. If spot was snatched between the outer scan and lock acquisition, returns `False` and the outer loop retries the next spot. No global serialization, no deadlock risk (single lock per spot, never hold two simultaneously).

For DB-backed production: `UPDATE spots SET vehicle_id=? WHERE spot_id=? AND vehicle_id IS NULL AND version=?` -- if `rowcount == 0`, retry.

### EV Charging Extension (Zero Changes to Existing Classes)
- `EVSpot` subclasses `ParkingSpot`, delegates to `EVCharger` entity (which owns charging session lifecycle independently, including fault/maintenance states)
- `EVChargingAddon` Decorator wraps any PricingStrategy to add kWh-based cost
- `Ticket` gains a `kwh_consumed` field populated at exit if spot was an EVSpot
- No modifications to `Car`, `HourlyFlat`, `ParkingLot`, or any other existing class

### Reservation Lifecycle
States: PENDING (created, spot held) -> CONFIRMED (payment captured) -> FULFILLED (driver arrived, converted to Ticket) | EXPIRED (driver did not arrive within hold window, spot released).

Expiry strategies:
1. **Lazy expiry:** Check `is_expired` on next `park()` or `reserve()` call. Simple, but spot stays "held" until someone triggers the check.
2. **Background job:** Cron/thread runs every 5 min, finds expired reservations, releases spots, notifies drivers. Correct for production.
3. **Redis TTL:** Automatic key expiry. Best for distributed deployments.

### Spot Allocation Policy
- Nearest-entrance: maximizes customer satisfaction, concentrates wear on close spots
- Random/load-balanced: extends physical infrastructure lifetime, lower satisfaction
- The choice should be configurable (Strategy pattern), not hardcoded

### Failure Modes
- Driver exits without payment (gate malfunction): need a reconciliation job flagging ISSUED tickets older than max stay duration
- EVCharger goes FAULT while in use: spot remains parkable, charger is a separate entity with independent state
- Reservation expiry race: hold_for_reservation and park happen simultaneously -- per-spot lock handles this

## Follow-Ups
- How would you add a motorcycle-can-park-in-standard-spot-when-compact-is-full rule? (affects `can_fit()` on StandardSpot)
- What happens when a driver follows 50,000 accounts -- wait, that is the news feed. What if the lot has 2,000+ spots under Black Friday traffic? (distributed locking with Redis SETNX)
- How would you add a mobile notification when a spot becomes available? (Observer pattern on ParkingSpot)
- How do you handle post-deletion propagation -- wait, how do you handle gate malfunction where driver leaves without paying? (reconciliation job)
- How would you design for a multi-lot network across a city? (flyweight registry instead of Singleton, centralized availability service)
- Can you extend this to support valet parking where attendants move cars between spots? (new ValetService, spot state becomes more complex with "occupied-but-relocatable")
