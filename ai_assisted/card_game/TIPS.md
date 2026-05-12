# Tips: Card Game Logic

## Key Concepts to Know

- **Combinatorics** — Finding all 3-card subsets from a hand of N is `C(N, 3) = N! / (3! * (N-3)!)`. For N=5, that's only 10 combinations — brute force is fine.
- **Strategy Pattern** — Encapsulate each winning rule as a separate class implementing a common interface. Enables adding new rules without modifying existing code.
- **Seeded randomness** — Use `random.seed()` or `random.Random(seed)` for reproducible dealing.
- **Input validation** — Count occurrences with `collections.Counter` to detect illegal duplicates.

## Common Mistakes

| Mistake | Why It's Wrong |
|---------|---------------|
| Using `random.shuffle` on the hand instead of the deck | Deck must be shuffled before dealing |
| Counting the same combination in different orders | (1,5,9) and (5,1,9) are the same combination — use combinations, not permutations |
| Hardcoding the target value of 15 | The problem asks for configurable targets |
| Skipping validation of dealt hands | Allows impossible states (5 copies of the same card) |
| Not handling tie-breaking | Two players can have the same number of winning combinations |

## How to Prompt the AI Effectively

1. **Data model first:** "Define a Card class and a Deck class. The deck has 4 copies of cards 1-9, for 36 cards total."
2. **Core logic:** "Implement `evaluate(hand)` that returns all 3-card subsets summing to a target value. Use itertools.combinations."
3. **Extend rules:** "Now refactor using a strategy pattern. Create a Rule base class and implementations for SumRule and StraightRule."
4. **Verify correctness:** "What are all 3-card combinations from [1, 5, 9, 3, 7] that sum to 15?" — Manually verify: {1,5,9}=15 ✓, {5,3,7}=15 ✓, {1,5,3}=9 ✗, ...

## Design Patterns for Extensibility

```python
from abc import ABC, abstractmethod

class Rule(ABC):
    @abstractmethod
    def evaluate(self, hand: list[int]) -> list[tuple[int, ...]]:
        """Return all valid combinations for this rule."""
        ...

class SumRule(Rule):
    def __init__(self, target: int, size: int = 3):
        self.target = target
        self.size = size

    def evaluate(self, hand: list[int]) -> list[tuple[int, ...]]:
        return [
            combo for combo in combinations(hand, self.size)
            if sum(combo) == self.target
        ]

class StraightRule(Rule):
    def __init__(self, length: int = 3):
        self.length = length

    def evaluate(self, hand: list[int]) -> list[tuple[int, ...]]:
        # Check for consecutive sequences
        ...
```

## What Interviewers Look For

- Clean modeling of game entities (Card, Deck, Hand, Rule).
- Understanding of combinatorics and when brute force is acceptable (C(5,3)=10 is tiny).
- Extensibility via design patterns (strategy, rule engine) rather than if-else chains.
- Input validation as a first-class concern (illegal hands, impossible duplicates).
- Awareness of fairness/cheating in online games (cryptographic commitments).
