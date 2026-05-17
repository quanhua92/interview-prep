# UML Class Diagrams -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What are the core entities in the domain?
  - [ ] Are there interfaces or abstract classes expected?
  - [ ] Should we model runtime flows (sequence diagram) too?
  - [ ] What level of detail: field types + methods, or just class names and relationships?
- [ ] Identify the central/orchestrator class (ParkingLot, Library, Order, etc.)
- [ ] List key entities (3-8 classes):
  - [ ] Core domain objects
  - [ ] Abstract classes and interfaces
  - [ ] Strategy/Policy injected classes
- [ ] State which relationship types you expect to use:
  - [ ] Inheritance (is-a) for subtype hierarchies
  - [ ] Realization (implements) for interface contracts
  - [ ] Composition (lifetime owned) for parent-child where child dies with parent
  - [ ] Aggregation (loose has-a) for parent-child where child survives
  - [ ] Association (persistent reference) for peer-to-peer references
  - [ ] Dependency (transient use) for method-parameter/local-variable usage

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the central class box center-board with three compartments (name, fields, methods)
- [ ] Place subclasses below their parent, interfaces above implementations
- [ ] Identify the main relationships and their types:
  - [ ] Inheritance arrows: child to parent, solid line with hollow triangle
  - [ ] Realization arrows: implementor to interface, dashed line with hollow triangle
  - [ ] Composition: solid line with filled diamond on owner end
  - [ ] Aggregation: solid line with hollow diamond on owner end
  - [ ] Association: solid line with open arrow
  - [ ] Dependency: dashed line with open arrow
- [ ] Note the composition vs aggregation decisions and prepare lifetime arguments:
  - [ ] "If I delete the parent, does the child also get deleted?" Yes = composition, No = aggregation
- [ ] Present the diagram skeleton and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Fill in class box details for each class:
  - [ ] Visibility modifiers on every field (`-` default) and method (`+` default)
  - [ ] Field signatures in `name: type` format (UML 2.5 standard, language-neutral)
  - [ ] Method signatures with parameters and return types
  - [ ] Static members underlined (Mermaid: `$` suffix)
  - [ ] Abstract methods italicized (Mermaid: `*` suffix)
- [ ] Mark interfaces with `<<interface>>` stereotype
- [ ] Mark abstract classes with `{abstract}` annotation
- [ ] Add multiplicity at both ends of every relationship:
  - [ ] `1`: exactly one (mandatory)
  - [ ] `0..1`: zero or one (optional)
  - [ ] `*`: zero or more
  - [ ] `1..*`: one or more (at least one)
  - [ ] `n..m`: between n and m
- [ ] Walk through the diagram class by class:
  - [ ] Central class and its composition/aggregation children
  - [ ] Inheritance hierarchies (subtypes and their parent)
  - [ ] Interface realizations (implementations and their contracts)
  - [ ] Associations between peers
  - [ ] Dependencies for transient uses

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Draw a sequence diagram for the main happy-path flow:
  - [ ] List participants (4-6 classes) along the horizontal axis
  - [ ] Draw lifelines (vertical dashed lines) for each participant
  - [ ] Show messages (arrows) between lifelines top-to-bottom (8-15 messages)
  - [ ] Use `alt`/`else` for branching, `loop` for iteration, `opt` for optional flows
  - [ ] Keep it at public-method level, avoid getter/setter calls
- [ ] Discuss composition vs aggregation edge cases:
  - [ ] Library/Book: aggregation (books outlive the library)
  - [ ] Order/OrderItem: composition (line items die with the order)
  - [ ] Loan/Fine: composition (fine doesn't exist outside the loan)
- [ ] Explain your relationship choices out loud:
  - [ ] Why composition over aggregation for each relationship
  - [ ] Why dependency over association (transient vs persistent reference)
  - [ ] Why interface + realization over inheritance
- [ ] Address common pitfalls:
  - [ ] Inheritance arrow direction: child to parent, not parent to child
  - [ ] Diamond on owner's end, not part's end
  - [ ] `<<interface>>` stereotype present on all interfaces
  - [ ] Visibility on every member, no bare field names
  - [ ] Multiplicity on both ends of every relationship

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the diagram in 2-3 sentences (entities, key relationships, design rationale)
- [ ] State the trade-offs you made and why (e.g., composition over inheritance, aggregation vs composition)
- [ ] Mention what you would improve with more time (e.g., additional subtypes, error-handling flows, concurrency)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
