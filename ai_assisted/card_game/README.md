# Problem 05: Card Game Logic

**Role:** Software Engineer
**Duration:** 45-60 minutes
**Difficulty:** Medium
**Format:** Feature Build-Out

---

## Background

We're building an online card game called **"Sum十五" (Sum 15)**. Players are dealt a hand of numbered cards and compete to form combinations that sum to a target value. Your job is to implement the game's core evaluation engine.

## Rules

1. A standard deck has cards numbered 1-9, with 4 copies of each number (36 cards total).
2. Each player is dealt **N cards** (default: 5).
3. A **winning combination** is any subset of exactly **3 cards** from the player's hand that sum to the **target value** (default: 15).
4. A player can have zero, one, or multiple winning combinations in their hand.
5. The player with the **most distinct winning combinations** wins the round.

## Functional Requirements

1. Represent a deck of cards, a hand, and individual cards.
2. **Deal** cards from a shuffled deck to players.
3. **Evaluate** a hand and return all valid winning combinations (3-card subsets summing to the target).
4. **Compare** two or more hands and determine the winner (most winning combinations).
5. **Validate** that a hand is legal (no duplicates beyond what the deck allows).

## Non-Functional Requirements

- Card dealing should be random but reproducible with a seed.
- Evaluation should work for any hand size and any target value (configurable).
- The system must reject impossible states (e.g., five copies of the same card).

## Constraints

- Hand size: 2-10 cards.
- Target sum: any positive integer.
- No UI needed — this is the backend evaluation engine.

## Starter Interface

```python
class CardGame:
    def __init__(self, target: int = 15, hand_size: int = 5, seed: int | None = None):
        ...

    def deal(self, num_players: int) -> list[list[int]]:
        """Deal hands to N players from a shuffled deck. Returns list of hands."""
        ...

    def evaluate(self, hand: list[int]) -> list[tuple[int, int, int]]:
        """Find all 3-card combinations in the hand that sum to the target."""
        ...

    def winner(self, hands: list[list[int]]) -> int | None:
        """Return the index of the winning hand, or None if it's a tie."""
        ...

    def validate_hand(self, hand: list[int]) -> bool:
        """Check if a hand is legal (no more than 4 copies of any card number)."""
        ...
```

---

## Follow-Up Questions

### Follow-Up 1: Extensible Rules
> "We want to support different game modes. In 'Pair Mode', 2-card pairs summing to 10 also count. In 'Straight Mode', 3 consecutive cards (e.g., 3-4-5) count. How do you design for this?"

- Implement a **rule engine** or **strategy pattern** where rules are pluggable.
- Each rule is an object with a `evaluate(hand) -> list[Combination]` method.
- Multiple rules can be active simultaneously and their results merged.

### Follow-Up 2: Scoring System
> "Not all combinations are equal. A combination using three different numbers scores higher than one using duplicates. Design a scoring system."

- Assign weights to different combination types (e.g., all-distinct = 3 points, one-pair = 2 points).
- How does scoring change the comparison logic?
- Support configurable scoring rules.

### Follow-Up 3: Preventing Cheats
> "In an online game, players could submit tampered hands. How do you validate that a hand was actually dealt from a legitimate deck?"

- Cryptographic approach: hash the deck state + deal order with a server-side secret.
- How would you implement a **commit-reveal** scheme for fairness?
- What about detecting statistical anomalies over many rounds?

### Follow-Up 4: Tournament Mode
> "We want to run a 64-player tournament with elimination brackets. Design the tournament engine."

- Single elimination, double elimination, or round-robin?
- How do you handle ties in elimination rounds?
- Seeding strategy — should it be random or based on rankings?
