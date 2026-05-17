# Monotonic Stack

## One-Liner
Maintain a stack whose elements are always in monotonic (increasing or decreasing) order; when a new element violates the invariant, pop and process each displaced element to answer nearest-neighbor queries in O(n).

## Functional Requirements
- For each element in an array, find the next/previous greater or smaller element
- Compute distances (days gap, histogram widths) between elements and their nearest greater/smaller neighbor
- Find maximum/minimum in every sliding window of fixed size k
- Handle circular arrays by simulating a double traversal

## Non-Functional Requirements
- O(n) time amortized -- each element is pushed and popped at most once
- O(n) space worst case for the stack (strictly monotonic input fills the stack)
- Stable handling of duplicate values (strict vs non-strict inequality choice matters)

## Key Scale Questions
- Brute force is O(n^2): for each element, scan right/left until you find a greater/smaller element
- Monotonic stack achieves O(n) because total push + pop operations across all iterations is at most 2n
- The inner while loop does not add an O(n) factor; it redistributes work that is bounded globally

## Core Components
- **Monotonic increasing stack**: elements increase bottom-to-top; pop when incoming > top. Solves next greater element.
- **Monotonic decreasing stack**: elements decrease bottom-to-top; pop when incoming < top. Solves next smaller element.
- **Monotonic deque (double-ended)**: like a stack but with O(1) eviction from both ends. Required for sliding window variants where elements must also be removed at the front (window boundary expiry).

## Key Design Decisions

### Store Indices, Not Values
- **Option A: Store values**: Lets you compare elements, but you lose position information. Cannot compute distances or widths.
- **Option B: Store indices**: Values are always retrievable as `arr[idx]`. Position is NOT recoverable from value alone. Indices enable distance computation (`i - idx` in LC 739, `right - left - 1` in LC 84).
- **Verdict**: Always store indices. This is the single most common mistake candidates make.

### Increasing vs. Decreasing Stack
- **Monotonic increasing stack**: Elements increase bottom-to-top. You pop when incoming >= top (the incoming element violates the increasing property by being too large). This is used for next greater element: the moment you encounter something larger than the top, you have found the answer.
- **Monotonic decreasing stack**: Elements decrease bottom-to-top. You pop when incoming <= top. Used for next smaller element.
- **Naming tip**: Name the stack by its content invariant, not the pop condition. State it explicitly: "I maintain a stack where indices are stored in increasing order of their corresponding heights, bottom to top."

### Stack vs. Deque
- **Stack**: Sufficient when there is no window constraint. Push/pop from one end only.
- **Deque**: Required when there is a fixed window size k. You need O(1) eviction from both ends -- back for domination (new element is larger), front for window boundary expiry (index falls outside window).
- **Why not stack for sliding window**: A stack cannot efficiently evict front elements. You need `collections.deque` for sliding window variants.

### Handling Remaining Elements
- **Next-greater problems**: Pre-initialize result to -1 (or 0 for distance). Elements remaining after the loop have no answer; the default value is correct.
- **Histogram problems**: Use a sentinel (append 0) to flush the stack inside the loop, avoiding a separate post-loop pass. This is an O(1) code simplification that prevents bugs from forgetting the post-loop flush.

## Deep Dive Topics

### Amortized O(n) Argument
Each element is pushed onto the stack exactly once and popped at most once. Across all n iterations of the outer loop, the total number of pop operations is bounded by n (you cannot pop more elements than you push). Therefore total work is O(2n) = O(n).

### The Sentinel Trick (LC 84)
Append a bar of height 0 to the end of the histogram array. This guarantees the stack is completely flushed at the end of the loop -- every bar gets its right boundary computed. Without the sentinel, you need a separate pass for bars remaining in the stack after the main loop. Input like `[1, 2, 3, 4, 5]` (all bars increasing) will have zero pops during the loop, making the post-loop flush essential.

### Strict vs Non-Strict Inequality
- Use strict inequality (`<` not `<=`) when equal elements should both find answers independently.
- Use non-strict when the first of equal elements should find the answer for all of them.
- The choice affects deduplication behavior for equal elements.

### Circular Array Handling (LC 503)
Loop twice using `i % n` to simulate a circular array. Only push indices during the first pass (indices 0 to n-1) to avoid double-pushing.

### Sliding Window Maximum Deque Invariant
Indices in the deque have their array values in decreasing order from front to back. `deque[0]` always holds the index of the maximum element in the current window. Two maintenance rules:
1. **Evict from back** (monotonic property): Remove all indices whose values <= arr[i]. These smaller elements can never be the maximum for any future window.
2. **Evict from front** (window boundary): If `deque[0] <= i - k`, that index has fallen outside the current window.

## Common Mistakes That Produce Wrong Answers
1. **Storing values instead of indices**: Loses position information. In LC 739, you need index gap (i - idx), not temperature gap. In LC 84, you need boundary positions to compute width.
2. **Forgetting to flush the stack after the loop**: Elements remaining in the stack after the main loop have no next greater element. For histogram, missing the flush gives wrong answers for inputs like [1, 2, 3, 4, 5] (all increasing).
3. **Confusing increasing vs decreasing direction**: "Increasing stack" means elements increase bottom-to-top. Pop when incoming is greater. Reversing this gives wrong pop conditions.
4. **Using stack instead of deque for sliding window**: A stack cannot evict front elements in O(1). Always use `collections.deque` for windowed variants.

## Pattern Recognition Signals
- "Next greater element" / "next smaller element"
- "Previous greater" / "previous smaller"
- "How many days until..."
- "Largest rectangle" / "maximum area"
- "For each element, find..." combined with a directional search
- Brute force is O(n^2) nested loops and interviewer says "can you do better?"

## NOT a Monotonic Stack Problem
- "Find all pairs where arr[i] > arr[j] and i < j" -- this is inversion count, use merge sort or Fenwick tree.

## Interview Questions
1. Why is the monotonic stack O(n) when there's an inner while loop? Walk through the amortized argument.
2. Why store indices instead of values? Give a concrete example where values-only fails.
3. Walk through LC 84 (largest rectangle in histogram) step by step. Why does the sentinel work?
4. Explain the difference between stack and deque for sliding window maximum. Why can't you use a stack?
5. How do you recognize that a problem needs a monotonic stack vs. prefix sum, two pointers, or hash map?

## Follow-Up Variations
- What if the array is circular (LC 503)?
- How would you solve "sum of subarray minimums" (LC 907) using monotonic stack?
- Can you solve "trapping rain water" (LC 42) with a monotonic stack? Compare with the two-pointer approach.
- How would you handle "online stock span" (LC 901) where elements arrive one at a time?

Source: [Monotonic Stack and Deque: Next Greater Element in O(n) (CalibreOS)](https://www.calibreos.com/learn/dsa-monotonic-stack)

---

## Monotonic Deque Deep Dive

### Python `collections.deque` Internals

`collections.deque` supports O(1) `append` (right), `appendleft` (left), `pop` (right), and `popleft` (left). It also supports O(1) `len()` and O(1) `dq[0]`/`dq[-1]` (front/back peek). It is backed by a doubly-linked list of fixed-size blocks, not a ring buffer.

- **When deque vs list**: Python lists support O(1) `append`/`pop` from the right, but `list.pop(0)` and `list.insert(0, x)` are O(n). Never use a list as a queue or deque.
- **Random access caveat**: `dq[k]` for arbitrary k is O(n). In monotonic deque problems, you only ever access `dq[0]` (front) and `dq[-1]` (back), both O(1).
- **`deque(maxlen=k)`**: Auto-evicts oldest element from left when full. Useful for fixed-size sliding window without manual front eviction.

### Why Not Heap for Sliding Window Max?

A max-heap gives O(log n) per push, but removing the element that falls outside the window requires a linear scan unless you use lazy deletion (mark expired entries, skip on pop). Lazy deletion still costs O(n log n) total. The deque achieves O(n) by evicting expired elements from the front in O(1). The deque is strictly better: O(n) time and O(k) space vs O(n log n) time and O(n) space for the heap approach.

### The Two Deque Invariants (Precise Statement)

For sliding window maximum, the deque maintains two invariants simultaneously:

1. **Monotonic property (back eviction)**: Deque values are in strictly decreasing order front-to-back. Maintained by popping from the back all indices where `nums[dq[-1]] <= nums[i]`. These smaller-or-equal elements can never be the window maximum for any future window: element `i` is both newer (stays in window longer) and larger (or equal). They are permanently **dominated** by `nums[i]`.
2. **Window property (front eviction)**: All indices in the deque are within the current window `[i-k+1, i]`. Maintained by popping from the front when `dq[0] <= i - k`.

**The dominance argument** (why eviction is safe): If element A is newer AND larger than element B, B can NEVER be the window maximum for any future window -- A will outlast B and is larger. This dominance relationship allows safely discarding B.

**Order of operations matters**: Always (1) evict from back, (2) append, (3) evict from front, (4) record result. If you check front before appending, you may evict the newly appended element in the k=1 edge case.

For **sliding window minimum**: flip the comparison. Evict from back when `nums[dq[-1]] >= nums[i]` (discard elements larger-or-equal). The front then holds the minimum.

### BOTIC Pattern Recognition Framework for Monotonic Deque

1. **Brute force, identify the sliding window structure**: Does the problem ask for max/min within a moving window of size k? Signal phrases: "maximum of every window of size k", "minimum within last k elements", "best reachable score within k jumps". State brute force: O(nk). If k is close to n, O(nk) is O(n^2), too slow for n = 10^5.
2. **Optimize, identify the deque opportunity**: Is there a fixed-size window where elements can dominate each other? If element A is newer AND larger (for max deque) than B, B can never be the future maximum. State: "I maintain a deque of candidate maximums, discarding dominated elements."
3. **Template, define the two invariants**: Invariant 1 (monotonic) and Invariant 2 (window boundary). State: "`deque[0]` is always the index of the current window maximum."
4. **Implement, follow the exact order**: (A) back eviction, (B) append, (C) front eviction, (D) record result once `i >= k-1`.
5. **Check edge cases**: k=1 (every element is its own window max), k=n (single window), empty input. Verify invariants on a small example.

### DP Optimization with Monotonic Deque: O(nk) to O(n)

The most powerful and least-known application of monotonic deque is DP recurrence optimization. When a DP has the form `dp[i] = max(dp[j] + cost(i, j))` for all `j in [i-k, i-1]`, the naive computation is O(nk). If `cost(i, j)` depends only on `i` (not on j), this reduces to `dp[i] = nums[i] + max(dp[j])` for `j in [i-k, i-1]`, exactly a sliding window maximum over dp values. The monotonic deque reduces this to O(n).

**Jump Game VI (LC 1696)** is the canonical example. Start at index 0, jump 1 to k steps forward. Score at index i is `nums[i]`. Maximize total score. DP: `dp[i] = nums[i] + max(dp[j])` for `j in [max(0, i-k), i-1]`. The deque tracks the maximum dp value in the last k positions.

**Why the stack does not work for DP optimization**: The window constraint `j in [i-k, i-1]` means older dp values expire. A monotonic stack has no front-eviction capability; it cannot efficiently discard `dp[j]` once j falls outside the window.

**When this optimization does NOT apply**: If `cost(i, j)` depends on both i and j (e.g., `cost = |i - j|`), you cannot separate the max over j from the index-dependent term. Techniques like divide-and-conquer DP or Convex Hull Trick (for linear-in-j cost functions) apply instead.

**Pattern recognition signals for DP + deque**:
- "Jump at most k steps" -> k-bounded lookahead
- "Subarray of length at most k" -> window constraint
- "dp[i] depends on max of dp[j] in sliding window" -> deque

### Deque-Specific Common Mistakes

1. **Using `list.pop(0)` instead of `collections.deque`**: `list.pop(0)` is O(n), turning the O(n) algorithm into O(n^2). Always use `collections.deque`.
2. **Wrong order of operations**: Back-evict, then append, then front-evict. Reversing this order fails for k=1.
3. **Off-by-one in window boundary**: The condition is `dq[0] <= i - k` (less-than-or-equal), not `dq[0] < i - k`. The window is `[i-k+1, i]`, so any index `<= i-k` is outside. Using strict less-than leaves an out-of-window element active for one extra step.
4. **`<=` vs `<` in back eviction**: For strict-max deque, evict when `nums[dq[-1]] <= nums[i]` (newer wins on ties). For some problems, ties should preserve the older element (use strict `<`). Clarify with the problem's tie-breaking requirement.
5. **Using a stack for a deque problem**: If the problem says "within k steps" or "in last k elements", it requires a deque. Using a stack silently fails for inputs where front eviction is needed.

### Stack vs Deque: Precise Decision Rule

- **Monotonic stack**: No window constraint. Processes entire left/right of current element. One-end eviction. Signal: "next greater element", "days until warmer", "largest rectangle".
- **Monotonic deque**: Fixed window size k. Elements expire by index position. Two-end eviction (back for dominance, front for expiry). Signal: "max/min in every window of size k", "within last k elements", "jump at most k steps".
- **Stack cannot solve deque problems** (no front eviction in O(1)). Deque can always replace stack (with unused capacity).

### Interview Script for Deque Problems

When you see "maximum in every window of size k": say "I will use a monotonic deque. It maintains indices in decreasing order of values, so the front always holds the window maximum. Each index enters and exits the deque at most once, O(n) amortized regardless of the inner while loop." Then state both invariants.

When the interviewer asks "why not a heap?": say "A heap gives O(log n) per operation, but removing the expired element requires lazy deletion, making it O(n log n) total. The deque evicts expired elements from the front in O(1), giving O(n)."

For DP optimization: "When dp[i] = max(dp[j]) + cost for j in [i-k, i-1], this is sliding window maximum over dp values, identical to LC 239 but on the dp array instead of the input array. The deque reduces it from O(nk) to O(n)."

Source: [Deque and Monotonic Deque: Sliding Window Optimization and DP Acceleration (CalibreOS)](https://www.calibreos.com/learn/dsa-deque-monotonic-deque)
