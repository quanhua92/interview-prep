# LLD Anti-Patterns — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What are the core domain entities?
  - [ ] What behaviors must each entity support?
  - [ ] Are there cross-cutting concerns (notifications, billing, persistence)?
- [ ] List functional requirements (3-5 items):
  - [ ] Identify the main use cases (e.g., park vehicle, calculate fee, process payment)
  - [ ] Identify entity state transitions (e.g., order: pending -> paid -> shipped -> delivered)
  - [ ] Identify validation rules (e.g., email format, money amounts, status guards)
  - [ ] Identify cross-entity interactions (e.g., customer discount affects order total)
- [ ] List non-functional requirements:
  - [ ] Extensibility: how often will pricing rules, notification channels, or payment methods change?
  - [ ] Testability: can each component be tested in isolation?
  - [ ] Maintainability: will a single feature change require edits in multiple files?
- [ ] Identify potential anti-pattern traps in the problem:
  - [ ] Does the problem noun (e.g., "ParkingLot") tempt a God Class?
  - [ ] Are there domain rules that belong in entities, not services?
  - [ ] Are there primitives (int, String) used for domain concepts (Money, Email)?

## Phase 2: High-Level Design (3-5 min)
- [ ] Sketch the main classes and their responsibilities
- [ ] Identify the main operations and assign them to the correct owner:
  - [ ] Allocation logic -> SpotAllocator (not ParkingLot)
  - [ ] Pricing logic -> PricingEngine/Strategy (not ParkingLot)
  - [ ] Billing logic -> BillingService (not ParkingLot)
  - [ ] Notification logic -> NotificationService (not ParkingLot)
- [ ] Count verbs per class: if one class has 4+ unrelated verbs, flag as potential God Class
- [ ] Note the dependency direction between classes:
  - [ ] A depends on B: is the direction correct or is there a cycle?
  - [ ] Do any two classes import each other? Flag as Circular Dependency
- [ ] Present the design and call out anti-patterns you've deliberately avoided

## Phase 3: Core Component Design (5-8 min)
- [ ] Define value objects for domain concepts:
  - [ ] `Money(amount_minor_units, currency)` instead of `int`
  - [ ] `Email(string)` with validation in constructor instead of raw `String`
  - [ ] `UserId(uuid)` instead of raw `long` to prevent cross-type joins
  - [ ] Justify: only wrap primitives that carry invariants or identity
- [ ] Push behavior into domain entities (rich domain model):
  - [ ] `order.cancel()` enforces state machine (not OrderService.cancelOrder)
  - [ ] `order.applyDiscount(discount)` enforces non-negative total
  - [ ] `ticket.close()` prevents double-close
  - [ ] Service layer is a thin orchestrator, not the home of business rules
- [ ] Apply Strategy pattern for varying policies:
  - [ ] `PricingStrategy` interface with `StandardPricing`, `MemberPricing`, `MonthlyPricing`
  - [ ] `DiscountPolicy` interface with `TierAndLoyaltyPolicy`, `HolidayPolicy`
  - [ ] New rules are added without modifying existing classes (OCP)
- [ ] Design aggregates that encapsulate concepts:
  - [ ] Payment aggregate owns its own serialization, validation, persistence mapping
  - [ ] Adding a new field (installment_count, fraud_score) changes one place
  - [ ] Peripheral modules call `payment.to_*()` and stay agnostic
- [ ] Resolve any circular dependencies:
  - [ ] Extract shared value objects (UserId, CustomerView) as a kernel
  - [ ] Use dependency inversion (interface in the consumer module)
  - [ ] Move misplaced methods to their correct home (OrderRepository.findByUser)

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Walk through extension scenarios and show the design holds:
  - [ ] "Add a new pricing rule" -> new PricingStrategy, existing code untouched
  - [ ] "Add SMS notifications" -> new NotificationChannel, existing code untouched
  - [ ] "Add installment_count to payments" -> change Payment aggregate only
  - [ ] "Add a new order status (REFUNDED)" -> add transition method in Order entity
- [ ] Explain your anti-pattern avoidance strategy out loud:
  - [ ] Name the smell: "I'm avoiding God Class by splitting by reason-to-change"
  - [ ] Name the smell: "I'm using a rich domain model, not anemic, because..."
  - [ ] Name the smell: "I'm using Money instead of int to avoid Primitive Obsession"
  - [ ] Name the smell: "I moved calculateDiscount to Customer because Order had Feature Envy"
  - [ ] Name the smell: "I encapsulated Payment as an aggregate to prevent Shotgun Surgery"
  - [ ] Name the smell: "Order references UserId, not User, to avoid Circular Dependencies"
- [ ] Discuss trade-offs:
  - [ ] When is a DTO acceptable vs anemic? (DTO at API boundary = fine, domain entity = not fine)
  - [ ] When is a value object overkill? (no invariants, no identity = skip it)
  - [ ] When is Feature Envy acceptable? (aggregate root orchestrating children = fine)
- [ ] Address testability:
  - [ ] Each service can be mocked independently (no God Class coupling)
  - [ ] Entity invariants are tested at the unit level (order.cancel() throws if shipped)
  - [ ] Value object validation is tested once (Email constructor), not N times at call sites
- [ ] Mention CI enforcement for production:
  - [ ] madge / import-linter to fail on circular dependencies
  - [ ] Code-health KPIs: methods per class, distinct change reasons per class

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize your design in 2-3 sentences, mentioning which anti-patterns you avoided
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
