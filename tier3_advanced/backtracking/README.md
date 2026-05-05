# Backtracking

## Core Idea

Build candidates incrementally and abandon (backtrack) when a candidate cannot possibly lead to a valid solution. Think of it as exploring a decision tree: at each step, you make a choice, recurse deeper, and if the path leads to a dead end, you undo the choice and try the next option.

## When to Recognize

- "All permutations/combinations/subsets"
- "N-Queens", "Sudoku solver", "Word Search"
- "Generate all possible...", "find all..."
- Problems where you need to enumerate all valid configurations

## Complexity

- **Time**: Exponential in worst case -- O(k^n) where k is the branching factor and n is the depth
- **Space**: O(n) for the recursion stack (not counting output storage)

## Template

```python
def backtrack(candidate):
    if is_solution(candidate):
        output(candidate)
        return
    for next_candidate in expand(candidate):
        if is_valid(next_candidate):
            place(next_candidate)
            backtrack(next_candidate)
            remove(next_candidate)  # <-- the "backtrack" step
```

## Key Variants

1. **Permutations**: Swap elements in place, recurse, swap back
2. **Combinations (choose k from n)**: Use a `start` index to avoid revisiting earlier elements
3. **Subsets**: At each element, decide: include it or skip it

## Problems

| Problem | Difficulty | Description |
|---------|-----------|-------------|
| P078 Subsets | Medium | Generate all subsets of a set |
| P039 Combination Sum | Medium | Find all combinations that sum to target |
