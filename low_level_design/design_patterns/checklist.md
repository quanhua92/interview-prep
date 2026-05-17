# Design Patterns for LLD Interviews -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

Source: [Design Patterns (CalibreOS)](https://www.calibreos.com/learn/lld-design-patterns)

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Which patterns are in scope? (usually the interviewer expects 2-3 from the core 7)
  - [ ] What is the domain? (parking lot, elevator, chess, etc.)
  - [ ] Are we optimizing for extensibility, testability, or simplicity?
- [ ] Identify the axis of change:
  - [ ] "We need multiple ways to do X" -> Strategy
  - [ ] "Create an object based on a type" -> Factory
  - [ ] "Notify multiple listeners when X happens" -> Observer
  - [ ] "There should only be one X" -> Singleton
  - [ ] "Behavior changes based on current state" -> State
  - [ ] "Wrap an object to add behavior" -> Decorator
  - [ ] "Object needs many optional parameters" -> Builder
- [ ] List functional requirements (3-5 items):
  - [ ] What behaviors must vary independently?
  - [ ] What objects need to be created dynamically?
  - [ ] What events need to be broadcast?
  - [ ] What state transitions exist?
- [ ] List non-functional considerations:
  - [ ] Extensibility: new variants without modifying existing code (OCP)
  - [ ] Testability: can we mock/swap components easily?
  - [ ] Simplicity: don't over-engineer; patterns add classes

## Phase 2: High-Level Design (3-5 min)
- [ ] Identify which patterns apply to which parts of the system
- [ ] Draw a simple class diagram showing:
  - [ ] Interfaces/abstract classes for each pattern role (Strategy, Observer, State, etc.)
  - [ ] Concrete implementations
  - [ ] Composition relationships (has-a) over inheritance (is-a)
- [ ] Note the key pattern interactions:
  - [ ] Strategy + Decorator combine naturally (e.g., PeakHourPricing wraps HourlyPricing)
  - [ ] Factory creates objects whose Strategy is injected at runtime
  - [ ] Observer + State: state changes trigger notifications
  - [ ] Singleton holds the root object (e.g., ParkingLot)
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Define the Strategy interface and concrete strategies:
  - [ ] `PricingStrategy` -> `HourlyPricing`, `FlatRatePricing`, `PeakHourPricing`
  - [ ] `calculate_fee(entry, exit, vehicle_type) -> float`
  - [ ] Swap strategies without changing the client (ParkingLot)
- [ ] Define the Factory for object creation:
  - [ ] `SpotFactory.create_spot(type) -> ParkingSpot`
  - [ ] Centralizes type-to-class mapping and validation
  - [ ] Callers depend on interface, not concrete classes
- [ ] Define the Observer for event notification:
  - [ ] `ElevatorObserver` with `on_floor_change()`, `on_doors_open()`
  - [ ] `FloorPanel` as concrete observer
  - [ ] `Elevator` maintains `_observers` list and calls them on state change
- [ ] Define the State pattern for state-dependent behavior:
  - [ ] `ElevatorState` interface with `request_move()`, `open_doors()`
  - [ ] `IdleState`, `MovingState`, `DoorsOpenState` as concrete states
  - [ ] Elevator delegates behavior to current state object
- [ ] Define the Decorator for dynamic behavior extension:
  - [ ] `WeekendDiscount` wraps `PricingStrategy` and modifies output
  - [ ] `Retry(Timeout(Client))` vs `Timeout(Retry(Client))` -- order matters
  - [ ] Use builder/pipeline when ordering is critical
- [ ] Walk through the main flow end-to-end:
  - [ ] Vehicle enters -> Factory creates correct spot type -> Strategy calculates fee -> Observer notifies panels

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss pattern pitfalls and how to avoid them:
  - [ ] Singleton overuse: prefer dependency injection; only use when domain truly has one instance
  - [ ] Factory for one concrete class: direct construction is fine when creation is obvious and local
  - [ ] Observer without unsubscribe or failure isolation: add unsubscribe, handle errors per-observer
  - [ ] State for every enum: use State when behavior differs, use transition table when only validation matters
  - [ ] Decorator chains where order silently changes behavior: encode order in a builder or pipeline
- [ ] Explain the escape hatches:
  - [ ] Singleton becomes dependency injection
  - [ ] Observer becomes a durable event bus when delivery must survive crashes
  - [ ] State becomes a simple validated transition table when behavior does not differ by state
- [ ] Discuss when NOT to use popular patterns:
  - [ ] Singleton: Config can be passed into constructors; DB pool owned by container, not fetched via `getInstance()`
  - [ ] Factory: not needed when creation is obvious and local
  - [ ] Observer: not enough when notifications must be durable, ordered, retried, or audited -> use EventStore or queue
  - [ ] Decorator: dangerous when wrappers have hidden ordering dependencies -> use builder/pipeline instead
- [ ] Connect patterns to SOLID principles:
  - [ ] Strategy follows Open/Closed Principle (new pricing without modifying ParkingLot)
  - [ ] Factory follows Dependency Inversion (clients depend on interface, not concrete class)
  - [ ] Observer follows Single Responsibility (publisher doesn't know about subscribers)
  - [ ] State follows Liskov Substitution (any state object can replace another)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the patterns used and why each was chosen
- [ ] State the trade-offs you made and why (more classes vs extensibility)
- [ ] Mention what you would improve with more time (e.g., add Builder for complex objects, Command pattern for undo)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
