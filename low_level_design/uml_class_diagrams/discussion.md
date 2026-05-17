# UML Class Diagrams

Source: [UML Class Diagrams (CalibreOS)](https://www.calibreos.com/learn/lld-uml-class-diagrams)

## One-Liner
Master UML class diagram notation, the six relationship types (inheritance, realization, composition, aggregation, association, dependency), multiplicity, visibility modifiers, and Mermaid syntax for LLD interviews.

## Why UML Class Diagrams Matter in LLD Interviews
Every senior LLD interview ends with the same instruction: "Draw the class diagram." The interviewer isn't asking for art, they're asking for a contract. A correctly drawn class diagram tells them, in 30 seconds, three things words cannot: which classes own which (composition vs aggregation), which classes know about which (dependency direction), and how many of each there are (multiplicity).

Verbal descriptions break down at the second relationship. By the time you've explained that *Library* has *Books*, *Members* borrow *Books*, *Books* contain *Authors*, and *Loans* link *Members* to *Books*, the interviewer has lost the topology. A diagram makes the topology immediate.

The interviewer is testing four things when they grade your diagram:
1. **Arrow direction**: do you know inheritance points from child to parent, dependency from caller to callee?
2. **Relationship choice**: composition vs aggregation, dependency vs association?
3. **Visibility**: do internal helpers leak as public?
4. **Completeness**: are multiplicities present, are abstract classes marked, are interfaces distinguished from concrete classes?

Most candidates fail one of these even when their *design* is correct. The design and the diagram are graded separately. The bar isn't just "produce a diagram", it's "produce a diagram a staff engineer could implement from without asking follow-up questions."

## What Earns Each Level (6/10, 8/10, 10/10)
- **6/10**: Draws boxes labeled with class names and connects them with plain arrows. Knows inheritance is an arrow but draws it backwards (parent to child). No visibility modifiers. No multiplicity. No distinction between composition and aggregation.
- **8/10**: Uses correct UML arrows for inheritance (hollow triangle, child to parent), composition (filled diamond), aggregation (hollow diamond). Marks visibility with `+`/`-`/`#`. Includes multiplicity at both ends of associations (1, *, 0..1). Distinguishes interfaces from classes (`<<interface>>` stereotype, dotted realization arrow). Draws a sequence diagram for at least one runtime flow.
- **10/10**: Reads Mermaid `classDiagram` syntax fluently and writes it from memory. Annotates abstract classes (italic name) and abstract methods. Uses dependency (dashed arrow) for transient uses (parameter, local variable) vs association (solid line) for held references. Picks composition vs aggregation by lifetime ownership argument ("books outlive a closed library, so it's aggregation"). Verbalizes the diagram while drawing.

## Class Notation Anatomy

### The Three-Compartment Class Box
- Top: class name (centered, bold).
- Middle: fields/attributes.
- Bottom: methods/operations.
- Empty compartments can be collapsed when not interesting, but the three-compartment structure is the canonical UML 2.5 form.
- In Mermaid: `class User { +String name; +login() }` automatically renders three compartments.

### Visibility Modifiers
- `+` = public (any class can access), `-` = private (only this class), `#` = protected (this class and subclasses), `~` = package-private (same package only).
- Default to `-` for fields and `+` for methods you intend to expose.
- Forgetting visibility signals junior; interviewers expect every field/method to declare it.

### Field and Method Signatures (`name: type` format)
- Fields: `- email: String`
- Methods: `+ login(password: String): Boolean`
- The colon-then-type is UML 2.5 standard. Return type goes last. Parameters are comma-separated.
- Mermaid uses the same format: `+login(password: String) Boolean`
- Avoid language-specific syntax (no Java `String email;` or Python `email: str`), UML is language-neutral.

### Static and Abstract Members
- Underline `nextId: int` to mark it static.
- Italicize `area(): double` to mark it abstract (the class itself is abstract if any method is).
- On a whiteboard, use a dotted underline for static and write `{abstract}` next to abstract methods.
- Mermaid uses `$` suffix for static (`+nextId$ int`) and `*` suffix for abstract (`+area()* double`).

### Interfaces (`<<interface>>` Stereotype)
- Interfaces are drawn as a normal class box with `<<interface>>` written above the class name (called a stereotype).
- All methods are implicitly public and abstract.
- In Mermaid: `class PaymentProcessor { <<interface>> +charge(amount: Double) Boolean }`
- The stereotype is what tells the reader "this is a contract, not a concrete class."

### Abstract Classes
- An abstract class differs from an interface: it can have fields, constructors, and concrete methods.
- Mark with italics on the class name and `{abstract}` constraint.
- Mermaid: `class Vehicle { <<abstract>> #plate: String +start()* void }`
- Use abstract classes when you have shared state (fields) plus abstract behavior; use interfaces when you only have a behavior contract.

## The Six Relationship Types

UML defines six relationships between classes. The interviewer is grading you on whether you pick the right one -- picking *composition* when you mean *aggregation* changes the contract by years.

1. **Inheritance (is-a, generalization)**: `Square` inherits from `Shape`. The arrow has a hollow triangle head and points *from child to parent*. The most common candidate mistake: drawing it backwards. The arrow follows the "is-a" direction.

2. **Realization (interface implementation)**: `StripePaymentProcessor` realizes the `PaymentProcessor` interface. Same hollow triangle, but the line is *dashed*. Distinguishes "implements an interface contract" from "extends a concrete parent."

3. **Composition (strong has-a, lifetime ownership)**: `House` is composed of `Rooms`. Filled diamond on the *owner's* end. The contained object cannot exist without the container: when the House is demolished, the Rooms cease to exist. Use composition when the child's lifecycle is bound to the parent.

4. **Aggregation (weak has-a, no lifetime ownership)**: `Library` has `Books`. Hollow diamond on the owner's end. The contained object exists independently: close the library, the books still exist. They can be transferred to another library. Use aggregation when the child outlives the parent or can move between parents.

5. **Association (uses-a, persistent reference)**: `Order` has a reference to `Customer`. Plain solid line, no diamond. Both objects are independent peers, neither owns the other, but they hold persistent references to each other. Add multiplicity (1, *, 0..1) to clarify cardinality.

6. **Dependency (uses-a, transient)**: `OrderService` depends on `Logger` (used as method parameter or local variable, not stored). Dashed line with open arrow. Weakest relationship: a brief, momentary use. If you'd remove the relationship by changing one method's signature, it's a dependency, not an association.

**The composition vs aggregation distinction is the single most-tested in LLD interviews.** The verbal test: *"if I delete the parent, must the child also be deleted?"* Yes -> composition. No -> aggregation. Library/Book: closing the library doesn't burn the books -> aggregation. Order/OrderItem: deleting the order deletes its line items -> composition.

## Relationship Symbols Cheat Sheet

| Relationship | Mermaid Syntax | UML Symbol | When to Use | Concrete Example |
|---|---|---|---|---|
| Inheritance (extends) | `Parent <|-- Child` | Solid line, hollow triangle on parent end | Child IS-A Parent. Reuse fields and methods. Use sparingly, favor composition over inheritance. | `Manager <|-- Engineer`, both are Employee subtypes |
| Realization (implements) | `Interface <|.. Class` | Dashed line, hollow triangle on interface end | Class fulfills an interface contract. Always for `<<interface>>` stereotyped types. | `PaymentProcessor <|.. StripeProcessor` |
| Composition (lifetime owned) | `Owner *-- Part` | Solid line, filled diamond on owner end | Part cannot exist without owner. Delete owner -> part is deleted. Strongest has-a. | `Order *-- OrderItem`; `House *-- Room` |
| Aggregation (loose has-a) | `Owner o-- Part` | Solid line, hollow diamond on owner end | Part has independent lifetime. Can be transferred between owners. | `Library o-- Book`; `Team o-- Player` |
| Association (knows-a) | `A --> B` | Solid line with open arrow (or no arrow if bidirectional) | Persistent reference between independent objects. Neither owns the other. | `Order --> Customer`; `Driver --> Car` |
| Dependency (uses-a) | `A ..> B` | Dashed line with open arrow | Transient use: parameter, local variable, return type. Not stored as a field. Weakest relationship. | `OrderService ..> Logger`; `ReportGenerator ..> Database` |

## Complete Mermaid Example: Parking Lot System

```yaml
classDiagram
    ParkingLot "1" *-- "*" Level : composition
    Level "1" *-- "*" ParkingSpot : composition
    ParkingSpot <|-- CompactSpot : inheritance
    ParkingSpot <|-- LargeSpot : inheritance
    ParkingSpot <|-- HandicappedSpot : inheritance
    Vehicle <|-- Car : inheritance
    Vehicle <|-- Truck : inheritance
    Vehicle <|-- Motorcycle : inheritance
    ParkingLot "1" o-- "*" Ticket : aggregation
    Ticket "1" --> "1" Vehicle : association
    Ticket "1" --> "1" ParkingSpot : association
    ParkingLot ..> PricingStrategy : dependency
    PricingStrategy <|.. HourlyPricing : realization
    PricingStrategy <|.. FlatRatePricing : realization

    class ParkingLot {
        -id: UUID
        -name: String
        -levels: List~Level~
        +parkVehicle(v: Vehicle) Ticket
        +unparkVehicle(t: Ticket) Receipt
        +findAvailableSpot(v: Vehicle) ParkingSpot
    }
    class Level {
        -floor: int
        -spots: List~ParkingSpot~
        +availableCount(type: SpotType) int
    }
    class ParkingSpot {
        <<abstract>>
        #spotId: UUID
        #isOccupied: Boolean
        +canFit(v: Vehicle)* Boolean
        +occupy(v: Vehicle) void
        +vacate() void
    }
    class CompactSpot {
        +canFit(v: Vehicle) Boolean
    }
    class LargeSpot {
        +canFit(v: Vehicle) Boolean
    }
    class HandicappedSpot {
        -permitRequired: Boolean
        +canFit(v: Vehicle) Boolean
    }
    class Vehicle {
        <<abstract>>
        #licensePlate: String
        #size: VehicleSize
    }
    class Car {
    }
    class Truck {
    }
    class Motorcycle {
    }
    class Ticket {
        -ticketId: UUID
        -entryTime: DateTime
        -spotId: UUID
        +duration() Duration
    }
    class PricingStrategy {
        <<interface>>
        +computeFee(duration: Duration) Money
    }
    class HourlyPricing {
        -ratePerHour: Money
        +computeFee(duration: Duration) Money
    }
    class FlatRatePricing {
        -flatRate: Money
        +computeFee(duration: Duration) Money
    }
```

## Multiplicity Notation

Multiplicity tells the reader *how many* objects participate at each end of a relationship. Without it, the diagram is ambiguous.

- `1`: exactly one (mandatory). Example: `Order "1" --> "1" Customer`, every order has exactly one customer.
- `0..1`: zero or one (optional). Example: `User "1" --> "0..1" PremiumSubscription`, a user may or may not have a subscription.
- `*` (or `0..*`): zero or more. Example: `Customer "1" --> "*" Order`, a customer can have any number of orders, including zero.
- `1..*`: one or more (at least one). Example: `Order "1" *-- "1..*" OrderItem`, every order must have at least one line item.
- `n..m`: between n and m. Example: `Team "1" --> "5..15" Player`, teams have between 5 and 15 players.

Multiplicity goes at *both ends* of the relationship, in quotes adjacent to the connecting line. The interviewer reads `Customer "1" --> "*" Order` as *"one customer has many orders, each order belongs to exactly one customer."* Forgetting multiplicity is the most common 6/10 to 8/10 gap.

A subtle but common mistake: candidates write `Order *-- OrderItem` without multiplicities, leaving the interviewer to ask whether an empty cart is allowed. State it: `Order "1" *-- "1..*" OrderItem` says "an order must have at least one item."

## Common Mistakes to Avoid

1. **Drawing inheritance arrows backwards.** The most frequent mistake. Inheritance points FROM child TO parent (the "is-a" direction). `Dog --|> Animal`, never `Animal --|> Dog`. Mermaid syntax: `Animal <|-- Dog` puts the parent first because the triangle is on the parent's side. If you reverse it, you've said "Animal is-a Dog", which is nonsense.

2. **Confusing composition with aggregation.** Filled diamond (`*--`) means the part dies with the whole; hollow diamond (`o--`) means the part survives. Library/Book is aggregation, books outlive the library. Order/OrderItem is composition, line items die with the order.

3. **Drawing the diamond on the wrong end.** The diamond goes on the *owner's* side, not the part's side. `Order *-- OrderItem` puts the diamond on Order (the owner). A diamond on the Item side would mean the item owns the order.

4. **Forgetting visibility modifiers.** A field without `+`/`-`/`#` defaults to "package-private" in UML, but interviewers read it as "candidate didn't bother." Always annotate. Default fields to `-` private and methods to `+` public.

5. **Omitting multiplicity.** `Order --> OrderItem` without multiplicities leaves the cardinality undefined. State it: `Order "1" *-- "1..*" OrderItem`.

6. **Treating interfaces like classes.** Without the `<<interface>>` stereotype, an interface looks identical to a concrete class. Always include `<<interface>>` (and use the dashed realization arrow `<|..` for implementations, not the solid inheritance arrow `<|--`).

7. **Mixing up dependency and association.** If A holds B as a field, that's association (solid line). If A only uses B in one method's parameter or local variable, that's dependency (dashed line). The test: would the relationship survive removing all storage of B in A? If yes, dependency. If no, association.

## Sequence Diagrams for Runtime Flows

Class diagrams show *static structure* -- what classes exist and how they relate. They don't show *what happens at runtime*. For that, use a **sequence diagram**.

Sequence diagrams have two axes. The horizontal axis lists actors and objects (the *participants*), usually drawn as boxes at the top with vertical dashed lines (called *lifelines*) descending. The vertical axis is time, top to bottom. Arrows between lifelines represent messages (method calls, returns, async events). Activations (thin rectangles on a lifeline) show when an object is "running."

The interview-relevant fragments:
- **`alt` / `else`**: branching: "if user is premium, charge discount price; else charge full price."
- **`loop`**: iteration: "for each item in cart, validate availability."
- **`opt`**: optional flow: "if customer is logged in, attach loyalty points."
- **`par`**: parallel flows: "send confirmation email AND push notification simultaneously."
- **Self-message**: an object calls its own method (arrow loops back to the same lifeline).
- **Return arrow** (dashed): the response message; often omitted for clarity in voids.

When to draw a sequence diagram in an LLD interview: *you almost always should*. After the class diagram, the interviewer typically asks "walk me through the happy path." A sequence diagram answers that visually. Pick the most interesting flow, usually the one that touches 4-6 classes. For a parking lot: `Customer arrives -> ParkingLot.parkVehicle() -> SpotFinder.find() -> Spot.occupy() -> Ticket created -> Customer receives ticket`. Each `->` is one message in your diagram.

The most common mistake: drawing every internal helper call. Sequence diagrams should show the public-method-level flow, not getter/setter calls. Aim for 8-15 messages covering the canonical flow.

## Whiteboard Drawing Tips

1. **Identify the central class first.** Usually the orchestrator or the entity at the center of the domain (ParkingLot, Library, Order). Place it center-board.

2. **Place subclasses below their parent, interfaces above implementations.** Inheritance arrows point up; realization arrows point up. Vertical alignment makes the hierarchy readable at a glance.

3. **Strategy/Policy classes go to the side.** PricingStrategy, NotificationStrategy, anything injected, sits at the right edge with a dependency or association arrow pointing back to the orchestrator.

4. **Composition relationships group together.** Order with its OrderItems should be visually adjacent; the composition diamond is easier to read when the parts cluster around the whole.

5. **Multiplicity in tiny text near the line ends.** Don't make multiplicity huge; it's annotation, not the focus.

6. **Verbalize while drawing.** Say *"User has-many Orders, each Order is-composed-of OrderItems"* as you draw each line. The interviewer is grading both your design and your communication.

7. **Use abbreviations consistently.** `+` `-` `#` for visibility; `1`, `*`, `0..1` for multiplicity; `<<I>>` shorthand for `<<interface>>` is acceptable on whiteboard. Don't invent symbols; interviewers expect UML standard notation.

## Interview Scenario: Drawing a Library Management System

Interviewer: *"Draw the class diagram for a library management system. I want to see the core entities and relationships."*

Strong walk-through (verbalized while drawing):

*"Let me start with the central entity, **Library**. A library has-many **Book**s, but I'll use aggregation (hollow diamond) because if the library shuts down, the books still exist physically; they could move to another library. So `Library "1" o-- "*" Book`."*

*"**Member** is the user. A member can borrow books, but borrowing isn't a permanent relationship; it's a transient transaction. I'll model **Loan** as its own class: `Member "1" --> "*" Loan` and `Loan "*" --> "1" Book`. The Loan has a borrowedAt and dueAt; it's an entity, not just a link."*

*"**Book** has an **Author**: `Book "*" --> "1..*" Author`. A book can have multiple authors; an author can write multiple books. That's actually many-to-many, so `Book "*" --> "*" Author`."*

*"For search, I'll add a **SearchService** with `..>` dashed dependency to **BookCatalog**; search uses the catalog but doesn't own it."*

*"Finally, fines. **Fine** is composed by the loan when overdue: `Loan "1" *-- "0..1" Fine`, composition because the fine doesn't exist outside the loan, and a loan has at most one fine."*

*"Visibility: Library, Book, Member, Loan are all public (`+` on methods). Internal helpers like Loan.computeOverdueDays() are private (`-`)."*

What this shows the interviewer: You picked **aggregation vs composition** with a verbalized lifetime argument (Library/Book vs Loan/Fine). You modeled **Loan** as a first-class entity rather than a join table -- the senior move. You used dependency for search, not association, because SearchService doesn't hold catalog state. You stated multiplicity on every relationship. Every choice was justified out loud.

## What to Say During the Interview

Phrases that signal mastery:

- *"I'll use **composition** here because [Part] cannot exist outside [Whole] -- if I delete the Order, the OrderItems are meaningless."*
- *"This is **aggregation**, not composition -- [Books] outlive the [Library] and can move between branches."*
- *"This is a **dependency**, not an association -- [OrderService] only uses [Logger] as a method parameter; it doesn't store it."*
- *"I'll mark this as the **`<<interface>>`** [PaymentProcessor], concrete implementations like [StripeProcessor] realize it via the dashed arrow."*
- *"The multiplicity is **`1..*`**, not `*` -- the business rule says an order must have at least one line item; empty orders aren't valid."*
- *"This method is **abstract** -- every [ParkingSpot] subtype must implement `canFit(vehicle)` differently."*
- *"I prefer **composition over inheritance** here -- instead of `PremiumUser extends User`, I'll model [User] with an injected [SubscriptionPlan] strategy."*
- *"Let me draw a **sequence diagram** for the happy path so we can see how these classes collaborate at runtime."*

These phrases are interview shibboleths -- staff engineers say them automatically; juniors don't know they exist. Using them while drawing tells the interviewer you've internalized UML semantics, not just memorized arrow shapes.
