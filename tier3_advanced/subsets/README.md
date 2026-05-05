# Subsets / Permutations / Combinations

## Core Idea

Generate all subsets, permutations, or combinations of a collection. These problems share a common structure: at each step, you decide whether to include an element (subsets), where to place it (permutations), or which elements to pick (combinations). Both BFS and backtracking (DFS) approaches work.

## When to Recognize

- "All subsets", "power set"
- "All permutations", "next permutation"
- "Letter combinations of a phone number"
- "Generate all possible..."
- Problems asking for combinations that sum to a target

## Complexity

- **Subsets**: O(n * 2^n) time -- 2^n subsets, each up to size n
- **Permutations**: O(n * n!) time -- n! permutations, each of size n
- **Combinations**: O(C(n,k) * k) time
- **Space**: O(n) recursion depth (not counting output)

## Template (BFS approach for subsets)

```python
def subsets(nums):
    result = [[]]
    for num in nums:
        result += [curr + [num] for curr in result]
    return result
```

## Key Variants

1. **Subsets (BFS)**: Start with an empty set, for each number duplicate all existing subsets and add the number.
2. **Permutations (swapping)**: Swap elements into position, recurse, swap back.
3. **Letter combinations**: Map digits to letters, then recursively build combinations.

## Problems

| Problem | Difficulty | Description |
|---------|-----------|-------------|
| P046 Permutations | Medium | Generate all permutations of distinct integers |
| P090 Subsets II | Medium | Generate all subsets with duplicate elements |
| P077 Combinations | Medium | Choose k from n with start-index backtracking |
