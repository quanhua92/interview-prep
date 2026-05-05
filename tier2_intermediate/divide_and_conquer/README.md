# Divide & Conquer

## Core Idea
Break the problem into smaller subproblems, solve each recursively, then combine the results. Classic example: merge sort divides an array in half, sorts each half, then merges them.

## When to Recognize
- "Sort an array" (merge sort, quick sort)
- "Merge k sorted lists"
- "Majority element"
- Problems that can be split into independent subproblems
- "Find kth largest/smallest" (quickselect variant)

## Complexity
- **Time:** O(n log n) for merge sort; O(n log k) for merge k sorted lists
- **Space:** O(n) for merge sort (or O(log n) auxiliary stack); O(n) for result

## Key Variants
1. **Merge sort** — divide, sort halves, merge in O(n log n)
2. **Boyer-Moore voting** — linear-time majority element (D&C-adjacent)
3. **Merge k sorted lists** — divide list of lists, merge pairs recursively

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 23 | [Merge k Sorted Lists](./problems/p023_merge_k_sorted_lists.py) | Hard |
| 912 | [Sort an Array](./problems/p912_sort_an_array.py) | Medium |
| 169 | [Majority Element](./problems/p169_majority_element.py) | Easy |

## Common Pitfalls
- Not handling the base case correctly (arrays of length 0 or 1).
- In merge sort, creating too many intermediate copies (use indices instead).
- For majority element, forgetting to verify the candidate (though LeetCode guarantees a majority exists).
