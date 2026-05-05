# Modified Binary Search

## Core Idea

Adapt the standard binary search pattern for arrays that are rotated, contain duplicates, are unbounded, or where the answer lies in a monotonic predicate rather than a direct lookup. The key insight is always identifying which half to discard.

## When to Recognize

- "Search in rotated sorted array"
- "Find minimum/peak element"
- "Koko eating bananas", "split array largest sum", "capacity to ship packages"
- Any problem where the answer satisfies a monotonic condition (binary search on answer)

## Complexity

- **Time**: O(log n) for search, O(n log n) or O(log max_val) for binary-search-on-answer
- **Space**: O(1)

## Template

```python
def binary_search_on_answer(low, high, is_feasible):
    while low < high:
        mid = low + (high - low) // 2
        if is_feasible(mid):
            high = mid       # try for a smaller answer
        else:
            low = mid + 1    # need a larger answer
    return low
```

## Key Variants

1. **Search in rotated sorted array**: Determine which half is sorted, then check if target is in that half.
2. **Find peak element**: Compare mid with its neighbor to decide which half has a peak.
3. **Binary search on answer**: Define a predicate function `can(k)` that is monotonic, then binary search on `k`.

## Problems

| Problem | Difficulty | Description |
|---------|-----------|-------------|
| P033 Search in Rotated Sorted Array | Medium | Find target in a rotated sorted array |
| P875 Koko Eating Bananas | Medium | Minimize eating speed using binary search on answer |
