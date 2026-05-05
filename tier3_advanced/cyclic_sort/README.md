# Cyclic Sort

## Core Idea

Place each number at its correct index in a single pass. For an array containing numbers in the range [1, n] (or [0, n-1]), the number `i` belongs at index `i-1` (or index `i`). Swap elements into their correct positions until every element is where it belongs.

## When to Recognize

- Array of n numbers in range [0, n] or [1, n]
- "Find missing number", "find duplicate number"
- "Find all numbers disappeared in an array"
- "First missing positive"

## Complexity

- **Time**: O(n) -- each element is moved at most once
- **Space**: O(1) -- sort is done in place

## Template

```python
def cyclic_sort(nums):
    i = 0
    while i < len(nums):
        correct = nums[i] - 1          # where this number belongs
        if nums[i] != nums[correct]:
            nums[i], nums[correct] = nums[correct], nums[i]
        else:
            i += 1
    return nums
```

## Key Variants

1. **Cyclic sort**: Sort an array of 1..n in place using swaps.
2. **Find all numbers disappeared**: After cyclic sort, indices that don't match their value reveal missing numbers.
3. **Find the duplicate number**: Use the negation trick or Floyd's cycle detection to find duplicates without modifying the array.

## Problems

| Problem | Difficulty | Description |
|---------|-----------|-------------|
| P442 Find All Duplicates in an Array | Medium | Find all elements that appear twice |
| P268 Missing Number | Easy | Find the missing number in [0..n] |
