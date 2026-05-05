# Two Pointers

## Core Idea

Use two pointers that traverse the data structure. They can start from opposite ends and move toward each other, or start from the same end with one moving faster than the other. The key is that the pointers' movement is guided by a comparison, allowing O(n) processing.

## When to Recognize

Look for these keywords in the problem statement:

- Sorted array (or the array can be sorted without breaking the problem)
- "Find pair/triplet with sum", "two sum", "three sum"
- "Remove duplicates from sorted array"
- "Palindrome", "valid palindrome"
- "Container with most water", "trap rain water"
- In-place array modification without extra space

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| Two pointers from ends (sorted pair sum) | O(n) | O(1) |
| Two pointers from start (fast/slow removal) | O(n) | O(1) |
| Two pointers from ends (container problem) | O(n) | O(1) |

## Key Insight

For sorted arrays, moving a pointer inward is a deliberate decision based on whether the current sum/value is too high or too low. This eliminates one half of the remaining search space at each step -- similar to binary search but on two dimensions.

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P167 Two Sum II - Input Array Is Sorted | Medium | Two pointers from ends |
| P011 Container With Most Water | Medium | Two pointers from ends (greedy) |

## Template Variants

1. **Two pointers from ends** -- sorted array pair sum
2. **Two pointers from start** -- fast/slow for in-place removal
3. **Two pointers from ends** -- container problem (greedy area maximization)

See `template.py` for annotated skeleton code for each variant.
