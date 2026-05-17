# Design a Parking Lot System (LLD) -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Single floor or multi-floor? (determines if Floor is a first-class entity)
  - [ ] What vehicle types? Can cars use large spots? (spot-upsize policy)
  - [ ] Pricing model: flat hourly, tiered, peak surcharge, or all of the above?
  - [ ] Advance reservations with hold window?
  - [ ] EV charging: exclusive to EVs? Separate billing?
  - [ ] Concurrency model: single server (threading) or distributed (DB-backed)?
  - [ ] Output: domain model only, or also API/receipts/notifications?
- [ ] List functional requirements (3-5 items):
  - [ ] Vehicles enter and get assigned a compatible spot
  - [ ] Multi-floor lot with spot types: Compact, Standard, Large, EV
  - [ ] Pricing calculated at exit (duration, vehicle type, time-of-day, EV charging)
  - [ ] Advance reservations with hold window (spot released if driver no-show)
  - [ ] EV spots with chargers; charging cost billed separately
- [ ] List non-functional requirements:
  - [ ] Thread-safe: no double-booking under concurrent park() calls
  - [ ] Extensible: new vehicle types, pricing rules, spot categories via new classes only (OCP)
  - [ ] Supports single-server (in-process) and multi-server (DB-backed) deployment

## Phase 2: High-Level Design (3-5 min)
- [ ] Identify domain objects vs service objects:
  - [ ] Domain: ParkingLot, Floor, ParkingSpot (and subtypes), Vehicle (and subtypes), Ticket, Reservation, Payment, EVCharger
  - [ ] Service: PricingStrategy, SpotFinder, ReservationManager, PaymentProcessor
- [ ] State the key distinction: "Ticket and Reservation are separate entities with separate lifecycles"
- [ ] Draw the inheritance hierarchy:
  - [ ] Vehicle -> Motorcycle, Car, Truck, ElectricVehicle
  - [ ] ParkingSpot -> CompactSpot, StandardSpot, LargeSpot, EVSpot
- [ ] Identify the main operations:
  - [ ] `park(vehicle)` -- find spot, atomically assign, create Ticket
  - [ ] `leave(ticket_id)` -- stamp exit, free spot, calculate fee
  - [ ] `reserve(vehicle, floor_pref)` -- hold spot, return Reservation
  - [ ] `get_availability()` -- show counts per floor per spot type
- [ ] Present the design and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain concurrency strategy and justify:
  - [ ] Per-spot lock (pessimistic) for single-server: `threading.Lock()` on each ParkingSpot
  - [ ] Optimistic locking (version column) for multi-server: `UPDATE ... WHERE version=?`
  - [ ] Global lock is wrong (serialized throughput), per-floor is acceptable but suboptimal
- [ ] Explain design patterns with WHY, not just WHAT:
  - [ ] Singleton on ParkingLot: global shared state (note: use registry for multi-lot)
  - [ ] Strategy on PricingStrategy: pricing rules change independently, injectable for testing
  - [ ] Decorator on PeakHourSurcharge/EVChargingAddon: compose pricing without if-chains
  - [ ] Factory on SpotFactory: create subtypes without hardcoded type checks
  - [ ] Observer on spot availability: decouple notification from ParkingSpot
- [ ] Walk through the main flows:
  - [ ] Walk-in park: find available spots -> try spot.park(vehicle) -> retry on False -> create Ticket
  - [ ] Reserved park: lookup Reservation -> spot.park_reserved(vehicle, reservation) -> create Ticket
  - [ ] Leave: stamp exit -> spot.leave() -> pricing.calculate_fee(ticket) -> return fee
  - [ ] Reserve: find available spot -> spot.hold_for_reservation(reservation) -> return Reservation
- [ ] Sketch the pricing decorator chain: `EVChargingAddon(PeakHourSurcharge(HourlyFlat()))`

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Walk through the concurrency scenario in detail:
  - [ ] "Two threads call park() for the last spot simultaneously"
  - [ ] Explain per-spot lock: only one thread wins CAS, other retries next spot
  - [ ] Explain optimistic locking for DB: version column + conditional UPDATE
- [ ] Discuss extension scenarios:
  - [ ] Add EV charging: EVSpot subclass + EVCharger entity + EVChargingAddon Decorator. Zero changes to existing classes
  - [ ] Add new pricing rule: new Decorator class wrapping any base strategy
  - [ ] Add new vehicle type: new Vehicle subclass with required_spot property
- [ ] Address reservation expiry:
  - [ ] Lazy expiry (check on next operation)
  - [ ] Background job (cron/thread every 5 min) -- correct for production
  - [ ] Redis TTL -- best for distributed
- [ ] Discuss failure modes:
  - [ ] Driver exits without payment -> reconciliation job for stale ISSUED tickets
  - [ ] EVCharger FAULT -> charger is separate entity, spot remains parkable
  - [ ] Reservation expiry race -> per-spot lock handles this
- [ ] Discuss spot allocation policy as a business decision:
  - [ ] Nearest-entrance vs random/load-balanced (configurable via Strategy)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made:
  - [ ] Per-spot lock: max concurrency but requires retry loop
  - [ ] Decorator chain for pricing: extensible but adds indirection
  - [ ] Reservation as separate entity from Ticket: clean lifecycle but more classes
- [ ] Mention what you would improve with more time:
  - [ ] Distributed locking with Redis SETNX for multi-server
  - [ ] SpotFinder as Strategy with min-heap for nearest-entrance optimization
  - [ ] Reconciliation job for stale tickets
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
