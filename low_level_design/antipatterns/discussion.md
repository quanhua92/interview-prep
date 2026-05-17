# LLD Anti-Patterns: God Class, Anemic Models, Primitive Obsession

Source: [Antipatterns (CalibreOS)](https://www.calibreos.com/learn/lld-antipatterns)

## One-Liner
Recognize and refactor the six most-tested LLD anti-patterns (God Class, Anemic Domain Model, Primitive Obsession, Feature Envy, Shotgun Surgery, Circular Dependencies) with violation/fix code and interviewer probes.

## Why Anti-Patterns Matter More Than Patterns in LLD Interviews
- Most candidates rehearse design patterns. Few can articulate why their first draft is *wrong*. Interviewers probe for anti-patterns because spotting them separates engineers who have shipped real systems from those who have only memorized GoF.
- An anti-pattern is a recurring design choice that *appears* reasonable but creates predictable, expensive problems at scale: a class everyone modifies, a domain model with no behavior, a primitive type that hides validation bugs.
- The interviewer's playbook: nudge you toward an anti-pattern (often by asking the simplest solution first), then probe with extension questions ("What if we add tax?", "What if email is also used in Customer?", "How would you add SMS notifications?") to see whether your design crumbles. **The candidate who recognizes the trap and refuses to walk into it scores highest.**

## What Earns Each Level
- **6/10:** Knows SOLID by name. Writes a class per noun. Doesn't notice when one class grows to 600 lines or when domain entities become bags of getters and setters.
- **8/10:** Recognizes God Class and Anemic Domain Model by smell. Splits responsibilities proactively. Uses value objects for money and identifiers. Justifies each choice with a one-line rationale.
- **10/10:** Treats anti-patterns as *first-class evaluation criteria* during their own design. Names the smell explicitly ("this would create Shotgun Surgery, let me encapsulate"). Cites Martin Fowler's anemic-domain-model essay or *Refactoring* directly. Distinguishes acceptable simplicity from genuine smell, knows that a pure-data DTO is fine but a domain entity without behavior is not.

## The Six LLD Anti-Patterns Interviewers Test

### 01. God Class (one class doing everything)
- Symptoms: 500+ lines, 20+ methods spanning unrelated concerns (pricing, persistence, notifications, validation), every feature change touches it.
- Probe: "Walk me through what changes when we add hourly pricing." If your answer modifies the same class for a different reason, you've built a god.
- Fix: split by *reason to change*, extract PricingService, AllocationService, BillingService, NotificationService.

### 02. Anemic Domain Model (entities are bags of getters/setters)
- Symptoms: Order has only fields and accessors; OrderService.cancelOrder(order) holds the logic.
- Domain entities don't enforce their own invariants.
- Coined by Martin Fowler as the prototypical sign of *procedural code disguised as objects*.
- Probe: "Where does the rule live that you cannot cancel a shipped order?" If the answer is "in the service", the model is anemic.
- Fix: rich domain, order.cancel() enforces its own state machine.

### 03. Primitive Obsession (using int, String for domain concepts)
- Symptoms: amount: int (cents? dollars? rupees?), email: String (validated where, exactly?), userId: long (which user table?).
- Bugs hide in unit confusion and missing validation.
- Probe: "Two services pass amount around, how do you guarantee no one mixes cents and dollars?" Fix: Money(amount, Currency), Email(string) with validation in constructor, UserId(uuid).
- Type system prevents the bug at compile time.

### 04. Feature Envy (method uses another class's data more than its own)
- Symptoms: Order.calculateDiscount() calls customer.getTier(), customer.getLoyaltyPoints(), customer.getJoinDate() three times each. Order is *envious* of Customer's data.
- Probe: "Where does the discount logic belong?" Fix: move calculateDiscount onto Customer, or extract a DiscountStrategy that owns the calculation.
- The method belongs where the data lives.

### 05. Shotgun Surgery (one change requires edits in many files)
- Symptoms: adding a new payment field requires editing PaymentRequest, PaymentResponse, PaymentValidator, PaymentRepository, PaymentMapper, PaymentEvent, PaymentAudit -- seven files for one concept.
- Probe: "How would you add a new field, like installment_count?" If the answer is a long list, the concept is scattered.
- Fix: aggregate the concept into a single Payment value object that owns its own validation, persistence mapping, and serialization.

### 06. Circular Dependencies (A imports B which imports A)
- Symptoms: User imports Order to get user.getOrders(); Order imports User for order.getCustomer().
- Detected by import-cycle linters (madge, pylint, dependency-cruiser).
- Probe: "What happens to your build if I move Order to a different module?" Fix: extract a shared interface (UserView), invert the dependency (Order knows a UserId, not a User), or introduce a mediator (CustomerOrderService).
- Cycles destroy modularity and testability.

## Deep Dive 1: God Class

The God Class (also called *Blob* in Riel's *Object-Oriented Design Heuristics*) is what every first-draft parking lot, library system, or food delivery design becomes if you don't fight it. The candidate writes `class ParkingLot` and dumps every behavior inside: spot allocation, ticket generation, pricing, payment, billing, sensors, notifications.

The reason this happens is psychological: candidates feel *anchored* to the problem entity. The interviewer said "design a parking lot" so they create `ParkingLot` and start typing. They confuse the *problem domain noun* with the *implementation entity*. In production systems, "parking lot" is a *bounded context*, not a class -- it contains a SpotAllocator, a PricingEngine, a BillingService, a TicketService, each with a single reason to change.

**How to spot it during your own design:** count the verbs your class is responsible for. `parkingLot.allocateSpot()`, `parkingLot.calculateFee()`, `parkingLot.processPayment()`, `parkingLot.sendReceipt()` -- that's four reasons to change. The fix is mechanical: each verb-cluster becomes a service, and `ParkingLot` becomes a thin coordinator (or disappears entirely, replaced by an application service).

**The interview probe:** "Add a new pricing rule for monthly subscribers." If your answer modifies `ParkingLot`, you have a God Class. The principled answer modifies `PricingEngine` (or adds a new `MonthlyPricingStrategy`), `ParkingLot` is untouched.

### God Class Violation

```python
# ANTI-PATTERN: ParkingLot owns allocation, pricing, billing, notification, persistence.
# Six reasons to change, one class. Every feature edit fights merge conflicts.
class ParkingLot:
    def __init__(self, db, payment_gateway, sms_client, email_client):
        self.db = db
        self.payment = payment_gateway
        self.sms = sms_client
        self.email = email_client
        self.spots = self._load_spots()  # 200 spots

    def park_vehicle(self, vehicle, payment_method):
        # Allocation logic
        spot = None
        for s in self.spots:
            if s.is_free and s.size >= vehicle.size:
                s.is_free = False
                spot = s
                break
        if not spot:
            raise Exception("Lot full")

        # Pricing logic, hardcoded rates, hardcoded discount rules
        rate_per_hour = 5 if vehicle.size == "compact" else 10
        if vehicle.is_member:
            rate_per_hour *= 0.8

        # Ticket generation
        ticket_id = f"T{int(time.time())}"
        self.db.execute(
            "INSERT INTO tickets VALUES (?, ?, ?, ?)",
            (ticket_id, vehicle.plate, spot.id, time.time()),
        )

        # Payment
        self.payment.charge(payment_method, rate_per_hour)

        # Notification
        self.sms.send(vehicle.owner_phone, f"Parked at {spot.id}")
        self.email.send(vehicle.owner_email, f"Receipt #{ticket_id}")

        return ticket_id

    # Plus 17 more methods: release_vehicle, calculate_fee, apply_discount,
    # refund, generate_report, send_overdue_notice, mark_spot_maintenance, ...
```

### God Class Refactored (services + thin coordinator)

```python
# FIXED: each service has one reason to change. ParkingLotService coordinates.
from abc import ABC, abstractmethod
from dataclasses import dataclass

@dataclass(frozen=True)
class Ticket:
    id: str
    spot_id: str
    vehicle_plate: str
    issued_at: float

# SpotAllocator -- reason to change: allocation policy
class SpotAllocator:
    def __init__(self, spots): self._spots = spots

    def allocate(self, vehicle) -> "Spot":
        for s in self._spots:
            if s.is_free and s.fits(vehicle):
                s.occupy()
                return s
        raise NoSpotAvailable()

    def release(self, spot_id: str) -> None: ...

# PricingEngine -- reason to change: pricing rules
class PricingStrategy(ABC):
    @abstractmethod
    def quote(self, vehicle, duration_hours: float) -> "Money": pass

class StandardPricing(PricingStrategy):
    def quote(self, vehicle, hours): ...

class MemberPricing(PricingStrategy):  # OCP -- add new pricing without touching others
    def quote(self, vehicle, hours): ...

# BillingService -- reason to change: payment provider
class BillingService:
    def __init__(self, gateway): self._gateway = gateway
    def charge(self, payment_method, amount: "Money") -> "Receipt": ...

# NotificationService -- reason to change: channels
class NotificationService:
    def __init__(self, channels): self._channels = channels  # email, sms, push
    def notify_parked(self, vehicle, spot, ticket): ...

# TicketRepository -- reason to change: storage backend
class TicketRepository(ABC):
    @abstractmethod
    def save(self, ticket: Ticket) -> None: pass

# Thin coordinator -- orchestrates, doesn't implement
class ParkingLotService:
    def __init__(self, allocator, pricing, billing, notifier, tickets):
        self._allocator = allocator
        self._pricing = pricing
        self._billing = billing
        self._notifier = notifier
        self._tickets = tickets

    def park(self, vehicle, payment_method) -> Ticket:
        spot = self._allocator.allocate(vehicle)
        quote = self._pricing.quote(vehicle, duration_hours=1)
        self._billing.charge(payment_method, quote)
        ticket = Ticket(id=new_id(), spot_id=spot.id,
                        vehicle_plate=vehicle.plate, issued_at=now())
        self._tickets.save(ticket)
        self._notifier.notify_parked(vehicle, spot, ticket)
        return ticket
```

## Deep Dive 2: Anemic Domain Model

Martin Fowler named the *Anemic Domain Model* in 2003 as a prototypical anti-pattern: it has all the *appearance* of a domain model -- entities, repositories, services -- but the entities are bags of getters and setters and *all* business logic lives in the service layer. It looks object-oriented but is procedural.

Concretely: `Order` has `getStatus()`, `setStatus()`, `getItems()`, `setItems()`, `getTotal()`, `setTotal()`, but no behavior. The rule "you cannot cancel a shipped order" lives in `OrderService.cancelOrder(orderId)`. The rule "applying a discount cannot make total negative" lives in `DiscountService.apply(orderId, discount)`. The entity is *anemic* -- it has no immune system. It accepts any state any caller writes to it.

**Why this is a trap in interviews:** it's seductive. New engineers default to it because their frameworks push them there -- Spring, ASP.NET, Django all encourage thin entities and fat services. The interviewer is testing whether you've thought past framework defaults. The strong answer pushes invariants *into* the entity: `order.cancel()` *enforces* that the order is in a cancellable state; `order.applyDiscount(discount)` *enforces* that the resulting total is non-negative. The service layer becomes a thin orchestrator, not the home of business rules.

**The interview probe:** "Where does the rule live that prevents cancelling a shipped order?" If your answer is "in the OrderService", anemic. If it is "in `Order.cancel()` which throws if state is SHIPPED", rich. **The richer the entity, the harder it is to put the system into an invalid state from any caller, anywhere.**

Fowler's essay (martinfowler.com/bliki/AnemicDomainModel.html) is required reading. Cite it in interviews when you justify rich entities -- it shows you've engaged with the canonical literature.

### Anemic Domain Model Violation

```python
# ANTI-PATTERN: Order is a bag of getters/setters. All logic in OrderService.
# The entity cannot protect its own invariants, any caller can corrupt state.
from enum import Enum

class OrderStatus(Enum):
    PENDING = "pending"
    PAID = "paid"
    SHIPPED = "shipped"
    DELIVERED = "delivered"
    CANCELLED = "cancelled"

class Order:
    def __init__(self, id, items, status):
        self.id = id
        self.items = items
        self.status = status
        self.discount = 0
        self.total = 0

    # Just getters/setters -- no behavior, no invariants
    def get_status(self): return self.status
    def set_status(self, s): self.status = s
    def get_items(self): return self.items
    def set_total(self, t): self.total = t
    def set_discount(self, d): self.discount = d

class OrderService:
    def cancel_order(self, order_id):
        order = self.repo.find(order_id)
        # Rule lives here, not in the entity
        if order.get_status() == OrderStatus.SHIPPED:
            raise CannotCancelShippedOrder()
        order.set_status(OrderStatus.CANCELLED)
        self.repo.save(order)

    def apply_discount(self, order_id, discount):
        order = self.repo.find(order_id)
        # Another rule outside the entity
        if order.get_total() - discount < 0:
            raise DiscountExceedsTotal()
        order.set_discount(discount)
        order.set_total(order.get_total() - discount)
        self.repo.save(order)

    # Problem: any other caller (admin tool, batch job, message handler) can
    # set_status(CANCELLED) directly, bypassing the rule. The entity is defenceless.
```

### Anemic Domain Model Refactored to Rich Domain

```python
# FIXED: Order owns its invariants. State transitions are methods that enforce rules.
# Any caller, anywhere, must go through these methods, invalid states are unreachable.
from dataclasses import dataclass

@dataclass(frozen=True)
class Money:
    amount_cents: int
    currency: str
    def __post_init__(self):
        if self.amount_cents < 0:
            raise ValueError("Money cannot be negative")
    def minus(self, other): ...
    def is_zero(self): return self.amount_cents == 0

class Order:
    def __init__(self, id: str, items: list, total: Money):
        self._id = id
        self._items = list(items)
        self._total = total
        self._discount = Money(0, total.currency)
        self._status = OrderStatus.PENDING

    # Behavior: state transitions enforce their own rules
    def cancel(self) -> None:
        if self._status == OrderStatus.SHIPPED:
            raise CannotCancelShippedOrder(self._id)
        if self._status == OrderStatus.CANCELLED:
            return  # idempotent
        self._status = OrderStatus.CANCELLED

    def apply_discount(self, discount: Money) -> None:
        if discount.amount_cents > self._total.amount_cents:
            raise DiscountExceedsTotal(discount, self._total)
        self._discount = discount
        self._total = self._total.minus(discount)

    def mark_paid(self) -> None:
        if self._status != OrderStatus.PENDING:
            raise InvalidTransition(self._status, OrderStatus.PAID)
        self._status = OrderStatus.PAID

    def ship(self) -> None:
        if self._status != OrderStatus.PAID:
            raise InvalidTransition(self._status, OrderStatus.SHIPPED)
        self._status = OrderStatus.SHIPPED

    # Read-only views -- no public setters
    @property
    def status(self) -> OrderStatus: return self._status
    @property
    def total(self) -> Money: return self._total

# Service is now a thin orchestrator, invariants live in the entity
class OrderService:
    def cancel(self, order_id: str) -> None:
        order = self._repo.find(order_id)
        order.cancel()           # entity enforces the rule
        self._repo.save(order)

    def apply_discount(self, order_id: str, discount: Money) -> None:
        order = self._repo.find(order_id)
        order.apply_discount(discount)
        self._repo.save(order)
```

## Deep Dive 3: Primitive Obsession

*Primitive Obsession* (the term comes from Fowler's *Refactoring*, 1999) is the use of language primitives (int, String, long) where domain concepts should live. It's the most insidious anti-pattern because the code *looks correct*: `int amount`, `String email`, `long userId`. Compiler approves. Tests pass. Bugs ship.

The classic disaster: `int amount` for money. Service A interprets it as cents, Service B as dollars. They integrate. Now a $10 charge is processed as $0.10 or $1000. Stripe ships only `Money(amount_minor_units, currency)`, never raw integers, for exactly this reason. JPMorgan's 2012 *London Whale* losses were partly attributed to spreadsheet cell unit mixing. **Units kill more systems than algorithms.**

The second disaster: `String email`. Where is it validated? In `UserController.signup()`? Also in `AdminController.invite()`? Also in `BatchImporter`? You will find, every time, that one path skips validation, and one Bobby-Tables-shaped record makes it into the database. The fix is a value object: `Email(string)` validates in its constructor; if you have an `Email` instance, you have a valid email, period. Validation moves from N call sites to 1.

**The interview probe:** "Two services pass `amount` between them. How do you guarantee neither mixes cents and dollars?" The procedural answer ("we'll use a comment / convention / documentation") fails. The senior answer is `Money(amount_minor_units, currency)` -- the type system itself prevents the bug.

**The counterintuitive insight:** most candidates over-correct in the other direction and create value objects for *everything* (`UserName`, `OrderQuantity`, `LineItemIndex`). The right rule: introduce a value object when the primitive carries *invariants* (validation, units, format) or *identity*. A loop counter does not need a value object. An email does. A money amount does. A user ID does (preventing accidental cross-table joins).

### Primitive Obsession Violation and Fix

```python
# ANTI-PATTERN: primitives everywhere. Validation duplicated, units ambiguous.
class PaymentService:
    def charge(self, user_email: str, amount: int):
        # Email validation here...
        if "@" not in user_email or "." not in user_email:
            raise InvalidEmail()
        # ...and again in EmailService, AdminPanel, BatchImporter, drift inevitable

        # amount: cents? dollars? Caller knows. Maybe.
        self._gateway.charge(user_email, amount)

# FIX: value objects encode invariants once, in the constructor.
from dataclasses import dataclass
import re

EMAIL_RE = re.compile(r"^[^@\s]+@[^@\s]+\.[^@\s]+$")

@dataclass(frozen=True)
class Email:
    value: str
    def __post_init__(self):
        if not EMAIL_RE.match(self.value):
            raise ValueError(f"Invalid email: {self.value}")
    def domain(self) -> str:
        return self.value.split("@")[1]

@dataclass(frozen=True)
class Money:
    amount_minor_units: int          # always cents/paise, no ambiguity
    currency: str                    # ISO 4217: USD, EUR, INR
    def __post_init__(self):
        if self.amount_minor_units < 0:
            raise ValueError("Money cannot be negative")
        if self.currency not in {"USD", "EUR", "INR", "GBP"}:
            raise ValueError(f"Unsupported currency: {self.currency}")

    def plus(self, other: "Money") -> "Money":
        if self.currency != other.currency:
            raise ValueError("Cannot add different currencies")
        return Money(self.amount_minor_units + other.amount_minor_units, self.currency)

@dataclass(frozen=True)
class UserId:
    value: str  # not interchangeable with OrderId or ProductId at compile time

# Caller code becomes self-documenting and impossible to misuse:
class PaymentService:
    def charge(self, user_email: Email, amount: Money) -> "Receipt":
        # No validation here -- Email and Money are valid by construction
        # No unit confusion -- Money knows its currency and minor-unit basis
        ...

# Mixing currencies is now a runtime error from the type, not a silent bug:
# Money(100, "USD").plus(Money(100, "EUR"))  -> ValueError
```

## Deep Dive 4: Feature Envy and Shotgun Surgery

**Feature Envy** is when a method on class A spends most of its time accessing class B's data. `Order.calculateDiscount(customer)` calls `customer.getTier()`, `customer.getLoyaltyPoints()`, `customer.getJoinDate()`, `customer.isPremium()` -- *Order* is envious of *Customer*'s data. The method belongs where the data lives. Move it: either onto Customer (`customer.discountFor(order)`) or extract a `DiscountStrategy` that owns the calculation explicitly.

**Shotgun Surgery** is the dual sin: a single conceptual change requires edits across many files. Adding `installment_count` to a payment requires edits to `PaymentRequest`, `PaymentResponse`, `PaymentValidator`, `PaymentRepository`, `PaymentMapper`, `PaymentEvent`, `PaymentAudit` -- seven files for one concept. The concept is *scattered* across the codebase, instead of being *encapsulated* in a single Payment aggregate.

Both anti-patterns share a root cause: **misplaced cohesion**. Feature Envy is method-level (a method in the wrong place); Shotgun Surgery is system-level (a concept smeared across modules).

**The interview probes:**
- Feature Envy: "Where does the discount calculation belong?" Strong answer: where the discount-determining data lives, usually Customer or a strategy that owns the policy.
- Shotgun Surgery: "How would you add a new field, like a fraud score, to payment?" Strong answer: a single Payment aggregate owns its own request/response/persistence mapping, a new field changes one place. Weak answer: a long list of files.

The fix for both is the same root principle: *put data and behavior together*, and *encapsulate concepts behind aggregates* so the rest of the system depends on a stable interface, not on the internal layout.

### Feature Envy Violation and Fix

```python
# ANTI-PATTERN: Order envies Customer's data, accesses it 4 times in one method.
class Order:
    def calculate_discount(self, customer: "Customer") -> float:
        base = self.total
        # Heavy reliance on customer's internals -- feature envy
        if customer.get_tier() == "PLATINUM":
            return base * 0.15
        if customer.get_tier() == "GOLD":
            return base * 0.10
        if customer.get_loyalty_points() > 1000:
            return base * 0.05
        if (now() - customer.get_join_date()).days > 365 and customer.is_active():
            return base * 0.03
        return 0

# FIX OPTION A: move the method to Customer (where the data lives).
class Customer:
    def discount_rate(self) -> float:
        if self._tier == "PLATINUM": return 0.15
        if self._tier == "GOLD":     return 0.10
        if self._loyalty_points > 1000: return 0.05
        if (now() - self._join_date).days > 365 and self._active: return 0.03
        return 0

class Order:
    def calculate_discount(self, customer: Customer) -> float:
        return self.total * customer.discount_rate()

# FIX OPTION B: extract a Strategy that owns the policy independently.
# Use this when discount logic is policy that varies (A/B tests, regions, promos).
from abc import ABC, abstractmethod

class DiscountPolicy(ABC):
    @abstractmethod
    def rate_for(self, customer: Customer) -> float: pass

class TierAndLoyaltyPolicy(DiscountPolicy):
    def rate_for(self, customer):
        if customer.tier == "PLATINUM": return 0.15
        if customer.loyalty_points > 1000: return 0.05
        return 0

class HolidayPolicy(DiscountPolicy):
    def rate_for(self, customer): return 0.20  # blanket holiday sale

class Order:
    def calculate_discount(self, customer, policy: DiscountPolicy) -> float:
        return self.total * policy.rate_for(customer)
```

### Shotgun Surgery Violation and Fix

```python
# ANTI-PATTERN: adding installment_count to a payment requires changing 7 files.
# File 1: payment_request.py
class PaymentRequest:
    amount: int
    currency: str
    method: str
    # NEW field needed here

# File 2: payment_response.py -- add the same field
# File 3: payment_validator.py -- add validation rule
# File 4: payment_repository.py -- alter SQL INSERT/UPDATE
# File 5: payment_mapper.py -- extend ORM mapping
# File 6: payment_event.py -- extend event payload
# File 7: payment_audit.py -- extend audit log schema
# One concept (installments), seven edits -- shotgun.

# FIX: encapsulate the concept behind a Payment aggregate that owns its own
# serialization, validation, persistence shape, and event projection.
@dataclass(frozen=True)
class InstallmentPlan:
    count: int
    interval_days: int
    def __post_init__(self):
        if self.count < 1 or self.count > 24:
            raise ValueError("Installment count must be 1..24")
        if self.interval_days not in {7, 14, 30}:
            raise ValueError("Interval must be 7, 14, or 30 days")

@dataclass(frozen=True)
class Payment:
    amount: Money
    method: str
    installments: InstallmentPlan | None = None  # absent = single payment

    # The aggregate owns its own representations:
    def to_request_dict(self) -> dict: ...
    @classmethod
    def from_request_dict(cls, d: dict) -> "Payment": ...
    def to_db_row(self) -> dict: ...
    def to_event(self) -> dict: ...
    def to_audit_record(self) -> dict: ...
    def validate(self) -> None: ...  # invariants enforced once

# Adding fraud_score, currency_conversion, or any new concept changes ONE file.
# The seven peripheral modules call payment.to_*() and stay agnostic.
```

## Deep Dive 5: Circular Dependencies

A *circular dependency* -- A imports B, B imports A -- is the cleanest signal of a broken module boundary. It means the two classes share concepts they have not yet articulated as a third abstraction. Build systems hate cycles (some literally cannot compile them); test isolation becomes impossible (you cannot instantiate A without B and vice versa); reasoning about change blast radius collapses (every change in A potentially affects B and back).

In practice: `User` imports `Order` because `user.getOrders()` returns `List<Order>`, and `Order` imports `User` because `order.getCustomer()` returns `User`. Innocent. Both expressions are reasonable. The cycle is the bug.

**Detection:** every mainstream language has a tool. JavaScript/TypeScript: madge, dependency-cruiser, eslint-plugin-import. Python: pylint's cyclic-import check, import-linter. Java: ArchUnit, JDepend. CI should fail on new cycles. Big monorepos (Google, Meta) enforce no-cycle invariants at the build-graph level -- Bazel/Buck refuse cyclic build targets entirely.

**Three fixes, in order of preference:**

1. **Extract a third concept.** Both User and Order depend on `CustomerView` (or `UserId` value object). User defines its own User; Order references `UserId` and never imports User. The shared abstraction lives in a kernel module both depend on.
2. **Dependency Inversion.** Define an interface in the side that *needs* the dependency more loosely. `Order` declares `interface CustomerLookup { name(id): String }`. The User module *implements* CustomerLookup. The dependency arrow now points only one way.
3. **Move the function.** If `user.getOrders()` is the only reason User imports Order, move it out -- `OrderRepository.findByUser(userId)` is a better home anyway. Often the cycle reveals that one of the two associations was never needed on the entity.

**The interview probe:** "What happens to your build if I move Order to a different module?" If the candidate says "we'd have to move User too", cycle. The senior candidate has already seen the cycle in their design and designed it out from the start.

## Anti-Pattern Cheat Sheet

| Anti-Pattern | Symptom | Interviewer Probe | Fix |
|---|---|---|---|
| **God Class** | One class, 500+ lines, 15+ methods spanning unrelated concerns | "Walk me through what changes when we add X." Multiple unrelated edits to the same class. | Split by reason-to-change into focused services; thin coordinator orchestrates |
| **Anemic Domain Model** | Entity is only getters/setters; rules live in *Service classes | "Where does the rule that prevents cancelling a shipped order live?" | Push invariants into entity methods (order.cancel(), order.applyDiscount()) |
| **Primitive Obsession** | int amount, String email, long userId everywhere; validation duplicated | "How do you prevent mixing cents and dollars across services?" | Value objects: Money(amount, currency), Email(string), UserId(uuid) |
| **Feature Envy** | Method on A heavily uses B's data via 3+ accessor calls | "Where should this method live?" | Move method to the data's owner, or extract a Strategy that owns the policy |
| **Shotgun Surgery** | Adding one field requires editing 5+ files | "How would you add a new field like fraud_score?" | Aggregate the concept; one place owns serialization, persistence, validation |
| **Circular Dependencies** | Module A imports B, B imports A; build cycle linter flags it | "What happens if I move Order to a separate module?" | Extract shared kernel (interface or value object) or invert the dependency |

## Common Mistakes Candidates Make

1. **Confusing DTOs with anemic models.** A pure data-transfer object (`OrderDTO` for serialization at an API boundary) is *not* anemic; it has no behavior because it has no domain meaning. Anemic Domain Model applies to *domain entities* that have business rules but no methods. Don't push behavior into transport DTOs; do push behavior into domain entities.
2. **Over-correcting Primitive Obsession into value-object soup.** Wrapping every int in a class (`OrderQuantity`, `LineItemIndex`, `RetryCount`) creates ceremony without value. Use value objects only when the primitive carries *invariants* (validation, units, format) or *identity* (preventing cross-type joins).
3. **Splitting a God Class by *layer* instead of *reason*.** Splitting `ParkingLot` into `ParkingLotController`, `ParkingLotService`, `ParkingLotRepository` -- three classes that all change together -- is cosmetic, not structural. The split must be along reasons-to-change (allocation vs pricing vs notification), not along architectural layers.
4. **Calling Feature Envy a sin in *every* case.** Aggregates intentionally orchestrate across child entities. Order legitimately reads from its line items. The smell is when a method on A reads B's data *more than its own*. Count the access pattern before declaring envy.
5. **Treating Shotgun Surgery as a refactor, not a design test.** The fix is upstream: encapsulate the concept *before* the seven files exist. If the design has already smeared the concept, refactoring is expensive -- that's the lesson the interviewer is testing for.
6. **Hiding circular dependencies behind lazy imports.** `import Order` inside a method instead of at the top of the file silences the linter but doesn't fix the cycle. The build graph still has it; you've just made it invisible. Fix the structure, not the lint.

## Interview Walkthrough: Spotting Anti-Patterns Live

**Setup:** the interviewer asks you to design a parking lot. You sketch this:

```
class ParkingLot:
    def park(vehicle, payment_method): ...
    def calculate_fee(ticket): ...
    def charge(payment_method, amount): ...
    def send_receipt(email, ticket): ...
```

The interviewer asks: "Add a new pricing rule for monthly subscribers."

**Weak answer (walks into the trap):** "I'll add an `if vehicle.is_subscriber` branch in `calculate_fee`." -- you've just modified ParkingLot for a *new reason*. God Class confirmed. Interviewer follows up: "Now add SMS notifications." You modify ParkingLot again. God Class compounded.

**Strong answer (recognizes the trap):** "I notice my draft has ParkingLot owning allocation, pricing, billing, and notification -- that's a God Class. Let me decompose: SpotAllocator owns allocation, PricingEngine owns pricing as a Strategy (so I can add MonthlyPricing without touching existing code -- that's OCP), BillingService owns charging, NotificationService owns channels. ParkingLotService becomes a thin coordinator. Adding monthly pricing is a new MonthlyPricingStrategy implementing PricingStrategy, zero changes to existing classes."

Then probe themselves: "Also, I'd push invariants into the domain entities -- Ticket.close() should enforce that a ticket can't be closed twice rather than relying on the service to remember. That avoids the Anemic Domain Model. And I'd use Money instead of raw int for amounts, so no one mixes cents and dollars across the billing boundary -- that avoids Primitive Obsession."

This is a 10/10 answer because it (a) names the smells out loud, (b) explains *why* each fix is principled, not just stylistic, and (c) ties each to an interview-grade principle (OCP, rich domain, value objects).

## Interview Delivery Summary: What to Say When You See a Smell

Name the smell explicitly. Interviewers reward exact vocabulary because it signals you've engaged with the canonical literature (Fowler's *Refactoring*, *Clean Code*, *Object-Oriented Design Heuristics*).

- "This is starting to look like a God Class -- let me extract by reason-to-change."
- "My Order would be anemic if all rules lived in OrderService; I'll push cancel() and applyDiscount() into the entity so it owns its invariants."
- "I'd use Money(amount, currency) instead of int -- Primitive Obsession across service boundaries causes unit-confusion bugs that the type system can prevent."
- "calculateDiscount reads three fields off Customer -- that's Feature Envy. I'll move it to Customer or extract a DiscountPolicy."
- "If installment_count required edits in seven files, I'd encapsulate it as a Payment aggregate. Otherwise it's Shotgun Surgery."
- "User and Order can't import each other; I'll extract UserId as a value object so Order references the ID without depending on User."

**Staff signal:** end with "I'd wire madge / import-linter into CI to fail builds on new cycles, and run a metric like 'methods per class' or 'distinct change reasons per class' as a code-health KPI." -- connects the design principle to the production discipline that enforces it. Interviewers love this because it shows you don't just spot smells in interviews, you *prevent* them in real codebases.

## Interview Questions
1. Your draft has a single ParkingLot class with park(), calculateFee(), charge(), and sendReceipt(). The interviewer asks you to add a monthly subscriber pricing rule, then SMS notifications. Walk through how you would refactor your design as the requirements come in.
2. What is the Anemic Domain Model anti-pattern, why is it so easy to fall into, and how do you fix it? Cite the canonical reference.
3. Walk through how you would identify and fix Primitive Obsession in a payment system that passes amount as int and email as String across service boundaries. What value objects would you introduce, where would validation live, and what counterintuitive insight would you call out?
