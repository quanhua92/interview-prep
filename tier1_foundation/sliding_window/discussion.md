# Sliding Window: Fixed and Variable Window Patterns

## One-Liner
Maintain a window (contiguous subarray/substring) that slides through data with two pointers; expand right, shrink left when the constraint is violated, and update the answer -- achieving O(n) instead of O(n^2) brute force.

## When to Reach for Sliding Window
Three recognition signals must ALL appear:
1. **Contiguous subarray or substring** -- not subsequences, not arbitrary subsets. Elements must be adjacent.
2. **Optimizing over all possible windows** -- longest, shortest, maximum sum, minimum size.
3. **Monotonic constraint** -- as you expand the window, the property either stays valid or becomes invalid in one direction only. Shrinking always restores validity.

When all three signals appear, you collapse O(n^2) brute force into O(n). The brute force tries every window: O(n) starting positions x O(n) window sizes = O(n^2). Sliding window avoids this by maintaining a live **window state** (count, sum, frequency map) updated incrementally as boundaries move.

The pattern does NOT apply when:
- Elements can be non-contiguous (use DP)
- The constraint has multiple validity regions (use binary search on window size)
- You need all pairs regardless of adjacency (two-pointer converging is better)

Source: [Sliding Window: Fixed and Variable Window Patterns (CalibreOS)](https://www.calibreos.com/learn/dsa-sliding-window)

## Choosing Fixed vs. Variable Window

### Step 1: Check if window size k is given explicitly
- "subarray of exactly size k" or "every window of size k" -> **fixed window**
- Window always has exactly k elements
- Add `arr[right]` on entry, remove `arr[right - k]` on exit, no while loop needed

### Step 2: Identify the validity constraint for variable windows
- "longest satisfying X" or "shortest satisfying Y" -> **variable window**
- Define exactly what makes a window valid vs. invalid
- This invariant drives the shrink condition

### Step 3: Decide what state to track
- Fixed windows: running sum or fixed-size frequency count
- Variable windows: hash map (character/element counts) or counter (distinct elements, elements meeting threshold)

### Step 4: Confirm monotonicity of the constraint
- Once the window becomes invalid, shrinking from the left must eventually restore validity
- If expanding right can both create and destroy validity (e.g., "exactly k distinct"), reformulate as "at most k distinct minus at most k-1 distinct"

## What Interviewers Are Testing
Senior-level answers demonstrate:
1. Correctly identifying **which** window type applies before writing code
2. Articulating the **invariant** being maintained -- what state the window must satisfy at all times
3. Explaining **why** time complexity is O(n) rather than O(n^2)

Google and Meta specifically probe whether you understand that the amortized cost is O(n) because `left` only advances forward, not because the inner `while` loop has constant iterations.

## The Expand-Shrink Template

### Step 1: Initialize window state and set left = 0
- Create the data structure tracking window state: running sum, defaultdict for char counts, counter for "satisfied" elements
- Set left = 0
- right will be the loop variable

### Step 2: Expand -- iterate right from 0 to n-1, add arr[right] to state
- Sum windows: `total += arr[right]`
- Character windows: `count[arr[right]] += 1`
- "have/need" windows: if count reaches required frequency, increment `have`

### Step 3: Shrink -- while constraint violated, remove arr[left] and advance left
- Check the violation condition
- While it holds: remove arr[left] from state, then `left += 1`
- After the while loop, window [left, right] is valid again

### Step 4: Update answer from the current valid window
- Place this update **after** the shrink loop, not inside it
- Update: max size = `right - left + 1`, min size, or accumulate sum

## Worked Examples

### Fixed Window: Maximum Sum Subarray of Size K
- Invariant: window is always exactly k elements
- Add `arr[right]`, remove `arr[right - k]` (the element that fell off the left)
- No while loop needed

### Variable Window: Longest Substring Without Repeating Characters (LC 3)
- Window state: char_count frequency map
- Invariant: all values in char_count are exactly 1 (no duplicates)
- Violation: `char_count[s[right]] > 1` after adding s[right]
- Shrink until duplicate is removed, then update max length
- Key insight: only shrink when s[right] is the duplicate

### Variable Window with Condition: Minimum Window Substring (LC 76)
- **The have/need trick**: track `have` (characters satisfying required count) and `need` (total distinct characters required)
- This avoids scanning entire freq map on every shrink step (O(1) check vs O(|alphabet|) per step)
- Window state: window_counts frequency map + have counter + need target
- Invariant for valid window: `have == need`
- Update answer WHILE valid, then shrink to try to find a smaller valid window
- Opposite shrink trigger from "longest" problems

## Why Sliding Window Is O(n) Not O(n^2)

The expand-shrink template has a `while` inside a `for` loop, which looks like O(n^2). The resolution is **amortized analysis**:
- The total number of times `left` advances across ALL iterations of the outer loop is at most n
- `left` starts at 0, only ever increases, and can never exceed n
- So the inner while loop executes at most n times **total**, not n times per outer iteration

Formal argument: define potential = left. Each right iteration costs 1 + k_i where k_i is how far left advances. Total cost = sum(1 + k_i) = n + sum(k_i) = n + (final left - initial left) <= n + n = 2n = O(n).

This applies to any two-pointer scheme where both pointers move in the same direction and the sum of all movements is bounded by 2n.

The contrast with brute force: O(n^2) comes from starting a new scan for every starting position. Sliding window reuses window state -- when you move left, you **undo** the contribution of the removed element in O(1). If your undo takes O(k) time, you lose the O(n) guarantee.

## Common Mistakes That Kill Your Score

1. **Forgetting to shrink**: The `while constraint_violated` block is mandatory for variable windows. Missing it produces wrong answers on inputs with violations mid-array.

2. **Off-by-one on fixed windows**: The element leaving is `arr[right - k]`, not `arr[left]`. You don't track left separately for fixed windows.

3. **Updating answer inside the shrink loop**: Place the answer update AFTER the while loop, when the window is guaranteed valid. Updating inside can record intermediate invalid states.

4. **Empty or single-element edge cases**: Always check `if not s: return 0` before the main loop.

5. **Wrong violation check direction**: For "minimum window", you update the answer WHILE the window is valid then shrink. For "longest without repeating", you shrink WHILE invalid. These are opposite shrink triggers; mixing them up gives wrong answers.

## What Impresses Interviewers

Before coding, say: "This is a variable sliding window. The invariant I'm maintaining is X. I'll expand right, shrink left when X is violated, and update the answer after each shrink." Naming the invariant before coding signals senior-level thinking.

Then trace through a small example (3-4 elements) showing window state at each step. Interviewers at Facebook specifically look for candidates who can articulate **why** the approach is correct (the invariant proof) rather than just implementing it from memory.

## Classic Problem Reference

| LC # | Problem | Window Type | State to Track | Difficulty |
|------|---------|-------------|----------------|------------|
| 643 | Maximum Average Subarray I | Fixed (size k) | Running sum | Easy |
| 3 | Longest Substring Without Repeating Chars | Variable (longest valid) | char_count dict, shrink on dup | Medium |
| 76 | Minimum Window Substring | Variable (shortest valid) | have/need counter + freq map | Hard |
| 424 | Longest Repeating Character Replacement | Variable (longest valid) | max_freq, shrink when window - max_freq > k | Medium |
| 567 | Permutation in String | Fixed (size len(s1)) | Freq map diff count | Medium |
| 239 | Sliding Window Maximum | Fixed (size k) | Monotonic deque of indices | Hard |
| 1004 | Max Consecutive Ones III | Variable (longest valid) | Count of zeros flipped | Medium |
| 438 | Find All Anagrams in a String | Fixed (size len(p)) | Freq map diff count, record all starts | Medium |
| 209 | Minimum Size Subarray Sum | Variable (shortest valid) | Running sum | Medium |
| 992 | Subarrays with K Different Integers | Variable (count) | atMostK(k) - atMostK(k-1) trick | Hard |

## Interview Questions
1. Why is sliding window O(n) even though there's a while loop inside a for loop?
2. How do you choose fixed vs. variable window? Give a concrete decision process.
3. Walk me through the have/need trick in minimum window substring. Why not just compare frequency maps?
4. What if the window needs to track element order, not just frequency? Does sliding window still work?
5. How do you solve "number of subarrays with exactly k distinct integers"? The standard shrink doesn't work directly.
