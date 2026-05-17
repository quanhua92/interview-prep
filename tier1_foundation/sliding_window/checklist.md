# Sliding Window -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

Source: [Sliding Window: Fixed and Variable Window Patterns (CalibreOS)](https://www.calibreos.com/learn/dsa-sliding-window)

## Phase 1: Problem Recognition (1-2 min)
- [ ] Restate the problem in your own words
- [ ] Verify the three recognition signals:
  - [ ] Contiguous subarray/substring (not subsequence)
  - [ ] Optimizing over all windows (longest, shortest, max sum, min size)
  - [ ] Monotonic constraint (expanding only makes validity worse; shrinking restores it)
- [ ] Confirm sliding window applies (rule out DP, binary search, two-pointer converging)
- [ ] Classify the window type:
  - [ ] Fixed: "exactly size k", "every window of size k"
  - [ ] Variable: "longest satisfying X", "shortest satisfying Y"
- [ ] State the window invariant out loud before coding

## Phase 2: Design the Window State (2-3 min)
- [ ] Define what makes a window valid vs. invalid (the violation condition)
- [ ] Choose the data structure for tracking window state:
  - [ ] Running sum (for sum-based windows)
  - [ ] Frequency map / defaultdict (for character/element count windows)
  - [ ] have/need counter (for "must contain all of X" problems)
  - [ ] Monotonic deque (for sliding window maximum/minimum)
- [ ] Confirm monotonicity: once invalid, shrinking from left must eventually restore validity
- [ ] Identify edge cases: empty input, single element, k > len(arr), no valid window exists

## Phase 3: Implement the Template (5-8 min)
- [ ] Initialize window state and set left = 0
- [ ] Write the expand step: iterate right from 0 to n-1, add arr[right] to state
- [ ] Write the shrink step (variable windows only): while constraint violated, remove arr[left] and advance left
- [ ] Place answer update AFTER the shrink loop (not inside it)
- [ ] Handle edge cases with early returns (empty input, k > len)
- [ ] State the time complexity: O(n) amortized -- left advances at most n times total
- [ ] State the space complexity: O(k) for window state, O(1) for pointers

## Phase 4: Trace and Verify (2-3 min)
- [ ] Trace through a small example (3-4 elements) showing window state at each step
- [ ] Verify the invariant holds after every shrink
- [ ] Check that the answer updates correctly at each valid window
- [ ] Walk through edge cases: all duplicates, no valid window, single element

## Phase 5: Interviewer Follow-Up Readiness (2-3 min)
- [ ] Can explain WHY it is O(n) not O(n^2): amortized analysis, left only advances forward
- [ ] Can explain the have/need trick for minimum window substring
- [ ] Can reformulate "exactly k distinct" as "at most k minus at most k-1"
- [ ] Can compare fixed vs. variable window and justify the choice
- [ ] Can identify when sliding window does NOT apply and what to use instead

## Common Pitfalls to Avoid
- [ ] Did I include the shrink loop for variable windows?
- [ ] Did I use `arr[right - k]` (not `arr[left]`) for fixed window removal?
- [ ] Did I place the answer update AFTER the shrink loop?
- [ ] Did I handle empty input with an early return?
- [ ] Did I use the correct shrink trigger direction (shrink while invalid vs. update while valid)?

## Practice Notes
- Date: _______  Problem: _______  Score: ___/10  Notes:
- Date: _______  Problem: _______  Score: ___/10  Notes:
- Date: _______  Problem: _______  Score: ___/10  Notes:
