# Prefix Sum

## Core Idea
Build a running cumulative sum array where `prefix[i]` = sum of all elements from index 0 to i-1. This allows O(1) range sum queries: `sum(i, j) = prefix[j+1] - prefix[i]`. Variants extend this concept with hash maps (for subarray counting) and products (for array products).

## When to Recognize
- "Subarray sum" / "range sum" / "cumulative sum"
- "Product of array except self"
- "Subarray sum equals K"
- "Number of subarrays" with a given property
- Any problem needing O(1) range queries on a static array

## Complexity
- **Time:** O(n) to build, O(1) per range query
- **Space:** O(n) for the prefix array

## Key Variants
1. **Standard prefix sum** — range sum queries in O(1)
2. **Prefix sum + hash map** — count subarrays with sum K
3. **Prefix product** — product of array except self

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 560 | [Subarray Sum Equals K](./problems/p0560_subarray_sum_equals_k.py) | Medium |
| 238 | [Product of Array Except Self](./problems/p0238_product_except_self.py) | Medium |
| 713 | [Subarray Product Less Than K](./problems/p0713_subarray_product_less_than_k.py) | Medium |
| 523 | [Continuous Subarray Sum](./solutions/p523_continuous_subarray_sum.py) | Medium |
| 525 | [Contiguous Array](./solutions/p525_contiguous_array.py) | Medium |
| 528 | [Random Pick with Weight](./solutions/p528_random_pick_with_weight.py) | Medium |

## Common Pitfalls
- Forgetting that `prefix[0] = 0` (off-by-one errors).
- Not initializing the hash map with `{0: 1}` when counting subarrays summing to K.
- Forgetting to handle edge cases like empty arrays or k=0.
