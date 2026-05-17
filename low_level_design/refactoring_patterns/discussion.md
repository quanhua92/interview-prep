# Refactoring Patterns: Strangler Fig, Extract Class, Anti-Corruption Layer & Legacy Modernization

Source: [Refactoring Patterns (CalibreOS)](https://www.calibreos.com/learn/lld-refactoring-patterns)

## One-Liner
Safely modernize legacy codebases without a big-bang rewrite using incremental migration patterns: Strangler Fig, Branch by Abstraction, Extract Class, Anti-Corruption Layer, and Dual-Write.

## Why Refactoring Patterns Are an Interview Topic
Staff and senior engineering interviews increasingly include "production engineering" questions: "How would you modernize this legacy codebase without downtime?" or "The checkout service is a 15,000-line class. How do you break it up?" These questions test whether you can change a running system safely, a skill that's more valuable in production than any greenfield architecture.

The core challenge: you can't stop the world while you refactor. The system must keep working during the migration. This requires patterns that allow the old and new code to coexist temporarily.

## What Earns Each Level on Refactoring Questions

**6/10:** "We'd rewrite it from scratch" or "extract it into a separate service." No migration plan, no risk management.

**8/10:** Describes the strangler fig pattern. Mentions feature flags. Knows Extract Class and Extract Method from Fowler's *Refactoring* book.

**10/10:** Designs the full migration plan with a dual-write period, anti-corruption layer between old and new models, branch-by-abstraction to keep the team shipping while the refactor is in flight, and explicit rollback triggers. Talks about test coverage as a prerequisite ("you can't safely refactor code that has no tests").

## The Core Refactoring Patterns

### 01. Strangler Fig -- Migrate Without Big-Bang Rewrite
- Route traffic to the new implementation via a facade/proxy
- Old system handles everything it currently handles; new system handles newly routed paths
- Incrementally move traffic until the old system is strangled
- Safe because: rollback = revert routing
- Used by: Netflix, Shopify, GitHub for monolith migrations
- Example: add an API gateway in front of a monolith, route /payments to the new Payment service, everything else to monolith

### 02. Branch by Abstraction -- Keep Shipping During Refactor
- Introduce an interface/abstract class in front of the code you want to change
- Production uses the old implementation; new implementation is behind the interface
- Swap the implementation when the new one is ready
- Teams can merge to main daily because the abstraction prevents compile-time breakage
- The interface is the seam -- change what's behind it without affecting callers

### 03. Extract Class -- Break the God Class
- A class with 20 responsibilities has 20 reasons to change (violates SRP)
- Identify a cohesive subset of fields and methods that belong together
- Create a new class
- Move the fields (update all references)
- Move the methods (update all callers)
- Make the old class delegate to the new one
- Each Extract Class step should be a separate, reviewable commit
- Signal: "I can describe what this class does without using the word AND"

### 04. Extract Interface / Introduce Interface
- When a class is used in many places and you need to swap implementations: extract an interface from the existing class
- All callers now depend on the interface, not the concrete class
- Enables: mocking in tests, multiple implementations (e.g., CachingPaymentGateway wraps RealPaymentGateway via the same interface), and the Branch by Abstraction technique

### 05. Anti-Corruption Layer (ACL)
- When integrating legacy code with a new system that uses a different domain model: create an adapter/translator layer that converts between the two models
- The new system never sees the legacy model's anemic DTOs and database column names
- The ACL translates them into rich domain objects
- Example: legacy system has flat 'Customer' DB record with 40 fields; new system models 'Buyer', 'ShippingAddress', 'PaymentMethod' as separate objects. ACL converts between them

### 06. Introduce Parameter Object
- A method with 8 parameters is hard to call, hard to test, and hard to extend
- Group logically related parameters into a value object
- Before: `checkout(userId, cartId, couponCode, shippingAddr, billingAddr, paymentToken, currency, express)`
- After: `checkout(CheckoutRequest)` where CheckoutRequest is an immutable value object with all these fields
- Easier to add new parameters (add a field), easier to mock in tests

## Branch-by-Abstraction: Swapping a Payment Gateway Without Downtime

```python
# payment_gateway.py
from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Optional

# Step 1: Extract the interface, callers now depend on the abstraction
class PaymentGateway(ABC):
    @abstractmethod
    def charge(self, amount_cents: int, token: str) -> "ChargeResult": ...

    @abstractmethod
    def refund(self, charge_id: str, amount_cents: int) -> "RefundResult": ...

@dataclass
class ChargeResult:
    success: bool
    charge_id: Optional[str]
    error_code: Optional[str]

# Step 2: Old implementation behind the interface, no callers change
class StripeGateway(PaymentGateway):
    def charge(self, amount_cents: int, token: str) -> ChargeResult:
        # existing Stripe SDK calls unchanged
        ...
    def refund(self, charge_id: str, amount_cents: int) -> ChargeResult: ...

# Step 3: New implementation developed in parallel, tested independently
class BraintreeGateway(PaymentGateway):
    def charge(self, amount_cents: int, token: str) -> ChargeResult: ...
    def refund(self, charge_id: str, amount_cents: int) -> ChargeResult: ...

# Step 4: Coordinator depends on the interface, swap is a one-line DI change
class CheckoutService:
    def __init__(self, gateway: PaymentGateway):  # injected, not instantiated
        self._gateway = gateway

    def checkout(self, total_cents: int, token: str) -> bool:
        result = self._gateway.charge(total_cents, token)
        return result.success

# Swap with zero code changes to CheckoutService:
# container.bind(PaymentGateway, StripeGateway)    # before
# container.bind(PaymentGateway, BraintreeGateway) # after, one line
```

## Strangler Fig Migration: Step-by-Step

1. **Deploy a facade/proxy** (API gateway, reverse proxy, or routing layer) in front of the monolith
2. **Identify the first endpoint** to migrate (e.g., `/payments`)
3. **Build the new service** for that endpoint behind the facade
4. **Route traffic** for that endpoint to the new service; all other traffic goes to the monolith
5. **Verify** with shadow reads (new service processes the request but monolith result is returned; compare outputs)
6. **Cut over** when shadow comparison shows 0 divergence
7. **Repeat** for the next endpoint
8. **Decommission** the monolith when all traffic is routed to new services

Key: at every step, rollback is a routing change, not a redeploy.

## The Dual-Write Pattern for Data Migration

The hardest part of any refactoring that changes data storage is migrating the data without downtime. The dual-write pattern handles this safely:

- **Phase 1: Dual-write, old DB authoritative:** Write to both old DB and new DB. Read from old DB. Old is authoritative. New DB is populated but not trusted yet. Run for 1-2 weeks. Verify new DB has consistent data by running comparison queries.
- **Phase 2: Dual-write, new DB authoritative:** Write to both. Read from new DB. New is authoritative. Old DB still receives writes as a fallback/backup. Run for 1 week. Monitor closely. Rollback = flip reads back to old DB.
- **Phase 3: Single-write, new DB only:** Stop writing to old DB. Old DB is frozen as a backup. Reads from new DB. Keep old DB alive for 2 weeks (rollback window). Then decommission.

**Consistency check during dual-write:** Run a background job that reads matching records from both DBs and compares. Log any divergence. Fix the sync bug before advancing to the next phase. Never advance phases if divergence rate > 0.01%.

## Pattern Selection Guide

| Problem | Pattern | Key condition to apply it | Risk if misapplied |
|---------|---------|--------------------------|-------------------|
| Monolith to microservice migration | Strangler Fig | New service is independently deployable with its own DB | Missing anti-corruption layer causes both systems to share a confused domain model |
| God class (one class does everything) | Extract Class | Can identify a cohesive subset of responsibilities | Extracting without tests first causes silent regressions |
| Long parameter list (>4 params) | Introduce Parameter Object | Parameters logically belong together as a concept | Creating a parameter object that's just a bag of fields (same problem, different container) |
| Need to swap implementations without breaking callers | Extract Interface + Branch by Abstraction | Callers are injected the dependency (not instantiated inline) | Interface extracted too late, callers already have concrete type dependencies throughout the codebase |
| Integrating with legacy system with bad domain model | Anti-Corruption Layer | New system has a clean domain model worth protecting | ACL becomes too thick, re-implements business logic instead of just translating |
| Need to ship features while refactoring in progress | Branch by Abstraction + Feature Flags | New implementation passes all existing tests | Feature flag debt, forgotten flags left permanently on create dead code |

## Refactoring Anti-Patterns to Avoid

1. **Refactoring without tests.** The #1 rule: if there are no tests covering the code you're refactoring, write characterization tests first. Run representative inputs through the code and record the outputs. These become your regression suite -- any refactoring that changes the output is caught immediately.
2. **Big-bang refactor on a long-lived branch.** A 6-week refactor branch that diverges from main creates a merge nightmare and kills team velocity. Fix: use branch-by-abstraction -- the refactor lives on main, hidden behind an interface. Merge daily.
3. **Semantic changes during refactoring.** Refactoring means changing structure, not behavior. If you change variable names AND fix a bug in the same commit, you can't distinguish which change caused a regression. Rule: one refactoring step per commit, no behavior changes.
4. **Extracting a service before the domain model is stable.** If you extract a Payments microservice while the payment flow is still changing every week, you'll spend more time updating the API contract than building features. Extract when the domain is understood, not when it's still being discovered.
5. **Leaving dual-write running forever.** Dual-write adds write latency and consistency bugs. It's a migration tool, not an architecture. Set a hard deadline (4 weeks) and force the cutover.

## Interview Delivery Summary

When asked to refactor a legacy system, start with: **"First, I'd ensure test coverage of the existing behavior -- you can't safely refactor code you can't verify."** This signals production engineering maturity immediately.

Then describe the strangler fig for large-scale migration, branch-by-abstraction for keeping the team shipping during the refactor, and dual-write for safe data migration. Always mention rollback: "At every phase, rollback is a routing change or a feature flag flip, never a re-deploy."

The staff signal: bring up the anti-corruption layer to protect the new domain model from the legacy model's shape. This is the part most candidates miss.

## Refactoring Patterns Are Risk Controls

Refactoring patterns are useful because they reduce **blast radius**. `Extract Class` reduces local cognitive load; `Introduce Interface` reduces compile-time coupling; `Branch by Abstraction` reduces merge risk; `Strangler Fig` reduces release risk; `Anti-Corruption Layer` reduces domain contamination. In an interview, lead with the risk each pattern controls, not the mechanics alone.

For a god class, the correct first move is rarely "extract microservice." First add characterization tests around externally visible behavior, then find cohesive clusters of fields and methods. Extract one cluster behind a new class and delegate from the old class. The old API remains stable while internals improve. This is how you keep production safe and make review smaller than "trust me, I rewrote checkout."

For a system migration, Strangler Fig shifts risk from code replacement to traffic routing. The facade chooses old or new implementation by endpoint, tenant, region, or feature flag. Rollback is a routing flip. The pitfall is skipping data reconciliation: if old and new systems both write, you need shadow reads, diff metrics, and a clear cutover point.

A staff-level answer also names the cleanup: abstractions introduced for migration must be deleted when migration finishes. Otherwise the refactor leaves a permanent maze of flags, adapters, and double-writes.

## Extract Class While Preserving the Old API

```java
// CheckoutRefactor.java
interface FraudChecker {
    RiskDecision check(CheckoutRequest request);
}

final class RuleBasedFraudChecker implements FraudChecker {
    public RiskDecision check(CheckoutRequest request) {
        if (request.amountCents() > 100_000 && request.isFirstOrder()) {
            return RiskDecision.review("large first order");
        }
        return RiskDecision.approve();
    }
}

final class CheckoutService {
    private final FraudChecker fraudChecker;
    private final PaymentGateway paymentGateway;

    CheckoutService(FraudChecker fraudChecker, PaymentGateway paymentGateway) {
        this.fraudChecker = fraudChecker;
        this.paymentGateway = paymentGateway;
    }

    Receipt checkout(CheckoutRequest request) {
        RiskDecision risk = fraudChecker.check(request);
        if (!risk.approved()) {
            throw new CheckoutRejectedException(risk.reason());
        }
        return paymentGateway.charge(request);
    }
}
```

## When NOT to Use Each Refactoring Pattern

Do not use Strangler Fig for a small, internal class refactor where one safe `Extract Class` PR is enough. Do not use Branch by Abstraction when there is no parallel implementation; an interface with one implementation can be temporary, but it should earn its place. Do not introduce an Anti-Corruption Layer between two clean models just to sound enterprise. Do not dual-write unless you have reconciliation and a deletion plan. The best refactoring answer is often the smallest reversible step that preserves behavior.

## Refactoring Interview Walkthrough Script

A concise senior walkthrough sounds like this: "I will not start with a rewrite. I will lock behavior with characterization tests, identify responsibility clusters, introduce interfaces at the call boundaries, extract one class at a time, and keep the public API stable until callers migrate."

Then make the migration operational. "Every step merges to main. Feature flags decide whether old or new code handles a request. I will instrument old-vs-new output diffs during shadow mode and define rollback triggers before cutover." That shows production discipline, not just code cleanliness.

Finally, answer extensibility. If the current refactor extracts `PaymentGateway`, the next payment provider should be a new implementation and a configuration change. If the current refactor extracts `FraudChecker`, new fraud rules should be isolated behind that port. The measurable outcome is fewer reasons to modify the checkout orchestrator, smaller tests, and lower regression risk.

## Interview Questions
- Q1: When is Strangler Fig the wrong refactoring pattern, and what would you use instead?
- Q2: We have a PaymentProcessor class with 8,000 lines and 40 methods. How do you refactor it?
- Q3: How do you migrate a monolith's Orders module to a new microservice without downtime?
