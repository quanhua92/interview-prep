# Monotonic Stack — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Recognize the Pattern (1-2 min)
- [ ] Identify the query type: "for each element, find nearest greater/smaller neighbor"
- [ ] Confirm signal phrases: "next greater", "next smaller", "days until", "largest rectangle", "maximum in window"
- [ ] Confirm brute force would be O(n^2) nested loops
- [ ] Verify it is NOT an inversion count problem (which needs merge sort/Fenwick tree)

## Phase 2: Choose Stack Configuration (1-2 min)
- [ ] Determine if you need next/previous greater or next/previous smaller
- [ ] Choose increasing stack (for next greater) or decreasing stack (for next smaller)
- [ ] Name the stack by its content invariant, not the pop condition
- [ ] Decide: stack (no window constraint) or deque (fixed window size k)
- [ ] Choose strict vs non-strict inequality based on equal-element handling

## Phase 3: Core Implementation (3-5 min)
- [ ] Initialize result array with default values (-1 for NGE, 0 for distance)
- [ ] Initialize empty stack/deque (store indices, NOT values)
- [ ] Write the outer loop: iterate over all elements
- [ ] Write the inner while: pop while stack top violates monotonic invariant
- [ ] Process each popped element: record answer (value or distance)
- [ ] Push current index onto stack/deque
- [ ] Handle remaining elements (sentinel trick or post-loop flush)
- [ ] State the amortized O(n) argument: each element pushed once, popped at most once

## Phase 4: Problem-Specific Details (3-5 min)
- [ ] If histogram (LC 84): explain sentinel trick, area = height * (right - left - 1)
- [ ] If sliding window (LC 239): evict from front when index out of window (dq[0] <= i - k)
- [ ] If circular (LC 503): loop 2n iterations with i % n, push only in first pass
- [ ] If daily temperatures (LC 739): result[idx] = i - idx (distance, not value)

## Phase 5: Edge Cases and Verification (2-3 min)
- [ ] Strictly increasing input [1,2,3,4,5] -- no pops during loop, sentinel/flush handles it
- [ ] Strictly decreasing input [5,4,3,2,1] -- stack fills to n, all get -1
- [ ] All equal elements [3,3,3,3] -- depends on strict vs non-strict choice
- [ ] Single element [7] -- trivially -1 or 0
- [ ] Empty array -- return empty result
- [ ] Trace through the algorithm on the given example, narrating each push/pop

## Phase 6: Interview Probes (be ready to answer)
- [ ] "Why is this O(n) with an inner while loop?" -- amortized: total pops <= total pushes <= n
- [ ] "Why store indices not values?" -- distances and widths require positions; values are recoverable via arr[idx]
- [ ] "When would you use a deque instead of a stack?" -- fixed window size requires front eviction
- [ ] "How does the sentinel simplify LC 84?" -- flushes stack inside loop, avoids separate post-loop pass
- [ ] "What if the array is circular?" -- double traversal with modular indexing

## Classic Problems Reference
| LC # | Problem | Structure | Direction | Key Insight |
|------|---------|-----------|-----------|-------------|
| 496 | Next Greater Element I | Stack | Increasing | Process nums2, answer queries for nums1 via hash map |
| 739 | Daily Temperatures | Stack | Increasing | Store indices; result[idx] = i - idx |
| 503 | Next Greater Element II (Circular) | Stack | Increasing | Loop twice (i % n); push only in first pass |
| 84 | Largest Rectangle in Histogram | Stack | Increasing | Sentinel 0; area = height * (right - left - 1) |
| 42 | Trapping Rain Water (stack variant) | Stack | Decreasing | Pop valley bottom, compute water layer |
| 901 | Online Stock Span | Stack | Decreasing | Store (price, span); accumulate spans |
| 239 | Sliding Window Maximum | Deque | Decreasing | Front eviction for window; front = current max |
| 862 | Shortest Subarray Sum at Least K | Deque + Prefix Sum | Increasing | Combine prefix sum with monotonic deque |

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:

Source: [Monotonic Stack and Deque: Next Greater Element in O(n) (CalibreOS)](https://www.calibreos.com/learn/dsa-monotonic-stack)
