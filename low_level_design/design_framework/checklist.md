# LLD Interview Framework — Working Checklist

Source: [LLD Framework (CalibreOS)](https://www.calibreos.com/learn/lld-framework)

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Clarify Scope (3-5 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What actors use the system?
  - [ ] What are the core use cases?
  - [ ] Any constraints (concurrency, scale)?
  - [ ] What is the archetype? (resource allocation, workflow, domain-rich model, concurrency primitive)
- [ ] Define explicit boundaries:
  - [ ] List in-scope items
  - [ ] List out-of-scope items with reasons
  - [ ] State assumptions (e.g., single facility, no reservations, hourly pricing)
- [ ] Get alignment from the interviewer before proceeding

## Phase 2: Extract Entities (5 min)
- [ ] Read the requirements and identify nouns as candidate classes
- [ ] Identify verbs as candidate methods
- [ ] Filter weak candidates:
  - [ ] If a class has no lifecycle, no invariants, and no behavior, make it a value object or enum
  - [ ] Keep entities that own state plus behavior
- [ ] Explain rejected classes and why they are not core domain objects
- [ ] For Parking Lot example: ParkingLot, Floor, ParkingSpot, Vehicle, Ticket, PricingStrategy
- [ ] Write the final entity list on the board

## Phase 3: Design Class Structure (10-15 min)
- [ ] Define classes, their attributes, and relationships:
  - [ ] Use inheritance for is-a (CompactSpot is-a ParkingSpot)
  - [ ] Use composition for has-a (ParkingLot has Floors)
  - [ ] Use "uses-a" for services
- [ ] Define interfaces at extension points:
  - [ ] Interfaces belong where requirements vary (pricing, matching, payment, notification)
  - [ ] Concrete classes are fine where the domain is stable
- [ ] Call out pattern pitfalls:
  - [ ] Strategy pattern fits pricing because algorithms vary independently
  - [ ] Singleton is unnecessary unless explicitly required; DI is easier to test
- [ ] Draw the class diagram with relationships
- [ ] Walk through the main flow end-to-end

## Phase 4: Implement Key Methods (15-20 min)
- [ ] Focus on 2-3 methods with the most invariants (not every getter)
- [ ] For Parking Lot: park(), leave(), findAvailableSpot()
- [ ] Show error handling in the implementation
- [ ] Address concurrency:
  - [ ] Identify shared mutable state
  - [ ] Pick a concrete locking/optimistic strategy (per-spot lock, per-floor lock, optimistic DB update)
  - [ ] Avoid global locks that serialize the entire system
  - [ ] If single-threaded by assumption, state that explicitly
- [ ] Implement PricingStrategy with dependency injection:
  - [ ] HourlyPricing, FlatRatePricing, SurgePricing as interchangeable strategies
- [ ] Discuss invariant enforcement (e.g., one active ticket per spot)

## Phase 5: Discuss Extensions (5 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] Proactively demonstrate Open/Closed Principle:
  - [ ] "To add a new vehicle type, we'd just add a new Vehicle subclass, no changes to existing code"
  - [ ] Use concrete deltas: add EV spots, reservations, surge pricing, or multiple lots
  - [ ] For each change, name which class changes and which does not
- [ ] State trade-offs you made and why
- [ ] Mention production next steps: tests around invariants, contention, migration safety
- [ ] Ask the interviewer if they have questions

## Scoring Rubric Quick Reference
| Signal | What to demonstrate |
|--------|-------------------|
| Scope control | Define in/out scope and assumptions in 60-90 seconds |
| Invariant thinking | Name invariants and enforce them in code |
| Concurrency judgment | Identify shared mutable state and pick concrete strategy |
| Extensibility proof | Show next feature as additive class with minimal edits |
| Staff-level signal | Tradeoff narration with explicit rejections and failure modes |

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
