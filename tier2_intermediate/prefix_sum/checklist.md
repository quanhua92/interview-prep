# Prefix Sums & Hashing — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Identify the Pattern (1-2 min)
- [ ] Read the problem statement and identify signal words:
  - [ ] "subarray sum equals k" / "range sum" / "cumulative sum"
  - [ ] "find two numbers that sum to target"
  - [ ] "count subarrays with property"
  - [ ] "longest subarray with constraint"
- [ ] Classify the problem type:
  - [ ] Two-sum variant (find pair) -> complement hash
  - [ ] Subarray sum equals K (with negatives) -> prefix sum + hash
  - [ ] Max subarray sum -> Kadane's
  - [ ] Longest subarray with sum constraint (non-negative) -> sliding window
  - [ ] Group by property (anagrams) -> hash with canonical key
- [ ] State the brute force complexity: "Naive is O(n^2) checking all pairs"

## Phase 2: Brute Force (2-3 min)
- [ ] Describe the O(n^2) or O(n^3) brute force approach:
  - [ ] For subarray sum: check all O(n^2) pairs (i, j), compute sum in O(n) each
  - [ ] With precomputed prefix sums: O(n^2) pairs, O(1) per query -> O(n^2) total
- [ ] Write or sketch the brute force (briefly, 3-5 lines)
- [ ] State: "This is O(n^2), we can optimize using a hash map"

## Phase 3: Optimize with Prefix Sum + Hash (3-5 min)
- [ ] Explain the key mathematical insight:
  - [ ] `sum(i..j) = prefix[j] - prefix[i-1] = k`
  - [ ] Rearranges to: `prefix[i-1] = prefix[j] - k`
  - [ ] For each position j, ask "have we seen prefix[j] - k before?" in O(1)
- [ ] Explain the data structure choice:
  - [ ] Hash map: `{prefix_sum: frequency}` for counting subarrays
  - [ ] Hash map: `{value: index}` for two-sum pair finding
- [ ] Discuss the critical initialization:
  - [ ] Initialize hash map with `{0: 1}` for prefix-sum problems
  - [ ] Explain why: handles subarrays starting from index 0
- [ ] Present the optimized algorithm:
  - [ ] Single pass, maintain running_sum
  - [ ] For each element: running_sum += num
  - [ ] Check if complement (running_sum - k) exists in hash map
  - [ ] Update hash map with current running_sum

## Phase 4: Implement (5-8 min)
- [ ] Write clean, compilable code:
  - [ ] Correct function signature with type hints
  - [ ] Initialize hash map with `{0: 1}` (prefix sum problems) or `{}` (two-sum)
  - [ ] Single pass loop with running_sum
  - [ ] Check complement BEFORE updating hash map (important ordering)
  - [ ] Update hash map after the check
- [ ] Handle edge cases proactively:
  - [ ] Empty array -> return 0 (count) or [] (pairs)
  - [ ] Single element -> check if element itself equals k
  - [ ] All negative numbers -> prefix sums decrease, hash still works
  - [ ] k = 0 -> subarrays summing to zero; {0:1} handles full-array case
  - [ ] Duplicate prefix sums -> count-based hash handles multiple subarrays

## Phase 5: Test and Verify (2-3 min)
- [ ] Trace through a small example manually:
  - [ ] Example: nums = [1, 1, 1], k = 2 -> expected: 2
  - [ ] Example: nums = [1, 2, 3], k = 3 -> expected: 2 ([1,2] and [3])
- [ ] Verify off-by-one correctness:
  - [ ] prefix[0] = 0 (empty prefix)
  - [ ] prefix[i] = prefix[i-1] + nums[i-1]
  - [ ] Subarray [i..j] = prefix[j+1] - prefix[i]
- [ ] State complexity from first principles:
  - [ ] Time: O(n) — single pass, O(1) per element for hash lookup
  - [ ] Space: O(n) — hash map stores at most n distinct prefix sums

## Phase 6: Extensions and Follow-Ups (2-3 min)
- [ ] Discuss how the approach handles variants:
  - [ ] What if we need the longest subarray instead of the count? (Store index instead of count)
  - [ ] What if numbers are non-negative only? (Sliding window is better, O(1) space)
  - [ ] What if we need to support updates? (Fenwick tree or segment tree)
  - [ ] 2D prefix sum for matrix range queries?
- [ ] Compare with alternative approaches:
  - [ ] Kadane's for max subarray (O(1) space but only finds max, not count)
  - [ ] Sliding window for non-negative numbers (O(1) space, but fails with negatives)

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:

Source: [Prefix Sums & Hashing: Subarray Problems in O(n) (CalibreOS)](https://www.calibreos.com/learn/dsa-prefix-sums-hashing)
