# Two Pointers -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

Source: [Arrays and Strings: Core Interview Patterns and Execution Strategy (CalibreOS)](https://www.calibreos.com/learn/dsa-arrays-strings)

Additional Source: [Two Pointers: Converging, Fast/Slow, and Floyd's Cycle Detection (CalibreOS)](https://www.calibreos.com/learn/dsa-two-pointers)

## Phase 1: Pattern Recognition (2-3 min)
- [ ] Read the problem statement carefully -- is the input sorted or sortable?
- [ ] Identify keywords:
  - [ ] "Find pair/triplet with sum", "two sum", "three sum"
  - [ ] "Remove duplicates from sorted array"
  - [ ] "Palindrome", "valid palindrome"
  - [ ] "Container with most water", "trap rain water"
  - [ ] In-place array modification without extra space
- [ ] Classify the variant:
  - [ ] Converging pointers (opposite ends) -- pair sum, container, trapping rain
  - [ ] Fast-slow pointers (same direction) -- remove duplicates, partition, Floyd's
  - [ ] Sliding-width pointers -- substring problems with expanding/contracting window
  - [ ] Floyd's cycle detection -- linked list cycle, cycle entry, duplicate in array
- [ ] State why two pointers is better than alternatives:
  - [ ] vs nested loops: sorted order provides directional elimination (O(n^2) -> O(n))
  - [ ] vs hash map: O(1) space, or sorted structure already given
  - [ ] vs sliding window: when problem is not about contiguous subarray constraints
- [ ] Confirm you know which of the three variants applies:
  - [ ] Converging: sorted input, pair/triplet search
  - [ ] Same-direction: in-place modification (write ptr + read ptr)
  - [ ] Floyd's: linked list or array-as-implicit-linked-list cycle detection

## Phase 2: Brute Force Baseline (2-3 min)
- [ ] State the naive approach (usually nested loops O(n^2))
- [ ] Derive time complexity explicitly
- [ ] Derive space complexity explicitly
- [ ] Identify the repeated work that two pointers will eliminate

## Phase 3: Optimize with Invariant (3-5 min)
- [ ] State the invariant before writing any code:
  - [ ] Converging: "All pairs outside [left, right] have been eliminated"
  - [ ] Fast-slow: "[0...slow) is the valid processed region"
  - [ ] Sliding-width: "Window [left, right] satisfies the constraint"
- [ ] Explain the pointer movement logic:
  - [ ] Which pointer moves and under what condition
  - [ ] Why moving that pointer is correct (eliminates invalid candidates)
- [ ] State optimized time and space complexity
- [ ] If there is an inner while loop, explain amortized analysis:
  - [ ] "Right pointer moves n times, left pointer moves at most n times total"
  - [ ] "Total pointer moves <= 2n, each move does O(1) work"

## Phase 4: Implement (10-15 min)
- [ ] Write variable scaffolding first (left, right, result)
- [ ] Code incrementally, narrating each pointer update
- [ ] Keep each line tied to the invariant
- [ ] Use correct loop condition:
  - [ ] `while left < right` for converging pointers
  - [ ] `for fast in range(n)` for fast-slow variants
  - [ ] `while count[ch] > 1` for sliding-width contraction
- [ ] Handle duplicates correctly:
  - [ ] Compare current with previous element (fast-slow)
  - [ ] Move only one pointer per iteration (converging)
  - [ ] Track last occurrence index (sliding-width)

## Phase 5: Edge-Case Testing (3-5 min)
- [ ] Empty input (`[]` or `""`)
- [ ] Single element (`[1]`)
- [ ] All same elements (`[1, 1, 1]`)
- [ ] Two elements only
- [ ] All unique elements
- [ ] Extreme values (negative numbers, zeros)
- [ ] Window length off-by-one: inclusive `[left, right]` has size `right - left + 1`

## Common Pitfalls to Avoid
- [ ] Did I confuse substring with subsequence? (substring is contiguous)
- [ ] Did I move both pointers when only one should move?
- [ ] Did I handle equal-value runs in duplicate-heavy input?
- [ ] Did I state amortized O(n) reasoning for nested while loops?
- [ ] Did I test all-duplicate and all-unique inputs?
- [ ] Did I sort the array before applying converging pointers? (unsorted breaks correctness)
- [ ] Did I include the `i > 0` guard in 3Sum deduplication to avoid index error?
- [ ] Did I deduplicate at both outer (i) and inner (left/right) levels in 3Sum?
- [ ] Did I run Floyd's phase 2 after phase 1? (meeting point != cycle entry)
- [ ] Did I model the array as an implicit linked list for Floyd's on arrays? (LC 287 requires 1 <= nums[i] <= n)

## CalibreOS Interview Probes (Deep Understanding)
- [ ] Can I prove why moving the smaller-max pointer in trapping rain water is correct (not greedy)?
- [ ] Can I explain Floyd's phase 2 math: F = nC - h, and why slow/fast meet at cycle entry?
- [ ] Can I explain the LC 80 generalization (compare against nums[slow - k] instead of nums[slow - 1])?
- [ ] Can I state why 3Sum is O(n^2) optimal in the comparison model?
- [ ] Can I distinguish two pointers vs sliding window in one sentence?

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
