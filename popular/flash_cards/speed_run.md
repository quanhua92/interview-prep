# Speed Run Deck — 48 Curated Cards (7-Day Cherry-Pick)

The highest-yield items from the 7-day speed run. Drill this as one deck. Each card: trigger → pattern/move → file link. Click the bold text to reveal.

---

## Day 1 — Two Pointers + Sliding Window

<details><summary><b>Two Sum (sorted array): two elements sum to target</b></summary>

Pattern: Two Pointers — `L = 0`, `R = n - 1`; move the pointer that improves the sum.
File: [tiers/foundation/coding_two_sum.md](../tiers/foundation/coding_two_sum.md)
</details>

<details><summary><b>3Sum: unique triplets summing to zero</b></summary>

Pattern: Sort + fix-one + two-pointer on the rest; skip duplicate values at each anchor.
File: [tiers/foundation/coding_three_sum.md](../tiers/foundation/coding_three_sum.md)
</details>

<details><summary><b>Container With Most Water: maximize area between two lines</b></summary>

Pattern: Two pointers from the ends; always move the *shorter* line inward (moving the taller can only shrink area).
File: [tiers/foundation/coding_container_water.md](../tiers/foundation/coding_container_water.md)
</details>

<details><summary><b>Longest Substring Without Repeating Characters</b></summary>

Pattern: Variable sliding window + dict of last-seen index; jump `left` past the repeat.
File: [tiers/foundation/coding_longest_substring.md](../tiers/foundation/coding_longest_substring.md)
</details>

<details><summary><b>Find All Anagrams: all start indices of p's anagram in s</b></summary>

Pattern: Fixed-width sliding window + frequency-map match (compare counters, not substrings).
File: [tiers/foundation/coding_find_anagrams.md](../tiers/foundation/coding_find_anagrams.md)
</details>

<details><summary><b>Longest Repeating Character Replacement: longest substring after K replacements</b></summary>

Pattern: Variable window; track max char freq in window, shrink while `window - max_freq > K`.
File: [tiers/foundation/coding_longest_repeating_char.md](../tiers/foundation/coding_longest_repeating_char.md)
</details>

<details><summary><b>Permutation in String: does s2 contain a permutation of s1?</b></summary>

Pattern: Fixed window (len = s1) sliding over s2; frequency arrays must match.
File: [tiers/foundation/coding_permutation_in_string.md](../tiers/foundation/coding_permutation_in_string.md)
</details>

## Day 2 — Intervals + BFS/DFS

<details><summary><b>Merge Intervals: merge overlapping intervals</b></summary>

Pattern: Sort by start, then merge sequentially (extend end to max of overlapping ends).
File: [tiers/foundation/coding_merge_intervals.md](../tiers/foundation/coding_merge_intervals.md)
</details>

<details><summary><b>Insert Interval: insert a new interval into a sorted, non-overlapping list</b></summary>

Pattern: Three-phase — copy all before, merge all overlapping, copy all after.
File: [tiers/foundation/coding_insert_interval.md](../tiers/foundation/coding_insert_interval.md)
</details>

<details><summary><b>Meeting Rooms II: minimum meeting rooms required</b></summary>

Pattern: Sweep line (sort all start/end events) OR min-heap of end times; peak overlap is the answer.
File: [tiers/foundation/coding_meeting_rooms.md](../tiers/foundation/coding_meeting_rooms.md)
</details>

<details><summary><b>Binary Tree Level Order Traversal</b></summary>

Pattern: BFS with a queue; capture `len(queue)` at each level to batch nodes into one sublist.
File: [tiers/foundation/coding_level_order.md](../tiers/foundation/coding_level_order.md)
</details>

<details><summary><b>Rotting Oranges: time until all oranges rot</b></summary>

Pattern: Multi-source BFS — enqueue all rotten oranges at t=0, count remaining fresh, return minutes when fresh hits 0.
File: [tiers/foundation/coding_rotting_oranges.md](../tiers/foundation/coding_rotting_oranges.md)
</details>

<details><summary><b>Number of Islands: count islands in a grid</b></summary>

Pattern: DFS or BFS flood fill on each unvisited `'1'`; mark visited in-place or via a set.
File: [tiers/intermediate/coding_number_of_islands.md](../tiers/intermediate/coding_number_of_islands.md)
</details>

<details><summary><b>Linked List Cycle: detect a cycle</b></summary>

Pattern: Floyd's tortoise and hare — slow moves 1, fast moves 2; they meet iff a cycle exists.
File: [tiers/foundation/coding_linked_list_cycle.md](../tiers/foundation/coding_linked_list_cycle.md)
</details>

## Day 3 — Binary Search + DP + Stack + Top K

<details><summary><b>Binary Search: classic search in a sorted array</b></summary>

Pattern: `mid = L + (R - L) // 2` (overflow-safe); narrow to the half containing the target.
File: [tiers/intermediate/coding_binary_search.md](../tiers/intermediate/coding_binary_search.md)
</details>

<details><summary><b>First Bad Version: find first bad via an API</b></summary>

Pattern: Left-biased binary search — when `isBadVersion(mid)` is true, keep searching left (`R = mid`).
File: [tiers/intermediate/coding_first_bad_version.md](../tiers/intermediate/coding_first_bad_version.md)
</details>

<details><summary><b>Koko Eating Bananas: minimum eating speed to finish in H hours</b></summary>

Pattern: Binary search on the *answer* (speed in [1, max(piles)]); feasibility = total hours <= H.
File: [tiers/advanced/coding_koko_bananas.md](../tiers/advanced/coding_koko_bananas.md)
</details>

<details><summary><b>Climbing Stairs: number of ways to climb n stairs</b></summary>

Pattern: Fibonacci DP — `dp[i] = dp[i-1] + dp[i-2]`; O(1) space with two rolling variables.
File: [tiers/intermediate/coding_climbing_stairs.md](../tiers/intermediate/coding_climbing_stairs.md)
</details>

<details><summary><b>House Robber: max money without robbing adjacent houses</b></summary>

Pattern: DP — `dp[i] = max(dp[i-1], dp[i-2] + nums[i])` i.e. max(skip, rob this one).
File: [tiers/intermediate/coding_house_robber.md](../tiers/intermediate/coding_house_robber.md)
</details>

<details><summary><b>Coin Change: minimum coins to make an amount</b></summary>

Pattern: Unbounded knapsack DP — `dp[a] = min(dp[a], 1 + dp[a - coin])` for each coin.
File: [tiers/intermediate/coding_coin_change.md](../tiers/intermediate/coding_coin_change.md)
</details>

<details><summary><b>Valid Parentheses: validate bracket nesting</b></summary>

Pattern: Stack with an expected-closer map — push the matching closer for each opener, pop and compare on close.
File: [tiers/intermediate/coding_valid_parentheses.md](../tiers/intermediate/coding_valid_parentheses.md)
</details>

<details><summary><b>Min Stack: O(1) push/pop/getMin</b></summary>

Pattern: Auxiliary min-stack tracking the running minimum, or encode the delta against the previous min.
File: [tiers/intermediate/coding_min_stack.md](../tiers/intermediate/coding_min_stack.md)
</details>

<details><summary><b>Kth Largest Element in an Array</b></summary>

Pattern: Quickselect (avg O(n)) or a size-k min-heap (O(n log k)) holding the k largest seen.
File: [tiers/intermediate/coding_kth_largest.md](../tiers/intermediate/coding_kth_largest.md)
</details>

<details><summary><b>Top K Frequent Elements</b></summary>

Pattern: Bucket sort (index = frequency, O(n)) or a size-k min-heap on frequency counts.
File: [tiers/intermediate/coding_top_k_frequent.md](../tiers/intermediate/coding_top_k_frequent.md)
</details>

## Day 4 — Subsets + Trie + Graph + Greedy + Monotonic Stack

<details><summary><b>Subsets: all subsets of an array</b></summary>

Pattern: Cascading backtracking (include/exclude each element) or bitmask iteration over 2^n masks.
File: [tiers/advanced/coding_subsets.md](../tiers/advanced/coding_subsets.md)
</details>

<details><summary><b>Permutations: all permutations of an array</b></summary>

Pattern: In-place swap backtracking — swap index i with each j >= i, recurse, then swap back.
File: [tiers/advanced/coding_permutations.md](../tiers/advanced/coding_permutations.md)
</details>

<details><summary><b>Combination Sum: combinations summing to target (reuse allowed)</b></summary>

Pattern: Backtracking with index preservation — recurse from the same index to allow reuse, advance index to avoid it.
File: [tiers/advanced/coding_combination_sum.md](../tiers/advanced/coding_combination_sum.md)
</details>

<details><summary><b>Implement Trie: insert / search / startsWith</b></summary>

Pattern: Prefix tree with child-pointer nodes per character; mark terminal nodes with an `is_end` flag.
File: [tiers/advanced/coding_implement_trie.md](../tiers/advanced/coding_implement_trie.md)
</details>

<details><summary><b>Word Search II: find all board words from a dictionary</b></summary>

Pattern: Build a Trie from the words, DFS flood-fill the board, prune branches whose prefix is not in the Trie.
File: [tiers/advanced/coding_word_search_ii.md](../tiers/advanced/coding_word_search_ii.md)
</details>

<details><summary><b>Course Schedule: can all courses be finished? (cycle detection)</b></summary>

Pattern: Kahn's BFS topological sort (in-degree queue) or 3-state DFS coloring; cycle ⇒ impossible.
File: [tiers/expert/coding_course_schedule.md](../tiers/expert/coding_course_schedule.md)
</details>

<details><summary><b>Course Schedule II: return a valid topological order</b></summary>

Pattern: Kahn's BFS — emit zero-in-degree nodes, decrement neighbors, repeat; empty output ⇒ cycle.
File: [tiers/expert/coding_course_schedule_ii.md](../tiers/expert/coding_course_schedule_ii.md)
</details>

<details><summary><b>Jump Game: can you reach the last index?</b></summary>

Pattern: Greedy — track `max_reach` from the back or front; if `i > max_reach`, you're stuck.
File: [tiers/expert/coding_jump_game.md](../tiers/expert/coding_jump_game.md)
</details>

<details><summary><b>Gas Station: find the start index for a full circuit</b></summary>

Pattern: Track total surplus (must be >= 0 overall) and a running sum; reset the candidate start when the running sum goes negative.
File: [tiers/expert/coding_gas_station.md](../tiers/expert/coding_gas_station.md)
</details>

<details><summary><b>Daily Temperatures: days until a warmer temperature</b></summary>

Pattern: Monotonic decreasing stack of indices; when a warmer day arrives, pop and record index offsets.
File: [tiers/expert/coding_daily_temperatures.md](../tiers/expert/coding_daily_temperatures.md)
</details>

## Day 5 — Core Deep Files

<details><summary><b>HackerRank OA + onsite coding playbook</b></summary>

Move: 90-min OA = 2 coding + 10-15 MCQs (OS/arch/C++); onsite escalates one problem naive → optimized → cache → concurrent → GPU-aware.
File: [hackerrank_and_inperson_coding.md](../hackerrank_and_inperson_coding.md)
</details>

<details><summary><b>STAR — Intellectual Honesty: failed hypothesis</b></summary>

Move: Admit the optimization hypothesis was wrong (profile disproved it), pivot fast to the real bottleneck, never defend a personal design against the data.
File: [behavioral_star_intellectual_honesty.md](../behavioral_star_intellectual_honesty.md)
</details>

<details><summary><b>STAR — One Team: cross-functional interface bottleneck</b></summary>

Move: Bypass tickets, walk to the other team's lab, frame the debug around shared truth; zero finger-pointing under a hard deadline.
File: [behavioral_star_one_team.md](../behavioral_star_one_team.md)
</details>

<details><summary><b>LRU Cache deep: O(1) get/put with systems follow-ups</b></summary>

Move: HashMap + doubly linked list, move-to-front on access; low-level expects hand-built pointer nodes, `__slots__`, Segmented Caching.
File: [coding_lru_cache.md](../coding_lru_cache.md)
</details>

<details><summary><b>Merge Intervals deep: C++/Python systems analysis</b></summary>

Move: Sort + merge; `std::move` to avoid copies, in-place merge; Timsort vs Introsort; `sort(key=...)` runs key extraction in C.
File: [coding_merge_intervals.md](../coding_merge_intervals.md)
</details>

<details><summary><b>Number of Islands deep: recursion limits, iterative BFS, GC</b></summary>

Move: Flood fill; iterative BFS avoids stack overflow; 1D index mapping reduces tuple allocations and GC pressure.
File: [coding_number_of_islands.md](../coding_number_of_islands.md)
</details>

<details><summary><b>Python GIL: mechanism and bypass routes</b></summary>

Move: Single mutex on bytecode (ref-count safety); 5 ms switch interval; bypass via C-extension `Py_BEGIN_ALLOW_THREADS`, `multiprocessing`, or PEP 703 free-threaded.
File: [system_lowlevel_python_gil_concurrency.md](../system_lowlevel_python_gil_concurrency.md)
</details>

<details><summary><b>Python memory & GC: ref counting, cyclic GC, PyMalloc</b></summary>

Move: `ob_refcnt` immediate free + generational cyclic GC + PyMalloc arenas (256 KB → 4 KB pools → blocks); debug CUDA leaks with `tracemalloc`/`objgraph`.
File: [system_lowlevel_python_memory_gc.md](../system_lowlevel_python_memory_gc.md)
</details>

## Day 6 — System Design + Role-Specific

<details><summary><b>Distributed task scheduler with cooldown across machines</b></summary>

Move: Max-heap + cooldown wait-queue; distributed via `SKIP LOCKED` DB rows + Redis-lease TTL locks to enforce global cooldown.
File: [system_design_task_scheduler_multiple_machines.md](../system_design_task_scheduler_multiple_machines.md)
</details>

<details><summary><b>Triton inference server for LLM serving</b></summary>

Move: Dynamic + in-flight (continuous) batching so the GPU never idles; Paged KV Cache (OS-style paging) cuts fragmentation and lifts HBM use above 80%.
File: [system_design_triton_inference_server.md](../system_design_triton_inference_server.md)
</details>

<details><summary><b>GPU microservices: H2D bottleneck, MIG vs MPS</b></summary>

Move: Async buffer + KEDA; pin host memory and overlap H2D copies via CUDA streams; MIG = hard partition, MPS = shared address space (more throughput, weaker isolation).
File: [system_design_gpu_microservices_bottleneck.md](../system_design_gpu_microservices_bottleneck.md)
</details>

<details><summary><b>Producer-Consumer: circular buffer, condition variables, GIL</b></summary>

Move: Vector-backed circular ring + two condition variables + shutdown flag; Python `queue.Queue` is GIL-serialized, use `multiprocessing` for true parallelism.
File: [system_lowlevel_concurrency_producer_consumer.md](../system_lowlevel_concurrency_producer_consumer.md)
</details>

<details><summary><b>Aligned malloc: bitwise masks, PyMalloc, SIMD alignment</b></summary>

Move: `p2 = (p1 + sizeof(void*) + align - 1) & ~(align - 1)`; store raw pointer before `p2`; alignment is critical for SIMD loads and cache-line/page boundaries.
File: [system_lowlevel_memory_aligned_malloc.md](../system_lowlevel_memory_aligned_malloc.md)
</details>

<details><summary><b>C-bindings: ctypes/cffi/pybind11/Cython, RAII wrappers</b></summary>

Move: ctypes no-compile but slowest (~100 ns); pybind11/Cython fastest; zero-copy NumPy via `.ctypes.data` + `ndpointer`; RAII wrappers for safe lifetime control.
File: [system_lowlevel_python_c_bindings_ctypes.md](../system_lowlevel_python_c_bindings_ctypes.md)
</details>

---

[Flashcard Index](README.md)
