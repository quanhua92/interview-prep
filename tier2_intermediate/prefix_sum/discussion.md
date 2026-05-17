# Prefix Sums & Hashing — Discussion

## One-Liner
Prefix sums convert subarray range-sum queries from O(n) to O(1), and hash maps eliminate the inner loop in two-pass subarray problems, together turning O(n^2) into O(n).

## Core Idea
Build a running cumulative sum array where `prefix[i]` = sum of all elements from index 0 to i-1. Any subarray sum `[i..j]` is answered in O(1): `prefix[j+1] - prefix[i]`. When combined with a hash map that stores previously seen prefix sums, you can solve "subarray sum equals K" in a single pass by checking whether `prefix[j] - k` was seen before.

## When to Recognize
Signal words that should trigger the prefix sum + hash pattern:
- "subarray sum equals k"
- "longest subarray with sum <= k"
- "find two numbers that sum to target"
- "count subarrays with property"
- "range sum" / "cumulative sum"
- "product of array except self"
- "number of subarrays" with a given property

## Key Techniques

### Prefix Sums
Precompute cumulative sums so any subarray sum `[i..j]` is `prefix[j+1] - prefix[i]`. Build in O(n), query in O(1).

### Hash Maps (Complement Search)
Store previously seen values (or their complements) so each element can be matched in O(1) instead of O(n) inner scan. For "subarray sum equals K": `sum(i..j) = prefix[j] - prefix[i-1] = k` rearranges to `prefix[i-1] = prefix[j] - k`. As we scan left to right, we ask "have we seen prefix[j] - k before?" in O(1) via a hash map.

### Combined: Prefix Sum + Hash
Initialize hash map as `{0: 1}`, meaning "we have seen a prefix sum of 0 once (before any elements)." This handles subarrays starting from index 0. Without this, subarrays like `[1,2,3]` where k=6 (the entire array) would be missed.

## Problem Type to Technique Mapping

| Problem Signal | Technique | Key Data Structure | Complexity |
|---|---|---|---|
| Find two elements summing to target | Complement hash | dict: value -> index | O(n) time, O(n) space |
| Count subarrays summing to k (with negatives) | Prefix sum + complement hash | dict: prefix_sum -> count | O(n) time, O(n) space |
| Max subarray sum (no constraint) | Kadane's algorithm | Two variables (current, global) | O(n) time, O(1) space |
| Longest subarray with sum <= k (non-negative) | Sliding window (variable) | Two pointers + running sum | O(n) time, O(1) space |
| Count elements in range [i..j] | Prefix frequency array | Array of cumulative counts | O(n) build, O(1) query |
| Group strings by anagram | Sorted-string hash key | dict: tuple -> list | O(n * m log m) time |
| Longest subarray with k distinct values | Sliding window + frequency map | dict: value -> count | O(n) time, O(k) space |

## Core Pattern Templates

### Pattern 1: Two Sum (find pair summing to target)
Store value -> index in a dict. For each element, check if `target - num` was seen earlier. No inner loop.

```python
def two_sum(nums: list[int], target: int) -> list[int]:
    seen = {}  # value -> index
    for i, num in enumerate(nums):
        complement = target - num
        if complement in seen:
            return [seen[complement], i]
        seen[num] = i
    return []
# O(n) time, O(n) space
```

### Pattern 2: Subarray Sum Equals K (count all subarrays)
Running sum + hash map of prefix sum frequencies. Initialize with `{0: 1}`.

```python
def subarray_sum(nums: list[int], k: int) -> int:
    count = 0
    running = 0
    seen = {0: 1}  # prefix_sum -> frequency
    for num in nums:
        running += num
        count += seen.get(running - k, 0)
        seen[running] = seen.get(running, 0) + 1
    return count
# O(n) time, O(n) space
```

### Pattern 3: Longest Subarray with At Most K Distinct Values
Sliding window with frequency map. Expand right, shrink left when distinct count exceeds k.

```python
def longest_subarray(nums: list[int], k: int) -> int:
    freq = {}
    left = max_len = 0
    for right, num in enumerate(nums):
        freq[num] = freq.get(num, 0) + 1
        while len(freq) > k:           # shrink window
            freq[nums[left]] -= 1
            if freq[nums[left]] == 0:
                del freq[nums[left]]
            left += 1
        max_len = max(max_len, right - left + 1)
    return max_len
# O(n) time, O(k) space, sliding window + hash
```

### Pattern 4: Group Anagrams
Use sorted string (or character count tuple) as hash key.

```python
def group_anagrams(strs: list[str]) -> list[list[str]]:
    groups = {}
    for s in strs:
        key = tuple(sorted(s))  # canonical form
        groups.setdefault(key, []).append(s)
    return list(groups.values())
# O(n * m log m), n strings, m avg length
# Better key: tuple of 26 char counts -> O(n * m)
```

## BOTIC Walkthrough (for "subarray sum equals K")

1. **B (Brute Force):** Check all O(n^2) pairs (i, j), compute sum from i to j. State this verbally: "Naive is O(n^2) with prefix sums, scanning all (i,j) pairs."
2. **O (Optimize):** Key insight: `sum(i..j) = prefix[j] - prefix[i-1] = k` rearranges to `prefix[i-1] = prefix[j] - k`. Use a hash map to look up whether this complement was seen before in O(1).
3. **T (Template):** Initialize hash map as `{0: 1}` for subarrays starting at index 0.
4. **I (Implement):** Single pass. Maintain running_sum. For each element: add num, check complement, update hash.
5. **C (Check):** Empty array -> count=0. All negatives -> hash still works. Duplicate prefix sums -> count-based hash handles multiple subarrays.

## Common Mistakes and Edge Cases

1. **Forgetting `{0: 1}` initialization:** Without it, subarrays starting from index 0 are missed. Always initialize `seen = {0: 1}` before the loop.
2. **Using prefix sums with negative numbers but assuming positivity:** Sliding window only works for non-negative numbers. With negatives, use prefix-sum + hash instead.
3. **Overwriting instead of accumulating in the hash map:** For subarray count problems, use `seen[key] = seen.get(key, 0) + 1`, not `seen[key] = 1`. Duplicate prefix sums each represent distinct valid subarrays.
4. **Off-by-one in prefix array indexing:** `prefix[0] = 0`, `prefix[i] = prefix[i-1] + nums[i-1]`. Subarray `[i..j]` (0-indexed) = `prefix[j+1] - prefix[i]`. Test with the full-array case manually.
5. **Mutating the input in place:** Never modify `nums` directly to build prefix sums. The interviewer may test with the same array multiple times. Use a separate `prefix` array or a running variable.

## Interview Communication Script

When you see a subarray or pair problem:
> "The naive approach is O(n^2), check all pairs. But I notice we can use a hash map to store previously seen values and answer 'have I seen X before' in O(1). Let me build this as a single-pass scan..."

When you initialize the hash map:
> "I'm initializing with {0:1}, this represents seeing a prefix sum of 0 before the array starts, which handles subarrays starting at index 0."

After coding:
> "Time complexity: O(n), one pass through the array, O(1) per element. Space: O(n), the hash map stores at most n distinct prefix sums. Edge cases: empty array returns 0, all-negative arrays work because we don't assume prefix sums are monotone."

## Key Variants
1. **Standard prefix sum** — range sum queries in O(1)
2. **Prefix sum + hash map** — count subarrays with sum K
3. **Prefix product** — product of array except self

## Follow-Up Questions
- What if you need to support point updates and range queries? (Answer: Fenwick tree / Binary Indexed Tree or Segment Tree)
- How would you handle 2D range sum queries? (Answer: 2D prefix sum, `sum(r1,c1,r2,c2) = D[r2+1][c2+1] - D[r1][c2+1] - D[r2+1][c1] + D[r1][c1]`)
- What if the array is too large for memory? (Answer: Process in blocks, use disk-backed prefix sums)
- How do you find the subarray with the maximum product? (Answer: Track both max and min at each position, since negative * negative = positive)

Source: [Prefix Sums & Hashing: Subarray Problems in O(n) (CalibreOS)](https://www.calibreos.com/learn/dsa-prefix-sums-hashing)
