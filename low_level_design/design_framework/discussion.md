# LLD Interview Framework & Walkthrough

Source: [LLD Framework (CalibreOS)](https://www.calibreos.com/learn/lld-framework)

## One-Liner
A repeatable 5-step (SEDIE) framework for LLD interviews with a Parking Lot walkthrough demonstrating class diagrams, SOLID principles, and code.

## The 5-Step LLD Framework (SEDIE)

### Step 1: Clarify Scope (3-5 min)
- Ask: What actors use the system?
- What are the core use cases?
- Any constraints (concurrency, scale)?
- For Parking Lot: "Is this one lot or a network? What vehicle types? How is pricing structured?"

### Step 2: Extract Entities (5 min)
- Read the requirements.
- Every noun is a potential class.
- Every verb is a potential method.
- For Parking Lot: ParkingLot, Floor, ParkingSpot, Vehicle, Ticket, PricingStrategy.

### Step 3: Design Class Structure (10-15 min)
- Define classes, their attributes, and relationships.
- Use inheritance for is-a (CompactSpot is-a ParkingSpot).
- Use composition for has-a (ParkingLot has Floors).
- Define interfaces for extensibility points.

### Step 4: Implement Key Methods (15-20 min)
- Focus on the most interesting 2-3 methods that demonstrate design thinking.
- For Parking Lot: park(), leave(), findAvailableSpot().
- Show error handling and concurrency awareness.

### Step 5: Discuss Extensions (5 min)
- Proactively raise: "To add a new vehicle type, we'd just add a new Vehicle subclass, no changes to existing code."
- This demonstrates Open/Closed awareness.

## Parking Lot Core Implementation

```python
from abc import ABC, abstractmethod
from datetime import datetime
from enum import Enum
import threading
import uuid


class VehicleType(Enum):
    MOTORCYCLE = "motorcycle"
    CAR = "car"
    TRUCK = "truck"


class SpotType(Enum):
    COMPACT = "compact"    # motorcycles
    STANDARD = "standard"  # cars
    LARGE = "large"        # trucks


class Vehicle(ABC):
    def __init__(self, license_plate: str):
        self.license_plate = license_plate

    @property
    @abstractmethod
    def type(self) -> VehicleType: pass

    @property
    @abstractmethod
    def required_spot(self) -> SpotType: pass


class Car(Vehicle):
    @property
    def type(self): return VehicleType.CAR

    @property
    def required_spot(self): return SpotType.STANDARD


class Motorcycle(Vehicle):
    @property
    def type(self): return VehicleType.MOTORCYCLE

    @property
    def required_spot(self): return SpotType.COMPACT


class ParkingSpot(ABC):
    def __init__(self, spot_id: str, spot_type: SpotType):
        self.spot_id = spot_id
        self.spot_type = spot_type
        self._vehicle: Vehicle | None = None
        self._lock = threading.Lock()

    @abstractmethod
    def can_fit(self, vehicle: Vehicle) -> bool: pass

    def park(self, vehicle: Vehicle) -> bool:
        with self._lock:
            if self._vehicle or not self.can_fit(vehicle):
                return False
            self._vehicle = vehicle
            return True

    def leave(self) -> Vehicle | None:
        with self._lock:
            v = self._vehicle
            self._vehicle = None
            return v

    @property
    def is_available(self) -> bool:
        return self._vehicle is None


class StandardSpot(ParkingSpot):
    def can_fit(self, vehicle): return vehicle.required_spot == SpotType.STANDARD


class CompactSpot(ParkingSpot):
    def can_fit(self, vehicle): return vehicle.required_spot in (SpotType.COMPACT, SpotType.STANDARD)


class PricingStrategy(ABC):
    @abstractmethod
    def calculate_fee(self, ticket: "Ticket") -> float: pass


class HourlyPricing(PricingStrategy):
    RATES = {VehicleType.MOTORCYCLE: 1.0, VehicleType.CAR: 2.5, VehicleType.TRUCK: 4.0}

    def calculate_fee(self, ticket):
        hours = max(1, (ticket.exit_time - ticket.entry_time).seconds / 3600)
        return round(hours * self.RATES.get(ticket.vehicle.type, 2.5), 2)


class Ticket:
    def __init__(self, vehicle: Vehicle, spot: ParkingSpot):
        self.id = str(uuid.uuid4())[:8]
        self.vehicle = vehicle
        self.spot = spot
        self.entry_time = datetime.now()
        self.exit_time: datetime | None = None


class ParkingLot:
    _instance = None  # Singleton

    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self, spots: list[ParkingSpot], pricing: PricingStrategy):
        if hasattr(self, '_initialized'):
            return
        self.spots = spots
        self.pricing = pricing
        self.active_tickets: dict[str, Ticket] = {}
        self._initialized = True

    def park(self, vehicle: Vehicle) -> Ticket | None:
        for spot in self.spots:
            if spot.is_available and spot.can_fit(vehicle):
                if spot.park(vehicle):
                    ticket = Ticket(vehicle, spot)
                    self.active_tickets[ticket.id] = ticket
                    return ticket
        return None  # full

    def leave(self, ticket_id: str) -> float:
        ticket = self.active_tickets.pop(ticket_id, None)
        if not ticket:
            raise ValueError(f"Ticket {ticket_id} not found")
        ticket.exit_time = datetime.now()
        ticket.spot.leave()
        return self.pricing.calculate_fee(ticket)
```

## Concurrency Note

Always mention thread safety for LLD problems in interviews. Parking lots will have concurrent park() calls. The lock in ParkingSpot.park() ensures two threads can't park in the same spot simultaneously. At senior level, discuss optimistic locking vs pessimistic locking for different scenarios.

## SEDIE Deep Dive: What Each Phase Must Produce

SEDIE is not a checklist to recite; it is a sequence of **interview artifacts**. Each phase should leave something visible on the board or in code.

**Scope** produces an explicit boundary: in scope, out of scope, and assumptions. For a parking lot, "single facility, no reservations, hourly pricing, concurrent entry gates" is stronger than asking ten vague questions. Scope also names the archetype: resource allocation, workflow, domain-rich model, or concurrency primitive.

**Extract Entities** turns nouns into candidate classes, then deletes weak candidates. Keep entities that own state plus behavior: `ParkingSpot.reserve()` is real; `ParkingSpotType` is usually an enum. This phase is where candidates over-model. If a class has no lifecycle, no invariants, and no behavior, make it a value object or enum.

**Design Classes** chooses relationships and extension points. Say "has-a" for composition, "is-a" for true substitutability, and "uses-a" for services. Interfaces belong where requirements vary: pricing, matching, payment, notification, trigger calculation. Concrete classes are fine where the domain is stable.

**Implement Key Methods** means code the method with the most invariants, not every getter. Pick `park(vehicle)`, `claimNextRun()`, or `checkout()`. **Extensibility** closes the loop: show how the next feature is added with a new class, state transition, or strategy rather than rewriting the core flow.

## How to Narrate Tradeoffs During SEDIE

Strong LLD candidates narrate decisions at the moment they make them. In the **Scope** phase, say what you are excluding and why: "I will not model multi-lot routing yet because it changes the problem into inventory search; I will leave a `ParkingLotRepository` boundary for that extension." That prevents the interviewer from thinking you forgot it.

During **Entity Extraction**, explain rejected classes. "I am not making `ReceiptPrinter` part of the core domain; it is an output adapter behind `ReceiptSender`." This shows you can separate domain model from infrastructure. During **Design**, call out pattern pitfalls: "Strategy fits pricing because algorithms vary independently. Singleton is unnecessary here; a repository or dependency-injected `ParkingLot` is easier to test unless the problem explicitly requires one process-wide instance."

The **Implementation** phase is where concurrency belongs. If shared mutable state exists, identify the state and primitive before coding: "`spotsByType` and `activeTickets` are shared; I will guard spot allocation with a per-floor lock or optimistic DB update, not a global lock that serializes the entire lot." If the design is single-threaded by assumption, state that too.

The final **Extensibility** discussion should use concrete deltas: add EV spots, reservations, surge pricing, or multiple lots. For each change, name which class changes and which does not. That is how interviewers verify the design is actually open for extension.

## LLD Interviewer Scoring Rubric

| Signal | Weak answer | Strong answer | Why it matters |
|--------|------------|---------------|----------------|
| **Scope control** | Starts drawing classes immediately | Defines in/out scope and assumptions in 60-90 seconds | Prevents elegant but irrelevant designs |
| **Invariant thinking** | Explains classes but no correctness guarantees | Names invariants like one active ticket per spot and enforces them in code | Shows production-grade correctness mindset |
| **Concurrency judgment** | Mentions threads vaguely | Identifies shared mutable state and picks a concrete locking/optimistic strategy | Interviewers test race-condition awareness explicitly |
| **Extensibility proof** | Claims OCP without concrete changes | Demonstrates next feature as additive class/state transition with minimal edits | Separates pattern vocabulary from actual design quality |
| **Staff-level signal** | Pattern-name recital | Tradeoff narration with explicit rejections and failure modes | Distinguishes memorized prep from engineering judgment |

## 60-Second Interview Close for Any LLD Problem

I scoped the problem, modeled entities around invariants, implemented the highest-risk method, and validated concurrency plus extension paths. If we add a new feature, the design changes at extension points (strategy/state/repository) rather than the core flow. In production, I would next add tests around invariants, contention, and migration safety because those are the failure surfaces that break otherwise clean class diagrams.

## Why LLD Differs From HLD

Source: [How to Approach a LLD Interview (CalibreOS)](https://www.calibreos.com/learn/lld-how-to-approach)

LLD and HLD are graded on different rubrics. HLD asks "can you architect a distributed system?" -- sharding, replication, caching, queue choice, fan-out at scale. LLD asks "can you decompose a domain into objects that respect SOLID and accommodate change?" -- class boundaries, inheritance vs composition, pattern selection, concurrency primitives at the object level.

In HLD you move from numbers to architecture (140K reads/sec -> cache layer required). In LLD you move from requirements to entities (the noun "Vehicle" with two variation axes -> composition with FormFactor and FuelType fields). The mode of reasoning is **requirement signal -> SOLID principle -> pattern**, not pattern-first.

HLD probes: "what's the throughput?", "what fails when Redis goes down?", "how does this shard?". LLD probes: "what would break if we changed the pricing model?" (SRP), "how do you add a new vehicle type?" (OCP), "can MotorcycleSpot replace ParkingSpot wherever it's used?" (LSP), "how do you unit-test the lot without instantiating real pricing?" (DIP via constructor injection). Memorize these probe shapes -- they map directly to the SOLID principle the interviewer wants you to demonstrate.

In HLD you draw boxes that represent services. In LLD you draw classes that represent domain concepts. A service in HLD wraps multiple classes; a class in LLD lives inside one service. Don't conflate the boundaries -- drawing a "service-style" box in an LLD interview signals you're solving the wrong problem.

## The 7 Mindset Rules for LLD Interviews

**Rule 1: Treat the prompt as deliberately ambiguous.** "Design a parking lot" is intentionally vague. The interviewer is testing whether you ask about actors, scale, persistence, concurrency, and pricing rules, or fill in assumptions silently. Silent assumptions are the single most common L5+ failure. Always say: "Before I draw anything, is this one lot or a network? What vehicle types? Is the system multi-threaded? Is pricing flat-rate or time-based?"

**Rule 2: Nouns become candidates, not commitments.** When you scan requirements for nouns, every noun is a candidate class. Some survive (ParkingLot, Vehicle, Ticket); others collapse into attributes (color, license_plate). The exercise is to enumerate candidates, then defend which ones become classes via the "does it have identity and behavior?" test. Skipping this scan is how candidates miss BookItem-vs-Book or Account-vs-Transaction distinctions.

**Rule 3: Drive the conversation; do not wait to be led.** At minute 5 say: "Now that requirements are clear, I'll spend 5 minutes extracting entities, 10 minutes on the class diagram with key relationships, 15 minutes implementing the 2-3 most signal-rich methods, then 5 minutes on extensions -- does that work?" This signals ownership and lets the interviewer redirect early.

**Rule 4: Every class decision = 1 SOLID principle + 1 pattern.** Anchor each design choice to a principle: "PricingStrategy is an interface because OCP -- adding peak-hour pricing must not modify ParkingLot." Pattern naming follows: "so this is the Strategy pattern." Never name a pattern without naming the SOLID principle it serves.

**Rule 5: Pick 2-3 methods to implement, not all of them.** In 15 minutes of coding time, you can implement 2-3 methods well or 8 methods badly. Pick the signal-rich ones: methods with concurrency (park()), methods with strategy selection (calculateFee()), methods with state transitions (checkout()). Skip getters, setters, and toString(). Decline the trap: "I'll implement park() and calculateFee(); getters are boilerplate I'd auto-generate in real code."

**Rule 6: Surface concurrency, persistence, and testability unprompted.** Don't wait for "how do you make this thread-safe?" -- proactively say "park() needs a lock on the spot because two threads could see the same available spot." Same for persistence ("in production this state lives in Postgres; here I'm modeling in-memory") and testability ("PricingStrategy as an interface lets me inject a MockPricing in unit tests"). These are L5+ signals.

**Rule 7: Watch the clock; finish with extensions.** At minute 35 of a 45-minute interview, stop adding classes. Spend the last 5-7 minutes on extensions: "To add EV charging spots, I'd subclass ParkingSpot, zero changes to ParkingLot. To add a reservation system, I'd add a Reservation entity and a ReservationService -- Ticket and ParkingSpot are unchanged." This is where OCP signal is strongest, and most candidates skip it because they've over-invested in the implementation.

## LLD Anti-Patterns That Lose Points

| Anti-pattern | Why it costs points | Senior fix |
|-------------|-------------------|------------|
| Drawing a class diagram in the first 90 seconds | Signals you skip requirements gathering; explicit L5+ red flag | Spend 5 min asking actors, scale, persistence, concurrency before a single box |
| Conflating Book and BookItem (or Order and OrderLine) | Catalog-vs-instance confusion produces a schema that cannot model multiple copies | Run the noun scan and ask: "is this the catalog entry or a physical instance?" for every domain object |
| Embedding pricing logic inside ParkingSpot.calculateFee() | Violates SRP; pricing changes force ParkingSpot changes | Extract PricingStrategy as an interface; ParkingLot or PricingService composes it |
| Using inheritance for everything (Order extends Cart extends Item) | Deep hierarchies break LSP and create rigid coupling | Apply the is-a vs has-a test; default to composition unless the subtype is a true specialization |
| Naming patterns without naming the requirement | "Let me add a Factory here" without justification reads as pattern-matching | Always pair: requirement -> SOLID principle violated -> pattern that fixes it -> name |
| Returning null or -1 for error cases | Forces every caller to remember error checks; loses information | Throw typed exceptions: ParkingLotFullException, InvalidVehicleTypeException; show one try/catch at the caller |
| Ignoring concurrency in multi-actor systems | Every realistic LLD has concurrent access; ignoring it is a junior signal | Surface lock granularity proactively: "park() locks the spot, not the whole lot, so 100 threads can park in parallel" |
| Writing getters/setters/toString first | Burns coding time on boilerplate; signals you don't know which methods carry signal | Pick 2-3 methods that show design thinking; explicitly say "I'd auto-generate getters in real code" |
| Treating the diagram as final once drawn | When a new requirement surfaces a gap, candidates patch instead of restructuring | Be willing to erase: "this requirement breaks my hierarchy, let me revise" |
| Over-engineering with patterns the requirements don't justify | Adding Visitor or Chain-of-Responsibility for a 3-class system reads as cargo-culting | Apply the "rule of three": only introduce a pattern when the third instance of the same shape appears |

## The Most Expensive Mistake: Hierarchy Lock-In

The single highest-leverage failure mode in LLD interviews: committing to an inheritance hierarchy in the first 10 minutes and refusing to revise it when requirements surface a gap.

Example: you draw Vehicle <- Car, Truck, Motorcycle. At minute 25, the interviewer adds: "we also rent boats and snowmobiles, and pricing depends on whether the vehicle is electric, gas, or human-powered." Your hierarchy now needs two orthogonal axes (form-factor x power-source). Inheritance can encode one axis; the other becomes a tangle of subclasses (ElectricCar, GasCar, ElectricTruck, GasTruck...).

Cost: 5-10 minutes of recovery, plus the perception that you committed without anticipating multi-axis variation.

Fix: when a class has more than one variation axis, switch to composition with strategies. Vehicle has a PowerSource field (Electric, Gas, Human) and a FormFactor field (Car, Truck, Boat), both as enums or composed objects.

The meta-rule: **inheritance is for single-axis specialization. Composition is for multi-dimensional variation.** Recognize this signal in requirements: "vehicle type AND fuel type AND size class" -> composition. "Just vehicle type" -> inheritance is fine.

## Recovery Patterns When the LLD Goes Wrong

**You realize at minute 25 that your hierarchy is wrong.** Acknowledge cleanly: "Stepping back, the requirement you just added means my Vehicle hierarchy can't represent two variation axes. Let me revise to composition." Erasing and redrawing earns more credit than patching with conditionals. Interviewers explicitly grade for the willingness to revise under pressure.

**The interviewer asks "what pattern is this?" and you used one without naming it.** Name the pattern, then justify the requirement: "This is Strategy -- pricing has multiple algorithms (hourly, daily, peak-hour) that swap at runtime, and ParkingLot shouldn't change when we add tiered pricing, that's OCP." Linking pattern -> SOLID is the L5+ signal; naming alone is the L4 signal.

**The interviewer pushes back on a class boundary.** Do not defend; reason. Walk through the SRP test: "Ticket holds state (entry time, vehicle, spot). Lending coordinates the checkout transaction. They have different reasons to change. So I'd keep them separate." If the boundary is genuinely wrong, revise: "You're right, these have the same lifecycle and only one reason to change; merging them."

**You're asked to deep dive on a method you barely sketched.** 60 seconds to establish the contract first: "park() takes a Vehicle, returns a Ticket or throws ParkingLotFullException. The constraint is two threads cannot park in the same spot. Now the implementation..." This shows you don't dive into code without contract clarity.

**You're 5 minutes from the end with major gaps.** Don't try to cover everything -- explicit prioritization is itself the signal: "In the remaining 5 minutes, I'll do extensions since OCP is the highest-signal topic -- persistence and concurrency edge cases I'd cover next if we had more time." Naming what you're skipping demonstrates time-management judgment.

**You give a wrong answer and realize it 30 seconds later.** Self-correct out loud: "Actually, what I said about Singleton being thread-safe via new -- that's only safe with the GIL in CPython. In Java I'd need double-checked locking or an enum-based Singleton." Self-correction is a positive signal; it shows reflection. Pretending it didn't happen is far worse.

## The Decision Loop for Every Class

For each candidate class, run this loop audibly:

1. **Identity test**: Does this have a distinct lifecycle, or is it an attribute of something else?
2. **Behavior test**: Does it own methods beyond getters/setters, or is it a value object / enum?
3. **Invariant test**: Does it enforce rules (e.g., "one active ticket per spot"), or is it pure data?
4. **SRP test**: Does it have one reason to change, or am I mashing two concerns together?
5. **OCP test**: If I need to extend this (new vehicle type, new pricing tier), does the design let me add without modifying?
6. **Relationship decision**: Is this "is-a" (inheritance), "has-a" (composition), or "uses-a" (dependency)?

If the class fails identity or behavior, collapse it to an attribute or enum. If it fails SRP, split it. If the OCP test fails, introduce a strategy or interface at that boundary.

## What LLD Interview Levels Actually Test

| Level | Primary signal | How to demonstrate |
|-------|---------------|-------------------|
| L4 / Mid | Can you produce a working class diagram from a clear spec? | Correct entity extraction, basic SOLID adherence, one or two named patterns where they fit |
| L5 / Senior | Can you defend every design choice against SOLID and predict extension impact? | Pattern + SOLID linkage on every choice; concurrency surfaced unprompted; extensibility walkthrough at the end; willingness to revise |
| L6 / Staff | Can you identify the design choice that constrains future evolution and reason about it? | Names the *one* class boundary the rest of the design hinges on; debates inheritance-vs-composition explicitly; discusses testability and DI as first-class concerns |
| L7 / Senior Staff | Can you connect class-level decisions to system-level architecture? | Discusses how LLD decisions interact with HLD (sharding implications of an aggregate boundary; cache invalidation implications of an entity's lifecycle) |

## How to Practice (and What to Practice)

The wrong practice: memorizing canonical designs. Interviewers know these are memorized -- they ask variants ("parking lot with EV charging and reservations" or "elevator with VIP override") that punish recall and reward derivation.

The right practice: drill the 6 canonical LLD problems (Parking Lot, Elevator, Vending Machine, Library, Splitwise, ATM) deeply enough to **re-derive** them from requirements in 30 minutes.

Drill exercises:

- **Entity-extraction reflexes**: pick a one-paragraph requirement and produce the noun list, verb list, and survive/collapse decisions in under 5 minutes. Speed of extraction creates space for design thinking.
- **The SOLID self-check loop**: practice running it audibly for every class. After the design, walk through SRP, OCP, LSP, ISP, DIP and name where each applies (or where you traded it off).
- **Pattern -> requirement linkage**: for each commonly tested pattern, write the requirement signal that triggers it:

| Pattern | Requirement signal |
|---------|-------------------|
| Strategy | Multiple algorithms swap at runtime |
| Observer | Multiple listeners react to events |
| Factory | Creation logic varies by type |
| Builder | Object has many optional configuration parameters |
| Singleton | Exactly one process-wide instance is required |
| State | Object behavior changes based on internal state |
| Decorator | Add responsibilities dynamically without modifying the class |
| Template Method | Algorithm skeleton is fixed; individual steps vary |

- **Recovery drills**: have a friend ambush your design at minute 25 with a new requirement that breaks your hierarchy. Practice revising without panic.

What NOT to over-practice: writing complete UML for every class. In 45 minutes you'll draw 8-15 classes; complete UML for each is impossible. Prioritize the 3-4 classes that carry signal (the entity hierarchy and the strategy interfaces) and abbreviate the rest with names + key fields.

## Follow-Up Variations
- Walk me through designing a Library Management System from scratch in 45 minutes. What are the key classes and how do they interact?
- You're asked to add a "book recommendation" feature to the Library System. How do you design it without breaking existing classes?
- How do you handle concurrency in a Library System? Two members try to check out the last copy simultaneously.
