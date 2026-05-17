# Two Pointers -- Discussion

## One-Liner
Use two pointers to exploit directional structure in sorted or sortable data, eliminating search space deterministically in O(n) time with O(1) space.

## Why Arrays and Strings Matter Most
Arrays and strings are the highest-frequency entry point for DSA interviews at Google, Meta, Amazon, and Microsoft. They are where interviewers evaluate core execution signals: pattern recognition speed, communication clarity, edge-case discipline, and complexity derivation under time pressure.

Most first-round coding screens start here because arrays/strings expose whether your process is systematic or ad-hoc. A candidate who cannot clearly reason about index boundaries, duplicates, and invariants in this space is unlikely to handle advanced graph or DP rounds.

## What Interviewers Evaluate

| Score | Description |
|-------|-------------|
| **6/10 (borderline pass)** | Gets to a working solution but only after trial-and-error coding, weak edge-case testing, and hand-wavy complexity statements. |
| **8/10 (strong pass)** | Names the right pattern in under 5 minutes, gives a clear brute-force baseline, then derives the optimized invariant before coding. |
| **10/10 (hire-leaning)** | Runs BOTIC with explicit checkpoints, proactively validates boundary conditions (`n=0`, duplicates, all-same/all-unique), and explains *why* complexity is O(n) when there is an inner while loop (amortized pointer movement). |

## BOTIC for Arrays and Strings

### B -- Brute Force (3-5 min)
State the straightforward solution first (often nested loops or restart-per-index scan). Derive its complexity explicitly and identify repeated work.

### O -- Optimize (5-8 min)
Choose the right pattern family: hash map, two pointers, sliding window, or prefix sums. State the invariant before writing code.

### T -- Template (2-3 min)
Write variable scaffolding first (left/right, counts, result, prefix map). This prevents mid-implementation drift.

### I -- Implement (10-15 min)
Code incrementally while narrating pointer/state updates. Keep each line tied to the invariant.

### C -- Check (3-5 min)
Manually trace happy path plus edge cases: empty input, single element, duplicate-heavy input, and tricky boundary cases.

## Two Pointers: Deep Dive and Variants

Two pointers exploit **directional structure** in sorted or sortable inputs to eliminate search space deterministically. The key insight: sorted order lets you rule out half the remaining candidates with each pointer move.

### Variant 1: Converging Pointers (Opposite Ends)
Start left at 0, right at n-1, move based on comparison to target.
- **Classic use:** pair sum in sorted array, container with most water, trapping rain water
- **Invariant:** all pairs outside `[left, right]` have been eliminated

### Variant 2: Fast-Slow Pointers (Same Direction)
Both start at 0, fast advances every iteration, slow advances conditionally.
- **Classic use:** remove duplicates in-place, partition arrays (Dutch National Flag), Floyd's cycle detection
- **Invariant:** `[0...slow)` is the valid processed region

### Variant 3: Sliding-Width Pointers
Both move right, distance between them varies based on validity check.
- **Classic use:** substring problems where window expands/contracts
- Overlaps with sliding window for contiguous ranges

### When to Use Two Pointers vs Alternatives
- Use over nested loops when sorted order provides directional elimination (reduces O(n^2) -> O(n))
- Use over hash map when O(1) space is required or when sorted structure is already given
- Avoid when order is semantically meaningless (e.g., grouping anagrams where letter order doesn't map to value order)

### Common Implementation Mistakes
- Moving both pointers simultaneously when only one should move based on comparison
- Not handling equal-value runs correctly in duplicate-heavy inputs
- Off-by-one errors when pointers can cross vs when they should stop at `left < right`
- Forgetting to advance slow pointer in fast-slow variants, causing infinite loops

## Pattern Selection Quick Reference

| Prompt Signal | Pattern | Invariant | Typical Complexity |
|---------------|---------|-----------|--------------------|
| longest/shortest substring with constraint | Sliding Window | Window is valid after contraction | O(n) |
| pair sum in sorted input | Two Pointers | Eliminate one side each move | O(n) |
| count/group by characters or values | Hash Map | Map tracks exact frequency state | O(n) |
| subarray sum equals k | Prefix Sum + Map | Store prior prefix frequencies | O(n) |
| in-place partition or deduplicate sorted array | Two Pointers | Left side is processed/valid region | O(n) |
| anagram/permutation checks | Frequency Count | All counts net to zero | O(n) |

## Complexity Analysis: Amortized Reasoning

### Variable-size sliding window
Has a `for` loop with a nested `while` loop -- looks like O(n^2), but is actually O(n).
- **Accounting argument:** Right pointer advances exactly n times (outer loop). Left pointer only moves forward, never resets. Each element is added to window once and removed at most once. Total pointer movements: <= 2n.
- **What to say in interviews:** "Right pointer visits each index once for n total moves. Left pointer also moves only forward and visits each index at most once, so at most n moves total. Combined 2n pointer movements with O(1) work per movement gives O(n) overall."

### Two-pointer complexity
Most two-pointer solutions are O(n) because each pointer moves at most n times and doesn't reset. Exception: nested two-pointer variants (e.g., 3Sum with outer loop and inner two-pointer) are O(n^2) because of the outer loop multiplier.

### Hashing complexity subtleties
Hash map operations are O(1) **average case**, but O(n) worst case with poor hash function or adversarial input. In interview settings, assume average case unless asked. Mention: "In practice O(1) average with good hash functions; worst-case O(n) with hash collisions, but Python's dict uses robust hashing."

## Failure Modes That Cause Rejection

1. **Confusing substring with subsequence:** Substring is contiguous; subsequence is not. This changes the pattern family completely.
2. **Off-by-one window length:** For inclusive `[left, right]`, size is `right - left + 1`, not `right - left`.
3. **Incorrect duplicate boundary handling:** In index-jump sliding window variants, move left only when last occurrence is inside current window.
4. **Weak complexity reasoning:** Saying "single pass so O(n)" without amortized explanation is not enough when an inner while loop exists.
5. **No edge-case protocol:** Candidates who never test empty, single-element, and all-duplicate inputs are treated as unreliable under production pressure.

## Interview Script

Use this structure out loud: *"I will start with a brute-force baseline, identify repeated work, then switch to the optimal pattern with an invariant. After coding, I'll trace one example and then run edge cases."*

For complexity, say: *"Right pointer moves n times, left pointer moves at most n times total, so total pointer moves are <= 2n, which is O(n)."* That single sentence often differentiates senior-caliber communication.

## Worked Example: Container With Most Water

**Pattern:** Two pointers (converging from ends)
**Brute force:** Try all pairs O(n^2)
**Optimization insight:** Area is limited by shorter line. If we move the pointer at the shorter line inward, we might find a taller line that increases area. Moving the taller line pointer can only decrease area (width decreases, height can't improve).
**Invariant:** All pairs outside `[left, right]` have been eliminated as suboptimal.
**Complexity:** O(n) time, O(1) space. Each pointer moves at most n times total.
**Edge cases:** two bars only, all same height, extreme heights [1, 100, 1].

## Worked Example: Product of Array Except Self

**Pattern:** Prefix products from left and right
**Brute force:** For each index, multiply all others O(n^2)
**Optimization insight:** Product except self = (product of all elements to the left) x (product of all elements to the right). Compute left products in one pass, right products in second pass.
**Complexity:** O(n) time, O(1) extra space (output array doesn't count).
**Edge cases:** single element, contains zero, all ones, negative numbers.

Source: [Arrays and Strings: Core Interview Patterns and Execution Strategy (CalibreOS)](https://www.calibreos.com/learn/dsa-arrays-strings)

---

## Additional Insights: Three Distinct Invariants and Floyd's Cycle Detection

Source: [Two Pointers: Converging, Fast/Slow, and Floyd's Cycle Detection (CalibreOS)](https://www.calibreos.com/learn/dsa-two-pointers)

### The Three Variants Are Separate Techniques, Not One Pattern

Two pointers is not a single pattern but a family of three distinct techniques, each with a different invariant and a different class of problems. Conflating them, or knowing only one, is a common interview failure mode.

**Converging (opposite ends):** `left` starts at index 0, `right` starts at the last index. They move toward each other. Invariant: `left < right`. The mechanism: you can skip large portions of the search space because the array is *sorted* -- if `arr[left] + arr[right] > target`, moving `right` left is safe because any element to the right of `right` would make the sum even larger.

**Same-direction (fast/slow):** Both pointers start at the beginning and move rightward, but at different speeds or triggered by different conditions. The invariant: everything to the left of the slow pointer satisfies some property (e.g., is a unique element), and the fast pointer scans ahead to find the next element that should be placed at slow.

**Floyd's cycle detection (hare/tortoise):** One pointer moves one step per iteration, the other moves two. Used exclusively on linked list structures where you cannot compute length or use indexing.

### What Interviewers Probe Beyond Mechanics

1. Can you prove *why* the converging approach is safe -- why moving the smaller-max pointer in trapping rain water gives the correct answer, not just a greedy heuristic?
2. Can you explain Floyd's phase 2 math -- why resetting one pointer to the head and advancing both at the same speed finds the cycle entry? Candidates who say "I know it works from LeetCode" fail this probe. Candidates who explain the phase 2 math (distance from head to cycle start = distance from meeting point to cycle start mod cycle length) pass.

### Floyd's Phase 2 Math (Detailed)

Let F = distance from head to cycle entry. Let C = cycle length. Let h = distance from cycle entry to meeting point (measured forward).

At phase 1 meeting: slow traveled F + h steps, fast traveled F + h + nC steps.
Since fast = 2 * slow: F + h + nC = 2(F + h) --> F = nC - h.

After phase 2 reset: slow starts at head (0 steps in), fast at meeting point (h steps into cycle). They both advance one step at a time. After F steps: slow is at cycle entry. Fast has advanced F = nC - h steps from meeting point, landing at (h + nC - h) mod C = 0 from cycle entry, exactly at cycle entry. They meet at the cycle entry node.

### 3Sum Deduplication: The Hard Part

3Sum is converging two pointers applied to a fixed outer element. Sort the array, fix index `i` as the first element, then use converging two pointers on `arr[i+1..n-1]` to find pairs that sum to `-arr[i]`. Time complexity: O(n^2). This is optimal: you cannot solve 3Sum in better than O(n^2) in the comparison model.

Three deduplication rules:
1. Skip `i` if `arr[i] == arr[i-1]` and `i > 0` -- same outer element would produce the same triplets.
2. After finding a valid triplet and recording it, advance both pointers *and* skip duplicates: `while left < right and arr[left] == arr[left-1]: left += 1` and similarly for right.
3. The sort itself is the prerequisite -- without it, deduplication via `arr[i] == arr[i-1]` doesn't work because equal elements may not be adjacent.

Edge case: when all elements are zero, `[0, 0, 0]` is the only valid triplet. The skip conditions use `left > i+1` and `right < n-1` guards, not `left > 0` and `right < n-1`, to avoid skipping the first occurrence.

### Trapping Rain Water: Proof by Case Analysis, Not Greedy Heuristic

The amount of water at position `i` is `min(left_max[i], right_max[i]) - height[i]`. The converging two-pointer solution maintains `left_max` and `right_max` and processes the pointer pointing to the shorter max.

If `left_max < right_max`, then the water at `left` is determined by `left_max`, specifically `left_max - height[left]`, regardless of what's to the right of `left`. We know `right_max >= left_max`, so `min(left_max, actual_right_max) = left_max`. The exact value of `actual_right_max` doesn't matter; it's at least `right_max`.

This is a proof by case analysis, not a greedy heuristic. Candidates who explain this proof in an interview are rated significantly higher than those who say "process the smaller side" without justification.

### LC 80 Generalization: Allow at Most k Occurrences

For "remove duplicates allow at most k occurrences" (LC 80), compare `nums[fast]` against `nums[slow - k]` instead of `nums[slow - 1]`. If they differ, the element at fast is safe to keep.

### Common Mistakes (from CalibreOS)

1. **Not sorting before converging**: On unsorted input, the directional guarantee breaks and you get incorrect results. Always sort first (O(n log n)) when the problem permits it.
2. **Wrong deduplication in 3Sum**: Using `if nums[i] == nums[i-1]` without the `i > 0` guard, causing an index error at i=0. Or deduplicating at the wrong level -- skipping only the outer i loop but not the inner left/right pointers.
3. **Skipping Floyd's phase 2**: The meeting point is *inside* the cycle, not at its start. Phase 2 is required to find the actual entry node.
4. **Using Floyd's on arrays without modeling**: Floyd's works on arrays only when you explicitly model the array as a function f: index -> nums[index], creating an implicit linked list. For LC 287, the array must satisfy 1 <= nums[i] <= n so that all values are valid indices.

### Two Pointers vs. Sliding Window: Key Distinction

- Use **two pointers (converging)** when: the array is sorted and you're searching for pairs or triplets summing to a target. The sorted structure is load-bearing -- without it, you need a hash set and O(n) space.
- Use **sliding window** when: the problem asks about a contiguous subarray or substring, and you're tracking a running state (sum, frequency) over the window.

The key difference: sliding window has an explicit *window state* that you maintain and query; converging two pointers generally makes O(1) decisions based on the current element values and a global target. Same-direction two pointers are typically about in-place array manipulation (write pointer + read pointer), while sliding window is about tracking a window property.

### Additional Classic Problems Reference

| LC # | Problem Name | Variant | Key Insight | Difficulty |
|------|-------------|---------|-------------|------------|
| 141 | Linked List Cycle | Floyd phase 1 | Hare reaches tortoise only if cycle exists; null check = no cycle | Easy |
| 142 | Linked List Cycle II | Floyd phase 1+2 | Phase 2 reset finds entry; requires understanding F = nC - h proof | Medium |
| 287 | Find the Duplicate Number | Floyd on array | Array as implicit linked list: i -> nums[i]; find cycle start = duplicate | Medium |
| 876 | Middle of the Linked List | Fast/slow same-start | When fast reaches end, slow is at middle; fast moves 2x | Easy |

### Interview Questions (from CalibreOS Two Pointers article)

1. Prove why Floyd's cycle detection phase 2 finds the cycle entry node, not some arbitrary node.
2. Why does two-pointer converging work correctly on trapping rain water, and how is it different from a greedy heuristic?
3. How does same-direction two-pointer handle "remove duplicates allow at most k occurrences" (LC 80)?
4. What's the time complexity of 3Sum, and can it be improved to better than O(n^2)?
5. How do you use Floyd's cycle detection on an array (LC 287, find the duplicate number)?
6. What happens when all elements in 3Sum are zero -- how does deduplication handle this edge case?
