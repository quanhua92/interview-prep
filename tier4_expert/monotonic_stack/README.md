# Monotonic Stack

## Core Idea
Maintain a stack whose elements are always in monotonic (increasing or decreasing) order. When a new element violates the monotonic property, pop elements from the stack until the property is restored, processing each popped element along the way.

## When to Recognize
- "Next greater element" / "next smaller element"
- "Daily temperatures"
- "Largest rectangle in histogram"
- "Remove K digits"
- "Trapping rain water" (variant)
- Any problem asking about nearest larger/smaller neighbor

## Complexity
- **Time:** O(n) — each element is pushed and popped at most once
- **Space:** O(n) — worst case stack holds all elements

## Key Variants
1. **Next greater element (ascending stack)** — find the next element larger than current
2. **Previous smaller element (descending stack)** — find the previous element smaller than current
3. **Sliding window maximum with monotonic deque** — maintain max in a sliding window

## Problems
- P739: Daily Temperatures
- P084: Largest Rectangle in Histogram
