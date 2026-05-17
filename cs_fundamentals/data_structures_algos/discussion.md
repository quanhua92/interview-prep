# Data Structures & Algorithms

Core data structures, traversal algorithms, complexity analysis, and a big-O reference table for SWE interviews.

## Key Concepts

- **Arrays**: Contiguous memory storage with O(1) access by index and O(n) insertion/deletion (shifting required). Static arrays have fixed size; dynamic arrays (ArrayList, vector) amortize resize operations to achieve O(1) average append. Cache-friendly due to memory locality.
- **Linked Lists**: Nodes connected by pointers with O(1) insertion/deletion at known positions but O(n) access by index. Singly linked lists have one direction; doubly linked lists support bidirectional traversal. No cache locality due to non-contiguous memory.
- **Hash Tables**: Store key-value pairs with O(1) average-case lookup, insertion, and deletion. Use a hash function to map keys to bucket indices. Collision resolution strategies include chaining (linked lists at each bucket) and open addressing (probing for the next open slot). Worst case is O(n) when many collisions occur.
- **Binary Search Trees (BST)**: Ordered tree structure with O(log n) average search, insert, and delete. Left subtree contains smaller values; right subtree contains larger values. Degenerates to O(n) when unbalanced (e.g., inserting sorted data). Balanced variants (AVL, red-black) guarantee O(log n) worst case.
- **Heaps**: A complete binary tree that maintains the heap property -- max-heap parents are greater than children, min-heap parents are smaller. O(1) access to the min/max element, O(log n) insert and extract. Implemented as an array for cache efficiency. Used in priority queues and heap sort.

## Common Questions with Brief Answer Outlines

**Q: When would you use a hash table versus a BST?**
- Use a hash table when you need O(1) average-case lookups and the order of elements does not matter.
- Use a BST when you need elements in sorted order or need range queries (find all keys between X and Y).
- Hash tables do not support efficient range queries; BSTs do via in-order traversal in O(n) for all, O(log n) per element.
- BSTs provide guaranteed O(log n) worst-case performance when balanced; hash tables can degrade to O(n) under worst-case collisions.
- Hash tables have higher constant factors due to hashing overhead and memory for buckets.

**Q: Explain BFS and DFS, and when to use each.**
- BFS (Breadth-First Search) explores level by level using a queue. Finds the shortest path in an unweighted graph. Uses O(V + E) time and O(V) space (queue can hold up to V/2 nodes at the widest level).
- DFS (Depth-First Search) explores as deep as possible before backtracking, using a stack (or recursion). Uses O(V + E) time and O(V) space (recursion depth or stack).
- Use BFS for shortest path in unweighted graphs, level-order traversal, and finding all nodes at distance k.
- Use DFS for cycle detection, topological sorting, connected components, maze solving, and when memory is constrained (DFS typically uses less space than BFS in wide graphs).

**Q: What is the difference between AVL trees and red-black trees?**
- Both are self-balancing BSTs guaranteeing O(log n) operations.
- AVL trees maintain a stricter balance factor (left and right subtree heights differ by at most 1), providing faster lookups.
- Red-black trees allow a looser balance constraint, requiring fewer rotations on insert and delete, providing faster writes.
- AVL trees are preferred in read-heavy workloads (databases, dictionaries); red-black trees in write-heavy workloads.
- Java's TreeMap and C++ std::map use red-black trees; databases often use AVL or B+ trees.

**Q: How does quicksort compare to mergesort?**
- Quicksort: average O(n log n), worst O(n^2) with poor pivot choice; in-place with O(log n) stack space; cache-friendly due to sequential access patterns.
- Mergesort: guaranteed O(n log n); requires O(n) additional space; stable sort (preserves relative order of equal elements); preferred for linked lists.
- Quicksort is generally faster in practice due to better cache locality and lower constant factors.
- Hybrid approaches (e.g., Timsort in Python/Java) combine insertion sort for small arrays with mergesort for larger ones.

**Q: What are time and space complexity trade-offs in common operations?**
- Precomputation (e.g., hash tables, prefix sums) trades space for faster query time.
- Memoization/caching stores computed results to avoid redundant work, using O(n) space to reduce exponential time to polynomial.
- In-place algorithms modify the input directly to save space but may be harder to understand or parallelize.
- Amortized analysis: a sequence of expensive operations averages out to low cost per operation (e.g., dynamic array resizing doubles capacity, giving O(1) amortized append).

**Q: How would you solve the "two sum" problem?**
- Problem: given an array of integers and a target sum, return the indices of two numbers that add up to the target.
- Brute force: check every pair -- O(n^2) time, O(1) space.
- Hash table approach: iterate through the array, storing each number in a hash table; for each element, check if (target - element) exists in the table -- O(n) time, O(n) space. This is the classic example of trading space for time.
- Sorting approach: sort the array, then use two pointers from both ends -- O(n log n) time, O(1) space (or O(n) if sorting is not in-place). Does not return original indices unless stored separately.

**Q: What is the difference between stable and unstable sorting?**
- A stable sort preserves the relative order of elements with equal keys; an unstable sort does not guarantee this.
- For example, if you sort a list of employees by department and then by name with a stable sort, employees with the same name will remain grouped by department. With an unstable sort, the department ordering among equal-name employees may be lost.
- Stable sorts: mergesort, Timsort (Python/Java default), insertion sort, bubble sort.
- Unstable sorts: quicksort (standard implementations), heapsort, shell sort.
- Stability matters when sorting on multiple keys or when equal elements carry additional associated data that should not be reordered.

## Quick Reference Table: Big-O Complexity

| Data Structure | Access | Search | Insert | Delete |
|---|---|---|---|---|
| Array | O(1) | O(n) | O(n) | O(n) |
| Linked List | O(n) | O(n) | O(1)* | O(1)* |
| Hash Table | O(1) avg | O(1) avg | O(1) avg | O(1) avg |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(log n) |
| Heap | O(1) for min/max | O(n) | O(log n) | O(log n) |
| Trie | O(L) | O(L) | O(L) | O(L) |

*O(1) only if node pointer is known; O(n) if traversal is needed. L = length of key.

---

## The 8 Core DSA Patterns

Source: [The 8 Core DSA Patterns (CalibreOS)](https://www.calibreos.com/learn/dsa-patterns)

Coding interviews test **pattern recognition**, not memorization. Thousands of LeetCode problems reduce to a small set of core patterns. Once you internalize these 8 families, you can recognize the right approach within the first 2 minutes of reading a problem.

### Pattern Families

| # | Code | Pattern | When to Use |
|---|------|---------|-------------|
| 01 | WIND | **Sliding Window** | Contiguous subarrays or substrings. Ask for max/min/count of a window. Two variants: fixed-size (sum of every window of size k) and variable-size (longest window satisfying a condition). |
| 02 | PAIR | **Two Pointers** | Sorted arrays or finding pairs. Left+right pointers converge. Also fast/slow pointers for linked list cycle detection and middle node. |
| 03 | SEAR | **Binary Search** | Any time the answer space is monotonic. Classic: sorted array lookup. Advanced: search on answer space (e.g., "minimum feasible X") -- the most underutilized pattern. |
| 04 | PREF | **Prefix Sums** | Range sum queries. Build prefix[i] = sum(arr[0..i]). Range sum [l, r] = prefix[r] - prefix[l-1] in O(1). Also handles "subarray sum equals K" with prefix + hash map. |
| 05 | GREED | **Greedy** | Make the locally optimal choice at each step. Works when local optimum leads to global optimum (provable). Common: interval scheduling, gas station, jump game. |
| 06 | STATE | **Dynamic Programming** | Overlapping subproblems + optimal substructure. Define dp[i] meaning, establish base case, write recurrence. 1D, 2D, and DP on trees. |
| 07 | NODES | **Graph Traversal** | BFS for shortest path in unweighted graphs / level-order processing. DFS for connected components, cycle detection, topological sort, backtracking. |
| 08 | HEAP | **Priority Queue** | Need the next-best item repeatedly. Min-heap: top-K largest, kth element. Two heaps: running median. Heap + hash: LFU cache. |

### Decision Framework

When you read a problem, immediately ask:

1. Is the input sorted? -- Binary Search or Two Pointers.
2. Does it ask about a window/substring? -- Sliding Window.
3. Does it ask for max/min/count of some property? -- DP or Greedy.
4. Is there a graph structure? -- BFS/DFS.
5. Do I need to repeatedly pull the best item? -- Heap.

### Pattern to Signal Words Mapping

| Pattern | Signal Words | Example Problems |
|---------|-------------|-----------------|
| Sliding Window | substring, subarray, window, contiguous | Longest Substring Without Repeating, Min Window Substring |
| Two Pointers | pair, sorted, palindrome, reverse | 3Sum, Container With Most Water, Trapping Rain Water |
| Binary Search | sorted, minimum feasible, find kth | Search in Rotated Array, Koko Eating Bananas, Median of Two Arrays |
| Prefix Sum | range sum, subarray sum equals k | Subarray Sum Equals K, Product Except Self |
| Greedy | minimum operations, can you reach, schedule | Jump Game, Meeting Rooms, Gas Station |
| DP | count ways, minimum cost, longest | Coin Change, LCS, Edit Distance, 0/1 Knapsack |
| BFS/DFS | grid, connected components, shortest path, islands | Number of Islands, Word Ladder, Course Schedule |
| Heap | kth largest, top k, median stream | Top K Frequent, Merge K Lists, Find Median from Stream |

### Interview Execution Strategy

1. Read problem -> identify signal words.
2. State the pattern out loud: "This looks like a sliding window problem."
3. State complexity before coding: "This will be O(n) time, O(k) space."
4. Code the template, then fill in the problem-specific logic.
5. Test with the given example + your own edge case.

### Key Templates

#### Sliding Window (Variable Size)

Expand right pointer, shrink left when constraint violated. O(n) time, O(k) space.

```python
from collections import defaultdict

def longest_substring_k_distinct(s: str, k: int) -> int:
    counts = defaultdict(int)
    left = 0
    best = 0
    for right in range(len(s)):
        counts[s[right]] += 1
        while len(counts) > k:
            counts[s[left]] -= 1
            if counts[s[left]] == 0:
                del counts[s[left]]
            left += 1
        best = max(best, right - left + 1)
    return best
```

#### Binary Search on Answer Space

Works when the answer space is monotonic. Find the smallest X where condition(X) is True.

```python
def binary_search_answer(lo, hi, condition):
    while lo < hi:
        mid = (lo + hi) // 2
        if condition(mid):
            hi = mid
        else:
            lo = mid + 1
    return lo  # lo == hi == answer
```

#### Heap: Top-K and Running Median

- Top-K frequent: min-heap of size k, O(n log k) time.
- Running median: two heaps (max-heap for left half, min-heap for right half), O(log n) add, O(1) median.

---

## How to Approach a DSA Coding Interview

Source: [CalibreOS -- How to Approach a DSA Coding Interview](https://www.calibreos.com/learn/dsa-how-to-approach)

### The Six Signals DSA Interviewers Score

Every FAANG / Microsoft / Stripe coding rubric grades some variation of these six signals:

1. **Problem decomposition** -- do you restate the problem, identify constraints, and ask clarifying questions before coding? Or do you start typing on the first reading?
2. **Brute-force-then-optimize** -- do you propose an O(n^2) baseline first, state its complexity, and only then optimize? Jumping straight to the optimal hides reasoning and reads as memorization.
3. **Pattern recognition** -- within 2-3 minutes of seeing the problem, do you map it to a known family (sliding window, two pointers, binary search on answer, BFS, DP, heap, etc.)?
4. **Clean code** -- meaningful variable names, helper functions for repeated logic, no dead code, no commented-out attempts. The code reads like you wrote it for a teammate.
5. **Complexity analysis** -- both time AND space, stated unprompted, with the dominant cost identified (e.g., "O(n log n) sort dominates O(n) scan").
6. **Edge cases and testing** -- empty input, single element, all-equal elements, negative numbers, integer overflow, cycle in graph, duplicates. Surfaced *before* the interviewer asks.

Mid-level (L4) candidates miss signals 1, 5, and 6. Senior (L5) candidates lose on 2 and 4 -- they know the optimal answer but skip the brute-force conversation. Staff (L6) candidates win on 3 and on naming non-obvious tradeoffs.

### Why DSA Interviews Are Communication Tests in Disguise

The biggest misconception: that coding interviews test your ability to produce *correct code*. They don't, at least not primarily. They test your ability to *reason out loud about code* in a constrained, ambiguous, time-pressured setting. Two candidates can produce the identical final solution and receive opposite hire/no-hire signals based purely on how they communicated the journey.

Three skills compound:
- **Pattern matching** -- recognizing within 2-3 minutes which family of problem this is.
- **Structured narration** -- saying out loud what you're doing, why, and what you'd do differently.
- **Complexity literacy** -- stating both time and space complexity, identifying the dominant cost, and connecting the cost to a real-world constraint.

### The 8 Mindset Rules for DSA Coding Interviews

| # | Rule | Details |
|---|------|---------|
| 1 | Restate the problem in your own words before doing anything | Catches misreadings and signals you're not pattern-matching on a memorized title. |
| 2 | Ask 3-5 clarifying questions before coding | Standard battery: input size (rules in/out O(n^2)), value range (negatives? overflow?), duplicates allowed?, sorted?, return value?, empty input behavior? Each question takes 5 seconds and prevents minutes of wrong code. |
| 3 | Always state the brute force first, even if you know the optimal | Say "The brute force is O(n^2)... Space O(1). Now let me see if we can do better." This earns the decomposition signal AND gives you a fallback. Skipping brute force is a senior-level red flag -- it reads as memorized. |
| 4 | Explain the approach BEFORE coding, not while coding | Walk through it on a small example out loud before writing code. Catches bugs before they're written and lets the interviewer course-correct early. |
| 5 | Narrate the code as you write it | Coding silently for 15 minutes is the second-most-common interview-failing mistake. The interviewer scores reasoning, not just the final code. |
| 6 | Walk through your code on a test case before saying "done" | Trace manually with a small input. Catches off-by-one errors, wrong initial values, and missing edge cases. Signals discipline. |
| 7 | Surface edge cases unprompted | List them before tracing: empty input, single element, all-equal, very large input, negative numbers, integer overflow. Catching your own edge cases beats having the interviewer point them out. |
| 8 | State final complexity unprompted | After tracing, say both time and space, plus the alternative tradeoff. Stating BOTH, plus the alternative, is the L5+ signal. |

### Additional Pattern Recognition Signals

Beyond the 8 core patterns covered earlier, these signal-to-pattern mappings are critical for interviews:

| Signal in the problem | Pattern to apply |
|-----------------------|-----------------|
| "Maximum subarray sum" | **Kadane's Algorithm** -- O(n) time, O(1) space. Variant "max subarray with at most k deletions" becomes a small DP. Max Product Subarray needs two states (max and min). |
| "Next greater element" OR "rectangle in histogram" | **Monotonic Stack** -- maintain monotonically increasing/decreasing stack. O(n) amortized. |
| "Connected components" OR "check cycle in undirected" | **Union-Find** -- near-O(alpha(n)) amortized per op (effectively constant). |
| "Prefix matching / autocomplete / dictionary" | **Trie** -- O(L) per insert/search where L = word length. |

### The Single Most Expensive Mistake: Coding Before Confirming the Approach

Arriving at an approach in your head and immediately coding it, without explaining it to the interviewer first, is the highest-leverage failure mode. Example: the interviewer says "find the longest substring with at most K distinct characters." You silently decide on sliding window with a hashmap and start typing. At minute 20, you realize you confused this problem with "exactly K distinct." Now you're 20 minutes in with broken code.

**Fix**: after identifying the pattern, take 60-90 seconds to walk through the approach on a small input out loud. The interviewer will catch your misunderstanding before you write a single line. The cost of this 60-second check is tiny; the cost of skipping it is the whole interview.

### Recovery Patterns When You're Stuck

| Situation | Recovery pattern |
|-----------|-----------------|
| Can't find the optimal in 5 minutes | Commit to coding the brute force. A working O(n^2) solution beats no solution. Say: "Let me code the O(n^2) approach first, then we can optimize together." The brute-force code's redundancy often reveals the optimization pattern. |
| Silent for 60 seconds | Break the silence with structured thinking out loud: "Let me think about the structure here. The input is X, the output is Y. The key insight I'm looking for is..." Silence reads as panic; structured reasoning under pressure reads as senior. |
| Interviewer gives you a hint | Take it gracefully: "Ah, that helps, so I should be thinking about [restated insight]. Let me reconsider..." Refusing or ignoring hints is a major negative signal. Hints are gift-wrapped credit. |
| Code has a bug you can't find by reading | Don't keep re-reading. Trace through with a tiny input by hand, writing values on the whiteboard. 95% of bugs found this way. |
| Approach is wrong at minute 30 | Acknowledge cleanly: "Stepping back, I think this approach has a flaw because [reason]. Let me reconsider, I think the right approach is [pattern], because [reasoning]." Self-correction is a positive senior signal. |
| Time's running out and code isn't finished | Don't finish frantically. Finish the algorithm in pseudocode and articulate complexity. Explicit prioritization beats incomplete code with no narrative. |

### What Separates L4 / L5 / L6 in DSA Interviews

| Level | Expectations |
|-------|-------------|
| **L4 / Mid** | Solves the problem with help; arrives at a correct O(n log n) or O(n) solution; states one of time/space complexity; identifies one edge case unprompted. |
| **L5 / Senior** | Solves independently within time; states brute force first, then optimizes; states *both* time and space; identifies 3+ edge cases; handles 1-2 follow-up questions. Code is clean enough that a teammate could read it. |
| **L6 / Staff** | Same as L5 PLUS connects the problem to a broader pattern family; discusses non-obvious tradeoffs (segment tree vs Fenwick tree vs sqrt decomposition); proposes a generalization or real-world application; handles open-ended follow-ups. |

The pattern: progression isn't about solving harder problems, it's about *depth of reasoning* on the same problem.

### Anti-Patterns That Lose Points

| Anti-pattern | Why it costs points | Senior fix |
|-------------|--------------------|------------|
| Coding within 60 seconds of seeing the problem | Signals you skip clarification and risk solving the wrong problem | Take 5 minutes for clarification and approach before any code |
| Jumping to optimal without mentioning brute force | Reads as memorized; loses the decomposition signal | State brute force with complexity, then say "now let's optimize" |
| Coding silently for > 60 seconds | Interviewer cannot grade what they cannot hear | Narrate every decision |
| Single-letter variable names outside loop counters | Reads as junior; obscures intent | Use meaningful names: prefix_sum, last_seen, char_count |
| Forgetting space complexity | Half-answered complexity is a near-guaranteed L5+ downgrade | Always state both time and space |
| Saying "I'm done" without tracing a test case | Junior signal | Trace through a small input AND an edge case first |
| Refusing or ignoring an interviewer hint | Reads as defensive | Take the hint gracefully and re-derive |
| Memorized solutions for canonical problems | Falls apart on variants; interviewers ask deliberate twists | Re-derive from first principles; state the pattern explicitly |
| Adding code comments instead of explaining out loud | Comments are for the reader after; interviewer wants live reasoning | Talk through reasoning; reserve comments for non-obvious invariants |
| Defending a wrong approach when interviewer pushes back | Reads as inflexible | "Fair point, let me reconsider" followed by structured re-analysis |

### How to Practice (and What to Practice)

The wrong practice: grinding 500 LeetCode problems shallowly. The right practice: solving 100-150 problems *deeply*, organized by pattern, with a 45-minute timer and out-loud narration.

What to drill:
- **Pattern recognition under time pressure**: pick a random LeetCode medium and aim to identify the pattern within 2-3 minutes. Track which patterns you miss most often.
- **Brute-force-first habit**: even on problems you've seen before, force yourself to articulate the brute force out loud before coding the optimal.
- **Complexity stating reflex**: after every solved problem, state time and space complexity unprompted. Identify the dominant cost.
- **Edge case checklist**: empty input, single element, all-equal, sorted vs reverse-sorted, very large input, integer overflow, negative numbers, cycle in graph, duplicates. Surface 3-5 relevant ones for any problem.
- **Mock interviews with peers**: at least 5-10 mocks with someone playing interviewer, on a real whiteboard or shared editor with no autocomplete.

Coverage targets by pattern (rough): Arrays / Strings (40), Two Pointers (15), Sliding Window (15), Binary Search (15), Trees (20), Graphs (20), DP (25), Backtracking (10), Heap (10), Stack / Monotonic Stack (10), Trie (5), Union-Find (5), Bit Manipulation (5). Total ~200 problems organized by pattern beats 500 random problems.

---

## How to Design a DSA Solution: The Mechanical Playbook

Source: [CalibreOS -- How to Design a DSA Solution](https://www.calibreos.com/learn/dsa-how-to-design)

The two organizing rules:
1. **Constraints drive the data structure, the data structure drives the algorithm.** Sorted input + pair search -> two pointers. Stream + top-K -> heap. Range queries -> prefix sum. Prefix matching -> trie. Connected components -> union-find. If you cannot tie a data-structure choice to a specific access pattern, you are guessing.
2. **Brute force first, then optimize through one targeted change.** Identify the *redundant work* in the brute force and name the data structure that eliminates it. O(n^2) -> O(n): identified repeated computation and replaced with a hashmap. O(n) -> O(log n): identified monotonicity and applied binary search. The optimization is a substitution, not a rethink.

### The 5-Phase Solution Playbook

**Phase 1 -- Translate the problem into 3 properties (3 min):**
- Input shape (array, string, tree, graph, matrix).
- Constraint type (sorted? bounded values? unique? cyclic?).
- Output type (count, value, index, all valid solutions, max/min).
- These three properties narrow the pattern space from 12 families to 2-3 candidates.

**Phase 2 -- State the brute force with complexity (2 min):**
- The most naive correct solution. Usually O(n^2) or O(n^3).
- State time AND space.
- A working brute force at minute 25 beats a half-finished optimal at minute 25.

**Phase 3 -- Identify the bottleneck and the data structure that fixes it (5 min):**
- Look at the brute force's inner loop: what is it recomputing?
  - Two pointers eliminate redundant scanning of sorted data.
  - Hashmap eliminates linear search for membership.
  - Heap eliminates re-sorting after each operation.
  - Prefix sum eliminates re-summing ranges.
  - Monotonic stack eliminates re-finding the next greater element.
- The optimization is a substitution, not a rethink.

**Phase 4 -- Code the template, customize for the problem (15-20 min):**
- Know 8-10 templates by muscle memory. Customize the template; don't rewrite from scratch.

**Phase 5 -- Trace, edge case, complexity (5-10 min):**
- Trace through a small input to verify correctness.
- Surface 3-5 edge cases (empty, single, duplicates, overflow, all-equal).
- State final time AND space complexity, identifying the dominant cost.
- Discuss one tradeoff or follow-up: "If the input were streaming, I'd switch to ...; if memory were tight, I'd switch to ..."

### Data Structure Selection Decision Tree

Before writing code, name the data structure that supports your algorithm based on the access pattern:

| Access pattern needed | Data structure | Cost / tradeoff |
|---|---|---|
| O(1) membership / lookup by key | Hashmap (dict / unordered_map) | O(n) space; no ordering |
| O(log n) operations on sorted data | Sorted set / TreeMap | O(n) space; balanced BST overhead |
| Top-K or repeated min/max extraction | Heap (heapq) | O(log n) per op; no random access |
| Prefix matching / autocomplete | Trie | O(alphabet * total_chars) space |
| Connected-components / cycle (undirected) | Union-find with path compression | Near-O(alpha(n)) per op |
| Next-greater / next-smaller / histogram queries | Monotonic stack or monotonic deque | O(n) amortized; one-pass |
| Range sum / range max with point updates | Fenwick tree (BIT) or segment tree | O(log n) per op; O(n) space |
| O(1) random access AND O(1) insert at front/back | Deque (collections.deque) | O(n) space; doubly-linked |
| Ordered iteration AND O(1) lookup by key | Ordered dict + linked list (LRU pattern) | O(n) space; pointer overhead |

Common mistake: using a list when a deque is needed. `list.pop(0)` is O(n) in Python. Always use `collections.deque` for queue/BFS workloads.

### The 12 Templates You Need by Muscle Memory

Templates are not the same as memorized solutions. A template is the *skeleton* of a pattern -- the fixed control flow with placeholders for problem-specific logic. A candidate who internalized the variable-size sliding window template can solve both "longest substring without repeating characters" and "longest substring with at most K distinct characters" by customizing the inner logic. Templates are muscle memory; internalize them by writing them from scratch repeatedly, against a timer.

1. **Two Pointers (sorted, converging):** Sorted array + pair sum, palindrome, container-with-most-water. left=0, right=n-1; while left<right: advance left or right based on condition. O(n) time, O(1) space.
2. **Sliding Window (variable size):** Longest/shortest substring with property X. Expand right, shrink while invalid, update best. O(n) amortized.
3. **Sliding Window (fixed size k):** Max sum of window size k, anagram detection. Init from arr[:k], slide by add right / remove left. O(n) time, O(k) space.
4. **Binary Search (find target in sorted array):** Standard left/right/mid. O(log n).
5. **Binary Search on Answer Space:** "Minimize the maximum X" or "find smallest k such that feasible." Define feasibility(x), binary search over x in [low, high]. O(n log(max_answer)). Examples: Koko Eating Bananas, Ship Packages, Split Array.
6. **BFS (shortest path / level order):** Queue-based, process by level. O(V+E) time, O(V) space.
7. **DFS (recursive):** Connected components, cycle detection, topological sort, tree traversals. O(V+E) time, O(V) space for recursion.
8. **Monotonic Stack:** Next greater element, daily temperatures, largest rectangle in histogram. O(n) amortized.
9. **Heap (top-K):** Maintain min-heap of size K for K largest. O(n log K) time, O(K) space. Two heaps for running median: max-heap of lower half, min-heap of upper half, rebalance to differ by at most 1.
10. **Backtracking:** Permutations, combinations, subsets, N-Queens. Exponential time.
11. **DP (memoized recursion):** Count ways, min cost, longest, edit distance. Use `@lru_cache`. Convert to tabulation only if recursion depth blows the stack.
12. **Union-Find (path compression + rank):** Connected components, redundant connections, accounts merge. Near-O(alpha(n)) per op.

### The "Design a Data Structure" Subgenre -- Patterns to Recognize

These problems ask you to combine data structures to achieve specific operation complexities:

| Data structure design | Implementation | Key operations / complexity |
|---|---|---|
| **LRU / LFU cache** | LRU = hashmap + doubly linked list. LFU = hashmap + (freq -> doubly linked list of nodes) + min-freq tracker. Both O(1) get and put. Trap: using a singly linked list (O(n) remove). | O(1) get/put |
| **Min stack / max stack** | Two parallel stacks: data stack + running-min stack. On push, push min(new_value, current_min) onto min-stack. On pop, pop both. Trap: recomputing min on each pop is O(n). | O(1) push/pop/getMin |
| **Time-based key-value store** | dict[key] -> sorted list of (timestamp, value) pairs. Get does binary search on the list. set is O(1) amortized; get is O(log n). Used for distributed snapshots and time-series. | O(1) set, O(log n) get |
| **Sliding-window rate limiter** | Deque per user storing recent timestamps. On each call, drop timestamps older than (now - T), check size < N, append new. O(1) amortized per op. Production uses Redis sorted sets. | O(1) amortized per check |
| **Autocomplete trie** | Trie with each node storing a heap (or sorted list) of top-K completions. Insert is O(L log K); search is O(L + K). Used by search engines, IDE autocomplete. | O(L log K) insert, O(L + K) search |
| **Twitter-feed-style top-N** | Per-user list of recent tweets + heap-based merge of followed users' lists at read time. O(F log F) per getNewsFeed where F = followed count. | O(F log F) per read |
| **Running median from stream** | Two heaps: max-heap of lower half, min-heap of upper half. Rebalance so heaps differ in size by at most 1. Median = top of larger heap or average of both tops. O(log n) insert, O(1) findMedian. | O(log n) insert, O(1) median |

### Common Mistakes That Sink DSA Interviews

- **Off-by-one in binary search bounds:** `while left < right` vs `while left <= right` require different update rules. Pick one variant and use it consistently.
- **Mutating the input you're iterating over:** Removing elements from a list while iterating causes silent index skipping. Iterate over a copy or build a new list.
- **Using list.pop(0) in BFS:** This is O(n). Always use `collections.deque` and `popleft()`.
- **Forgetting to mark visited in graph DFS/BFS:** Leads to infinite loops on cycles. Mark BEFORE recursing or enqueueing.
- **Wrong base case in DP recursion:** `dp(0)` for an empty subproblem must return the identity for your operation (0 for sum, 1 for product, infinity for min, -infinity for max).
- **Integer overflow in sum-based problems:** In Java/C++, summing 10^4 elements each up to 10^9 overflows 32-bit int. Use `long long`.
- **Confusing 'subsequence' with 'subarray':** Subarray is contiguous (sliding window applies); subsequence is not contiguous (DP usually applies).
- **Stack overflow on deep recursion:** Python default recursion limit is 1000. For depth > 10^3, set sys.setrecursionlimit() or convert to iterative DFS.
- **Mutating shared state in backtracking:** Forgetting to undo the choice (path.pop()) after recursing. Always pair modification with undo.

### Code Style for Interviews (What Reads as Senior)

- **Meaningful variable names:** `prefix_sum`, `last_seen_index`, `char_count` -- not `a`, `b`, `tmp`. Loop counters `i, j, r, c` are fine when unambiguous.
- **Helper functions for non-trivial logic:** If a check appears twice, extract it. Reduces bug surface.
- **Type hints on function signatures (Python):** `def solve(arr: list[int], k: int) -> int:` signals production code habits.
- **Constants for magic numbers:** `MAX_PRICE = 10**9` instead of inline `10**9`.
- **Comments only for non-obvious invariants:** "window [left, right] always contains at most k distinct chars after this loop" -- yes. "increment i" -- no.
- **Early returns for edge cases:** Handle empty input, single element, etc., at the top of the function.
- **Avoid deeply nested conditionals:** More than 3 levels of nesting is a smell. Extract to a helper or invert conditions.
- **No dead code, no commented-out attempts:** Clean up after yourself.
