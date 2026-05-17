# Top-K Elements — Discussion & Insights

## Core Pattern

Use a heap (priority queue) to find the top-k or bottom-k elements without fully
sorting. A min-heap of size *k* tracks the k largest elements; a max-heap of
size *k* tracks the k smallest.

## The Counter-Intuitive Rule: Min-Heap for K Largest

Use a **min-heap of size K** to find the K largest elements. This feels
backwards but is correct: the smallest of the top-K sits at the root. When a
new element is larger than the root, pop the root and push the new element.

**Why not a max-heap?** A max-heap of all n elements costs O(n) to build +
O(k log n) to extract = O(n + k log n). A bounded min-heap of size K costs
O(n log k), strictly better when k << n.

Rule of thumb: the heap always **evicts** the element that would NOT be in your
K-element answer.

| Goal          | Heap type     | Size | Evicts         |
|---------------|---------------|------|----------------|
| K largest     | Min-heap      | K    | Smallest of top-K |
| K smallest    | Max-heap (negate in Python) | K | Largest of bottom-K |
| Median stream | Both (two-heap) | balanced | N/A — partition |

## Heap Fundamentals

- **Array representation** (0-indexed): node at `i`, parent `(i-1)//2`, left child `2i+1`, right child `2i+2`.
- **heapify** runs in O(n), NOT O(n log n). Most sift-down operations work on small subtrees near the leaves.
- Python's `heapq` is min-heap only. Simulate max-heap by negating: push `-val`, pop and negate the result.
- For tuples, Python compares element-by-element: `(priority, item)` is canonical for priority queues.
- If items are not directly comparable (objects, ListNodes), use `(priority, counter, item)` where counter is a monotonically increasing tie-breaker.

## Key Operations

| Operation | Complexity | Notes |
|-----------|------------|-------|
| heappush  | O(log n)   | Insert at end, bubble up |
| heappop   | O(log n)   | Remove root, sift down last element |
| heap[0]   | O(1)       | Peek at root, no removal |
| heapify   | O(n)       | Convert array in-place |

## Three Interview Patterns

### Pattern 1: Top-K Elements

Build a frequency map (if needed), then maintain a bounded heap of size K.

```
K largest: min-heap of size K, O(n log k)
K smallest: max-heap of size K (negate), O(n log k)
K most frequent: count frequencies, then heap on (freq, element)
K closest points: max-heap keyed by distance, capped at size K
```

### Pattern 2: Merge K Sorted Lists (K-Way Merge)

Push the first element from each of K lists into a min-heap as
`(val, counter, node)`. Repeatedly pop the minimum, append to result, and push
that node's `.next` if it exists. Heap always has at most K elements.

- Time: O(N log k) where N = total elements across all lists
- Space: O(k)
- Real-world connections: merge sorted runs from K worker nodes, merge K log
  streams, merge K sorted database partitions, external merge sort
- **Critical**: Use a monotonic counter as tuple tie-breaker to prevent
  `TypeError` when comparing non-comparable objects (ListNodes)

### Pattern 3: Two-Heap Median (LC 295)

Maintain two heaps partitioning the sorted stream:

- `lo` = max-heap (negate in Python), stores lower half
- `hi` = min-heap, stores upper half
- Invariant: `len(lo) == len(hi)` or `len(lo) == len(hi) + 1`
- Invariant: `lo_max <= hi_min` (every element in lower half < every element in upper half)

**addNum algorithm**:
1. Push `num` to `lo` (max-heap)
2. Pop `lo`'s max, push to `hi` (enforces `lo_max <= hi_min`)
3. If `len(hi) > len(lo)`, pop `hi`'s min, push to `lo` (rebalance sizes)

**The subtle bug**: You must always push to `lo` first and then balance to `hi`.
Pushing directly to the "correct" half based on value alone can violate the
`lo_max <= hi_min` invariant when the value falls between `lo_max` and `hi_min`.

## Lazy Deletion Pattern

Heaps don't support O(log n) arbitrary deletion. When entries become stale:
1. Push the new entry, mark the old one stale in a dict
2. When popping, skip entries marked stale
3. **Never modify heap entries in-place** — the heap invariant breaks

Use cases: Dijkstra's algorithm (updated shortest distances), K closest points
with changing distances, any problem where heap entries need updating.

## Spotting Heap Problems

Keywords and signals:
- "K largest" / "K smallest" / "K most frequent"
- "find median dynamically"
- "merge K sorted streams"
- "schedule tasks with priorities"
- Any problem with K and a ranking criterion

## Complexity Comparison

| Approach | Time | Space | When to use |
|----------|------|-------|-------------|
| Full sort, take K | O(n log n) | O(1) or O(n) | K ~ n |
| Min-heap of size K | O(n log k) | O(k) | k << n (expected in interviews) |
| Quickselect | O(n) avg | O(1) | Order statistic, no sorting needed |
| Bucket sort (freq) | O(n) | O(n) | Frequencies bounded by n |

## Common Mistakes

1. **Using max-heap for K largest (backwards)**: Min-heap of size K is correct.
2. **Forgetting to negate for max-heap in Python**: Push `-val`, negate on pop. For tuples: `(-priority, counter, item)`.
3. **Comparing non-comparable objects in tuples**: `(val, ListNode)` crashes when vals tie. Always use `(val, counter, node)`.
4. **Modifying heap entries in-place**: Use lazy deletion instead.
5. **O(n log n) when O(n log k) is expected**: Sorting all n elements and taking K is O(n log n). Maintaining a heap of size K is O(n log k). Interviewers expect the heap solution when k << n.

## Must-Know LeetCode Problems

| LC# | Title | Heap Type | Pattern | Time | Key Insight |
|-----|-------|-----------|---------|------|-------------|
| 215 | Kth Largest Element | Min-heap size k | Top-K largest | O(n log k) | Min-heap evicts elements smaller than k-th largest |
| 347 | Top K Frequent | Min-heap size k | Top-K by frequency | O(n log k) | Heap on (freq, element) pairs after counting |
| 23 | Merge K Sorted Lists | Min-heap size k | K-way merge | O(N log k) | Counter tie-breaker prevents ListNode comparison error |
| 295 | Find Median from Stream | Two heaps | Lo/hi partition | O(log n) add, O(1) median | Always insert to lo first, then rebalance to hi |
| 973 | K Closest Points | Max-heap size k | Top-K by distance | O(n log k) | Use squared distance; max-heap evicts farthest |
| 767 | Reorganize String | Max-heap | Greedy frequency | O(n log n) | Always pick two most frequent to avoid adjacency |
| 1046 | Last Stone Weight | Max-heap | Simulation | O(n log n) | Repeat: smash two heaviest, push difference |
| 621 | Task Scheduler | Max-heap + counter | Greedy cooldown | O(n) | Fill cooldown with next-most-frequent tasks |
| 358 | Rearrange String k Distance Apart | Max-heap | Greedy windowed | O(n log n) | Variant of 767 with window size k instead of 2 |
| 632 | Smallest Range Covering K Lists | Min-heap | Sliding window + heap | O(N log k) | Track current max; advance min-list pointer each step |

Source: [Heaps & Priority Queues: Top-K, Merge K Lists, and Two-Heap Patterns (CalibreOS)](https://www.calibreos.com/learn/dsa-heaps)
