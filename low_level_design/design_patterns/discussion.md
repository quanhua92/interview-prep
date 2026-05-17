# Design Patterns for LLD Interviews

Source: [Design Patterns (CalibreOS)](https://www.calibreos.com/learn/lld-design-patterns)

## One-Liner
The 7 most frequently tested design patterns in LLD interviews -- know which pattern to reach for and why.

## How Patterns Appear in Interviews
Interviewers don't ask "implement the Strategy pattern." They ask "design a parking lot" and then evaluate whether you naturally reach for Strategy for pricing, Factory for spot creation, and Singleton for the lot itself. Patterns are the vocabulary; you demonstrate mastery by using them correctly without being prompted.

## The 7 Essential LLD Patterns

### 1. Strategy -- Interchangeable Algorithms
- Define a family of algorithms, encapsulate each, make them interchangeable.
- Use: parking lot pricing (hourly vs daily), sorting algorithms, payment methods.
- Signal: "we need multiple ways to do X."

### 2. Factory / Factory Method -- Object Creation
- Centralize object creation logic.
- Use: creating the right Spot subtype (Compact/Standard/Large), creating the right Piece in Chess.
- Signal: "create an object based on a type."

### 3. Observer -- Event Notification
- Define a one-to-many dependency.
- When one object changes state, all dependents are notified automatically.
- Use: elevator floor panels, stock ticker subscribers.
- Signal: "notify multiple listeners when X happens."

### 4. Singleton -- Single Instance
- Ensure a class has exactly one instance with global access.
- Use: ParkingLot (one lot in the system), configuration manager, logger.
- Signal: "there should only be one X."
- Be careful -- overused, hides dependencies.

### 5. State -- Object Behavior Based on State
- Allow an object to alter behavior when internal state changes.
- Use: Elevator (IDLE/MOVING/DOORS_OPEN), Order (PLACED/CONFIRMED/SHIPPED/DELIVERED), Traffic Light.
- Signal: "behavior changes based on current state."

### 6. Decorator -- Dynamic Behavior Extension
- Attach additional responsibilities to objects dynamically.
- Use: adding encryption to a file writer, adding logging to a data source.
- Signal: "wrap an object to add behavior without changing the class."

### 7. Builder -- Complex Object Construction
- Separate the construction of a complex object from its representation.
- Use: constructing HTTP requests, database queries, complex configuration objects.
- Signal: "object needs many optional parameters."

## Key Design Decisions

### Strategy Pattern -- Parking Lot Pricing
```python
from abc import ABC, abstractmethod
from datetime import datetime

class PricingStrategy(ABC):
    @abstractmethod
    def calculate_fee(self, entry: datetime, exit: datetime, vehicle_type: str) -> float:
        pass

class HourlyPricing(PricingStrategy):
    RATES = {"Motorcycle": 1.0, "Car": 2.0, "Truck": 3.5}

    def calculate_fee(self, entry, exit, vehicle_type):
        hours = max(1, (exit - entry).seconds / 3600)
        return hours * self.RATES.get(vehicle_type, 2.0)

class FlatRatePricing(PricingStrategy):
    def calculate_fee(self, entry, exit, vehicle_type):
        return 15.0  # flat day rate

class PeakHourPricing(PricingStrategy):
    def __init__(self, base: PricingStrategy):
        self.base = base  # Decorator + Strategy combo

    def calculate_fee(self, entry, exit, vehicle_type):
        fee = self.base.calculate_fee(entry, exit, vehicle_type)
        return fee * 1.5 if 8 <= entry.hour <= 18 else fee

# Usage: swap strategies without changing ParkingLot
lot = ParkingLot(pricing_strategy=HourlyPricing())
lot = ParkingLot(pricing_strategy=PeakHourPricing(HourlyPricing()))
```

### Observer Pattern -- Elevator Notification
```python
from abc import ABC, abstractmethod

class ElevatorObserver(ABC):
    @abstractmethod
    def on_floor_change(self, elevator_id: int, floor: int): pass

    @abstractmethod
    def on_doors_open(self, elevator_id: int, floor: int): pass

class FloorPanel(ElevatorObserver):
    def __init__(self, floor: int):
        self.floor = floor

    def on_floor_change(self, elevator_id, floor):
        if floor == self.floor:
            print(f"Elevator {elevator_id} arrived at floor {self.floor}")

    def on_doors_open(self, elevator_id, floor):
        if floor == self.floor:
            print(f"Doors open on floor {self.floor}")

class Elevator:
    def __init__(self, id: int):
        self.id = id
        self._floor = 0
        self._observers: list[ElevatorObserver] = []

    def add_observer(self, obs: ElevatorObserver):
        self._observers.append(obs)

    def move_to(self, floor: int):
        self._floor = floor
        for obs in self._observers:
            obs.on_floor_change(self.id, floor)
```

### Strategy Plus Decorator Without a Switch Statement
```typescript
type VehicleType = "CAR" | "TRUCK";

interface PricingStrategy {
  calculate(entry: Date, exit: Date, vehicle: VehicleType): number;
}

class HourlyPricing implements PricingStrategy {
  constructor(private readonly rates: Record<VehicleType, number>) {}

  calculate(entry: Date, exit: Date, vehicle: VehicleType): number {
    const hours = Math.ceil((exit.getTime() - entry.getTime()) / 3_600_000);
    return Math.max(1, hours) * this.rates[vehicle];
  }
}

class WeekendDiscount implements PricingStrategy {
  constructor(
    private readonly wrapped: PricingStrategy,
    private readonly discountPercent: number
  ) {}

  calculate(entry: Date, exit: Date, vehicle: VehicleType): number {
    const base = this.wrapped.calculate(entry, exit, vehicle);
    const isWeekend = [0, 6].includes(exit.getDay());
    return isWeekend ? base * (1 - this.discountPercent / 100) : base;
  }
}

const pricing: PricingStrategy = new WeekendDiscount(
  new HourlyPricing({ CAR: 4, TRUCK: 8 }),
  20
);
```

## Pattern Quick Reference
| Pattern | Problem Solved | LLD Problem Example |
|---------|---------------|---------------------|
| Singleton | Single shared instance | ParkingLot, Logger, Config |
| Factory | Create objects by type | ParkingSpot, ChessPiece, Vehicle |
| Strategy | Swap algorithms at runtime | Pricing, Dispatch, Sorting |
| Observer | Notify multiple dependents | Elevator panels, Event systems |
| State | Behavior changes with state | Elevator, Order, Traffic Light |
| Decorator | Add behavior without subclassing | Logging, Encryption wrappers |
| Builder | Construct complex objects | HTTP Request, Query Builder |

## Deep Dive Topics
- Pattern selection is about the axis of change: before naming a pattern, say which part of the design must vary independently
- Pricing varies independently from parking allocation, so Strategy fits
- Object subtype selection varies independently from callers, so Factory fits
- A sequence of optional behaviors varies at runtime, so Decorator fits
- An object changes behavior across lifecycle states, so State fits
- Strategy buys OCP but introduces more classes; Decorator avoids subclass explosion but can make debugging wrapper chains harder; Observer decouples publishers but makes ordering and failure handling explicit responsibilities
- Name the upside and the maintenance cost in the same answer

## Follow-Up Variations
- In a parking lot system, you need to support multiple pricing strategies (hourly, flat rate, weekend discount). Which design pattern do you use and why? Show the class structure.
- Implement the Observer pattern for a parking lot notification system. How does it differ from polling?
- When would you use the State pattern vs. a simple if-else state machine? Design the ticket state machine for a parking lot.
