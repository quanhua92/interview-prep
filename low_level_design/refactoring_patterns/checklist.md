# Refactoring Patterns -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the scope: a single class refactor or a system-level migration?
  - [ ] Can we take downtime, or must the system remain live during the migration?
  - [ ] Is there existing test coverage, or do we need to add characterization tests first?
- [ ] Identify the code smell or problem:
  - [ ] God class with too many responsibilities
  - [ ] Long method with deeply nested conditionals
  - [ ] Tightly coupled legacy system needing modernization
  - [ ] Long parameter list making methods hard to call and test
- [ ] List constraints (latency, availability, team velocity):
  - [ ] Zero downtime during migration
  - [ ] Team must keep shipping features during the refactor
  - [ ] Rollback must be instant (routing change or flag flip, never a redeploy)
- [ ] State your approach: incremental, behavior-preserving, test-first

## Phase 2: High-Level Design (3-5 min)
- [ ] Identify the refactoring pattern(s) that apply:
  - [ ] Strangler Fig for system-level migration (monolith to microservice)
  - [ ] Branch by Abstraction for swapping implementations without blocking the team
  - [ ] Extract Class for breaking up a god class
  - [ ] Extract Interface for decoupling callers from concrete implementations
  - [ ] Anti-Corruption Layer for protecting a new domain model from legacy shapes
  - [ ] Introduce Parameter Object for long parameter lists
- [ ] Describe the migration phases at a high level:
  - [ ] Phase 1: Add characterization tests to lock existing behavior
  - [ ] Phase 2: Introduce abstraction (interface/facade) at the call boundary
  - [ ] Phase 3: Build new implementation behind the abstraction
  - [ ] Phase 4: Switch traffic/callers to new implementation (incrementally)
  - [ ] Phase 5: Remove old code and cleanup abstractions
- [ ] Define rollback strategy for each phase:
  - [ ] Routing flip (Strangler Fig)
  - [ ] Feature flag toggle (Branch by Abstraction)
  - [ ] Read cutover back to old DB (Dual-Write)
- [ ] Present the plan and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Walk through the Strangler Fig migration steps:
  - [ ] Deploy facade/proxy (API gateway) in front of monolith
  - [ ] Identify first endpoint to migrate
  - [ ] Build new service for that endpoint
  - [ ] Route traffic to new service; shadow-read to compare outputs
  - [ ] Cut over when shadow shows 0 divergence
  - [ ] Repeat for next endpoint; decommission monolith when done
- [ ] Walk through Branch by Abstraction (payment gateway example):
  - [ ] Extract interface from existing implementation
  - [ ] All callers depend on interface, not concrete class
  - [ ] Build new implementation behind the interface
  - [ ] Swap is a one-line DI change
- [ ] Walk through Dual-Write for data migration:
  - [ ] Phase 1: Dual-write, old DB authoritative (1-2 weeks)
  - [ ] Phase 2: Dual-write, new DB authoritative (1 week)
  - [ ] Phase 3: Single-write, new DB only (2-week rollback window, then decommission)
  - [ ] Run consistency checks: compare records across DBs, fix divergence before advancing
- [ ] Walk through Extract Class (god class breakup):
  - [ ] Identify cohesive cluster of fields and methods
  - [ ] Create new class, move fields and methods
  - [ ] Old class delegates to new class (preserves old API)
  - [ ] Each step is a separate, reviewable commit
- [ ] Describe the Anti-Corruption Layer:
  - [ ] Adapter/translator between legacy model and new domain model
  - [ ] New system only sees rich domain objects, never legacy DTOs
  - [ ] Example: flat Customer record -> Buyer + ShippingAddress + PaymentMethod

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss test coverage strategy:
  - [ ] Characterization tests first: run representative inputs, record outputs
  - [ ] These become the regression suite for the refactor
  - [ ] No refactoring step should change any test output
- [ ] Address anti-patterns to avoid:
  - [ ] Refactoring without tests
  - [ ] Big-bang refactor on a long-lived branch
  - [ ] Semantic changes mixed with structural changes
  - [ ] Extracting a service before the domain model is stable
  - [ ] Leaving dual-write running forever (set a hard 4-week deadline)
- [ ] Discuss feature flag management:
  - [ ] Flags control old-vs-new routing during migration
  - [ ] Clean up flags when migration completes (avoid flag debt)
- [ ] Explain when NOT to use each pattern:
  - [ ] Strangler Fig is overkill for a small class refactor (use Extract Class)
  - [ ] Branch by Abstraction is unnecessary with no parallel implementation
  - [ ] ACL between two clean models is enterprise over-engineering
  - [ ] Dual-write without reconciliation and a deletion plan is dangerous
- [ ] Discuss risk control framing:
  - [ ] Extract Class reduces cognitive load
  - [ ] Introduce Interface reduces compile-time coupling
  - [ ] Branch by Abstraction reduces merge risk
  - [ ] Strangler Fig reduces release risk
  - [ ] Anti-Corruption Layer reduces domain contamination

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the refactoring plan in 2-3 sentences
- [ ] State the key principle: "smallest reversible step that preserves behavior"
- [ ] Mention cleanup: migration abstractions (flags, adapters, dual-writes) must be deleted when migration finishes
- [ ] Mention extensibility: the refactored code should make the next change easier (new payment provider = new impl + config change)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
