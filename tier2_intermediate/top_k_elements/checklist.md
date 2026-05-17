# Top-K Elements — Practice Checklist

Use this checklist each time you practice a heap / top-K problem.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Identification (1 min)
- [ ] Identify the heap signal:
  - [ ] "K largest" / "K smallest" / "K most frequent"
  - [ ] "find median dynamically"
  - [ ] "merge K sorted streams"
  - [ ] "schedule tasks with priorities"
  - [ ] K + a ranking criterion
- [ ] Choose the correct heap direction:
  - [ ] K largest -> min-heap of size K (evicts smallest of top-K)
  - [ ] K smallest -> max-heap of size K (evicts largest of bottom-K)
  - [ ] Median stream -> two heaps (max-heap for lower half, min-heap for upper half)
  - [ ] In Python: heapq is always min-heap, negate for max-heap

## Phase 2: Setup & Complexity (2 min)
- [ ] State the expected time complexity:
  - [ ] Top-K with bounded heap: O(n log k)
  - [ ] K-way merge: O(N log k) where N = total elements across K lists
  - [ ] Two-heap median: O(log n) per add, O(1) per query
  - [ ] Full sort fallback: O(n log n) — only when k ~ n
- [ ] State space complexity: O(k) for bounded heap, O(n) if counting frequencies
- [ ] Decide heap contents:
  - [ ] Tuples: `(priority, tie_breaker, item)`
  - [ ] Include monotonic counter if items are not directly comparable
  - [ ] For max-heap in Python: `(-priority, counter, item)`

## Phase 3: Implementation (5-10 min)
- [ ] Initialize the heap (empty list or heapify from collection)
- [ ] Maintain the size invariant:
  - [ ] After every push, if heap size exceeds K, pop once
  - [ ] This keeps the heap bounded at K, O(log k) per operation
- [ ] Handle edge cases:
  - [ ] K equals array length (no eviction needed)
  - [ ] K = 1 (just track the single answer)
  - [ ] Empty input
  - [ ] Duplicate values / frequencies
- [ ] For two-heap median:
  - [ ] Always push to `lo` first, then balance to `hi`
  - [ ] Rebalance sizes so `len(lo) >= len(hi)` (difference at most 1)
  - [ ] Enforce `lo_max <= hi_min` invariant
- [ ] For K-way merge:
  - [ ] Seed heap with first element from each list
  - [ ] Use `(val, counter, node)` tuple to prevent TypeError
  - [ ] Push `node.next` after each pop

## Phase 4: Verify & Debug (3-5 min)
- [ ] Trace through a small example (n=5, k=2)
- [ ] Verify the heap root after each step matches expectations
- [ ] Check for common mistakes:
  - [ ] Wrong heap direction (min vs max)
  - [ ] Forgot to negate for max-heap in Python
  - [ ] Comparing non-comparable objects without tie-breaker counter
  - [ ] Modifying heap entries in-place instead of lazy deletion
  - [ ] O(n log n) solution when O(n log k) is expected
- [ ] Confirm output format matches problem requirements

## Phase 5: Follow-Up Questions (if asked)
- [ ] "What if K is very large (k ~ n)?" -> Fall back to full sort O(n log n)
- [ ] "What if data is streaming / infinite?" -> Bounded heap works online
- [ ] "Can you do better than O(n log k)?" -> Quickselect O(n) average, bucket sort O(n) for bounded frequencies
- [ ] "How does this connect to real systems?" -> K-way merge in external sort, top-K in recommendation systems, priority queues in job schedulers

## Practice Log
| Date | Problem | Time | Solved? | Notes |
|------|---------|------|---------|-------|
| _______ | LC 215: Kth Largest | ___min | [ ] | |
| _______ | LC 347: Top K Frequent | ___min | [ ] | |
| _______ | LC 23: Merge K Sorted Lists | ___min | [ ] | |
| _______ | LC 295: Median from Stream | ___min | [ ] | |
| _______ | LC 973: K Closest Points | ___min | [ ] | |
| _______ | LC 767: Reorganize String | ___min | [ ] | |
| _______ | LC 1046: Last Stone Weight | ___min | [ ] | |
| _______ | LC 621: Task Scheduler | ___min | [ ] | |
| _______ | LC 632: Smallest Range K Lists | ___min | [ ] | |

Source: [Heaps & Priority Queues: Top-K, Merge K Lists, and Two-Heap Patterns (CalibreOS)](https://www.calibreos.com/learn/dsa-heaps)
