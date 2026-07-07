# Coding Playbook — Deep C++/Systems Analysis (Flashcards)

Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>What is the HackerRank OA + onsite coding loop structure?</b></summary>

Topic: OA & Onsite Coding Playbook
Key concepts:
- HackerRank OA: 90 min, 2 coding problems (LeetCode Med-Hard: arrays, bitwise, intervals, graphs) + 10-15 MCQs on OS internals, computer architecture, C++ basics. Need 100% on coding + high MCQ accuracy to advance.
- MCQ core: CPU scheduling (priority inversion/inheritance, MLFQ), context-switch/TLB/page-fault costs, thread memory model (shared heap, private stack), vtables/dynamic-dispatch inlining penalty, pointer sizing/alignment.
- Onsite evolution: a single problem is escalated naive → optimized → cache-aware → concurrent (thread-safety/locks) → GPU/hardware-aware, e.g., a sharded concurrent cache design.
File: [hackerrank_and_inperson_coding.md](../../hackerrank_and_inperson_coding.md)
</details>

<details><summary><b>Design an LRU Cache with O(1) get/put (low-level systems)</b></summary>

Topic: LRU Cache (LC 146)
Key concepts:
- HashMap (key → node) + doubly linked list; `get`/`put` move the node to the head (most-recently-used) and evict from the tail in O(1).
- Low-level expectation: implement the linked list from scratch with raw/custom pointer nodes (not `std::list`), to show manual pointer manipulation and cache-conscious layout.
- Python variant uses `collections.OrderedDict` or `__slots__` to cut per-node memory; advanced follow-up is Segmented Caching (shard locks to reduce contention).
File: [coding_lru_cache.md](../../coding_lru_cache.md)
</details>

<details><summary><b>Search in Rotated Sorted Array — algorithm + systems gotchas</b></summary>

Topic: Search in Rotated Sorted Array (LC 33/81)
Key concepts:
- Modified binary search: at least one half is always sorted. If `nums[left] <= nums[mid]` the left half is sorted; check if target lies in `[left, mid)` and narrow accordingly, else go right.
- Systems gotchas: branch prediction penalties from the unpredictable comparison; warp divergence on GPUs (threads take both sides); floor-division/float-precision loss in the midpoint; Python list slicing copies sublists.
File: [coding_search_rotated_array.md](../../coding_search_rotated_array.md)
</details>

<details><summary><b>Number of Islands — DFS vs BFS and GC optimization</b></summary>

Topic: Number of Islands (LC 200)
Key concepts:
- Flood fill each `'1'` cell via DFS or BFS, marking visited land; the count of flood fills is the island count.
- Recursion depth limits: deep DFS on large grids blows the Python/C stack → switch to iterative BFS with a `collections.deque`.
- GC optimization: map 2D `(r, c)` to a 1D index so the visited set holds integers (cheaper, fewer tuple allocations) and the flood fill produces less garbage to collect.
File: [coding_number_of_islands.md](../../coding_number_of_islands.md)
</details>

<details><summary><b>Merge Intervals — move semantics, Timsort, key sort</b></summary>

Topic: Merge Intervals (LC 56)
Key concepts:
- Sort by start, then iterate: if current start > last merged end, append; else merge by taking max of ends. Merge in-place in the input vector to save memory.
- C++ uses `std::move` to avoid deep copies / vector reallocation of inner elements; Python relies on Timsort (adaptive, stable) whereas C++ uses Introsort (quicksort → heapsort on depth).
- `list.sort(key=...)` in CPython runs the key extraction in C, making `sort(key=lambda i: i[0])` faster than a comparator function.
File: [coding_merge_intervals.md](../../coding_merge_intervals.md)
</details>

<details><summary><b>Course Schedule — cycle detection and graph representation</b></summary>

Topic: Course Schedule (LC 207)
Key concepts:
- Isomorphic to detecting a cycle in a directed graph. Kahn's algorithm (BFS topological sort) is preferred in production: count in-degrees, enqueue zero-in-degree nodes, decrement neighbors, and confirm all nodes are emitted.
- Recursive-free (no stack overflow risk) and models queue-based resource schedulers; alternative is 3-state DFS coloring (white/gray/black).
- Performance: pre-allocate adjacency lists (avoid `defaultdict` overhead); CSR (Compressed Sparse Row) representation gives cache-friendly, contiguous edge storage for large graphs.
File: [coding_course_schedule.md](../../coding_course_schedule.md)
</details>

<details><summary><b>Implement a Trie — RAII, setdefault trap, destructor leaks</b></summary>

Topic: Implement Trie (LC 208)
Key concepts:
- `insert`/`search`/`startsWith` walk child pointers per character; mark terminal nodes with an `is_end` flag.
- C++: use `std::unique_ptr` for children so RAII auto-frees the subtree (no manual destructor). Python: nested dicts work but `dict.setdefault(k, {})` eagerly constructs a new dict on every call even when the key exists — a performance trap.
- Deep recursion in a destructor can overflow the stack on tall tries; iterative teardown or smart pointers avoid the leak/overflow.
File: [coding_trie.md](../../coding_trie.md)
</details>

---

[Flashcard Index](../README.md)
