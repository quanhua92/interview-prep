# Tier 2: Intermediate — Coding Interview Preparation Roadmap

Welcome to the **Intermediate (Tier 2) Coding Roadmap**. This directory contains your structured study guide and indexed reference repository for mastering intermediate algorithmic design. These patterns extend the foundational structures to cover complex range queries, non-linear traversals, heap-based priority systems, low-level bit states, and dynamic programming optimization.

---

## 🗺️ Progression Roadmap

To tackle intermediate problems, follow a systematic progression that moves from linear sum/search concepts into trees, priority queues, and advanced memoization.

```text
┌────────────────────────────────────────┐
│  Step 1: Ranges & Bounds               │
│  (Prefix Sum & Binary Search)          │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 2: Non-Linear Traversal          │
│  (Stack & DFS)                         │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 3: Heap & Sorting                │
│  (D&C, Two Heaps & Top K)              │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 4: Machine State                 │
│  (Bit Manipulation)                    │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 5: Probability & Coordinates     │
│  (Math & Randomized)                   │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 6: Optimized Choices             │
│  (DP & Object Design)                  │
└────────────────────────────────────────┘
```

---

## 📈 Detailed Learning Modules & File Index

Here is the complete catalog of the 63 Intermediate problems, categorized by pattern, and arranged in recommended learning order.

### Module 1: Prefix Sum & Binary Search
*Goal: Search ranges, resolve subarray sums, and optimize threshold searches in logarithmic time.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Prefix Sum** | [Product of Array Except Self](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_product_except_self.md) | [LeetCode 238](https://leetcode.com/problems/product-of-array-except-self/) | Medium | Prefix/Suffix arrays consolidation, $\mathcal{O}(1)$ space |
| **Prefix Sum** | [Subarray Sum Equals K](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_subarray_sum_equals_k.md) | [LeetCode 560](https://leetcode.com/problems/subarray-sum-equals-k/) | Medium | Cumulative sum hashing, frequency lookups |
| **Prefix Sum** | [Subarray Product Less Than K](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_subarray_product_less_than_k.md) | [LeetCode 713](https://leetcode.com/problems/subarray-product-less-than-k/) | Medium | Sliding window integration, combinatorics addition |
| **Prefix Sum** | [Continuous Subarray Sum](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_continuous_subarray_sum.md) | [LeetCode 523](https://leetcode.com/problems/continuous-subarray-sum/) | Medium | Modulo hash matching, remainder tracking |
| **Prefix Sum** | [Contiguous Array](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_contiguous_array.md) | [LeetCode 525](https://leetcode.com/problems/contiguous-array/) | Medium | Zero-one replacement offset, max distance |
| **Prefix Sum** | [Random Pick with Weight](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_random_pick_with_weight.md) | [LeetCode 528](https://leetcode.com/problems/random-pick-with-weight/) | Medium | Cumulative probability array, binary search lookup |
| **Binary Search** | [Find Minimum in Rotated Sorted](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_find_min_rotated.md) | [LeetCode 153](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) | Medium | Unsorted-half boundaries, inflection identification |
| **Binary Search** | [First Bad Version](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_first_bad_version.md) | [LeetCode 278](https://leetcode.com/problems/first-bad-version/) | Easy | Left-biased convergence, API minimization |
| **Binary Search** | [Data Stream as Disjoint Intervals](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_data_stream_as_disjoint_intervals.md) | [LeetCode 352](https://leetcode.com/problems/data-stream-as-disjoint-intervals/) | Hard | Ordered tree boundaries lookup, interval merges |
| **Binary Search** | [Russian Doll Envelopes](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_russian_doll_envelopes.md) | [LeetCode 354](https://leetcode.com/problems/russian-doll-envelopes/) | Hard | Dual criteria sorting, Longest Increasing Subsequence (LIS) |
| **Binary Search** | [Smallest Good Base](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_smallest_good_base.md) | [LeetCode 483](https://leetcode.com/problems/smallest-good-base/) | Hard | Base representation math, geometric series binary search |
| **Binary Search** | [Random Point in Rectangles](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_random_point_in_non_overlapping_rectangles.md) | [LeetCode 497](https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/) | Medium | Weight areas prefix sums, coordinate binary search |
| **Binary Search** | [Binary Search](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_binary_search.md) | [LeetCode 704](https://leetcode.com/problems/binary-search/) | Easy | Classical mid-point search, overflow protection |

### Module 2: Stack Parsing & Depth-First Search (DFS)
*Goal: Process nested structures, validate expressions, and exhaustively explore graphs and binary trees.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Stack** | [Valid Parentheses](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_valid_parentheses.md) | [LeetCode 20](https://leetcode.com/problems/valid-parentheses/) | Easy | Expected closing bracket mapping, size validations |
| **Stack** | [Min Stack](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_min_stack.md) | [LeetCode 155](https://leetcode.com/problems/min-stack/) | Easy | Auxiliary stack matching, difference-tracking values |
| **Stack** | [Decode String](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_decode_string.md) | [LeetCode 394](https://leetcode.com/problems/decode-string/) | Medium | Count-and-buffer stacks, nested brackets tracking |
| **DFS** | [Jump Game III](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_jump_game_three.md) | [LeetCode 1306](https://leetcode.com/problems/jump-game-iii/) | Medium | Visited negations, array traversal limits |
| **DFS** | [Number of Islands](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_number_of_islands.md) | [LeetCode 200](https://leetcode.com/problems/number-of-islands/) | Medium | Grid cell mutation, island perimeter floodfill |
| **DFS** | [Mini Parser](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_mini_parser.md) | [LeetCode 385](https://leetcode.com/problems/mini-parser/) | Medium | Nested integer parsing, tree recursion |
| **DFS** | [Longest Absolute File Path](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_longest_absolute_file_path.md) | [LeetCode 388](https://leetcode.com/problems/longest-absolute-file-path/) | Medium | Directory depth mapping, stack level calculations |
| **DFS** | [Delete Node in a BST](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_delete_node_in_a_bst.md) | [LeetCode 450](https://leetcode.com/problems/delete-node-in-a-bst/) | Medium | Successor replacement, sub-tree structure rewires |
| **DFS** | [Most Frequent Subtree Sum](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_most_frequent_subtree_sum.md) | [LeetCode 508](https://leetcode.com/problems/most-frequent-subtree-sum/) | Medium | Post-order traversal sums, hashmap frequencies tracking |
| **DFS** | [Convert BST to Greater Tree](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_convert_bst_to_greater_tree.md) | [LeetCode 538](https://leetcode.com/problems/convert-bst-to-greater-tree/) | Medium | Reverse in-order traversal, accumulative values |
| **DFS** | [Array Nesting](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_array_nesting.md) | [LeetCode 565](https://leetcode.com/problems/array-nesting/) | Medium | Permutation cycle length, value negation marker |
| **DFS** | [Subtree of Another Tree](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_subtree_of_another_tree.md) | [LeetCode 572](https://leetcode.com/problems/subtree-of-another-tree/) | Easy | Tree matching recursion, tree hashing alternative |
| **DFS** | [Max Area of Island](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_max_area_island.md) | [LeetCode 695](https://leetcode.com/problems/max-area-of-island/) | Medium | Recursive area accumulation, in-place land sink |

### Module 3: Heap, Divide & Conquer, and Priority Systems
*Goal: Split and solve subproblems, manage dynamic midpoints, and process top elements in stream collections.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Divide & Conquer** | [Merge K Sorted Lists](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_merge_k_sorted_lists.md) | [LeetCode 23](https://leetcode.com/problems/merge-k-sorted-lists/) | Hard | Min-heap node extraction, partition merge sort |
| **Divide & Conquer** | [Majority Element](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_majority_element.md) | [LeetCode 169](https://leetcode.com/problems/majority-element/) | Easy | Boyer-Moore Voting Algorithm, partition checks |
| **Divide & Conquer** | [Construct Quad Tree](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_construct_quad_tree.md) | [LeetCode 427](https://leetcode.com/problems/construct-quad-tree/) | Medium | Quad-partition matrix recursion, leaf collapses |
| **Divide & Conquer** | [Reverse Pairs](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_reverse_pairs.md) | [LeetCode 493](https://leetcode.com/problems/reverse-pairs/) | Hard | Merge sort index tracking, inversion count |
| **Divide & Conquer** | [Sort an Array](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_sort_an_array.md) | [LeetCode 912](https://leetcode.com/problems/sort-an-array/) | Medium | Quicksort/Mergesort/Heapsort implementation safety |
| **Two Heaps** | [Find Median from Data Stream](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_median_finder.md) | [LeetCode 295](https://leetcode.com/problems/find-median-from-data-stream/) | Hard | Min-Heap/Max-Heap balancing, stream size constraints |
| **Two Heaps** | [Design Twitter](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_design_twitter.md) | [LeetCode 355](https://leetcode.com/problems/design-twitter/) | Medium | User follow lists, heap merge sorted newsfeed posts |
| **Two Heaps** | [Sliding Window Median](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_sliding_window_median.md) | [LeetCode 480](https://leetcode.com/problems/sliding-window-median/) | Hard | Double heaps with lazy removal, multiset BST |
| **Top K Elements** | [Kth Largest in Array](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_kth_largest.md) | [LeetCode 215](https://leetcode.com/problems/kth-largest-element-in-an-array/) | Medium | Quickselect partition, small min-heap |
| **Top K Elements** | [Top K Frequent Elements](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_top_k_frequent.md) | [LeetCode 347](https://leetcode.com/problems/top-k-frequent-elements/) | Medium | Frequency mapping, bucket sort, min-heap |
| **Top K Elements** | [Trapping Rain Water II](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_trapping_rain_water_ii.md) | [LeetCode 407](https://leetcode.com/problems/trapping-rain-water-ii/) | Hard | 3D grid cell boundary priority queue BFS |
| **Top K Elements** | [K Closest Points to Origin](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_k_closest_points.md) | [LeetCode 973](https://leetcode.com/problems/k-closest-points-to-origin/) | Medium | Euclidean distance calculation, max-heap size limit |
| **Randomized** | [Implement Rand10() Using Rand7()](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_implement_rand10_using_rand7.md) | [LeetCode 470](https://leetcode.com/problems/implement-rand10-using-rand7/) | Medium | Rejection sampling, base-7 multiplication representation |
| **Randomized** | [Random Flip Matrix](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_random_flip_matrix.md) | [LeetCode 519](https://leetcode.com/problems/random-flip-matrix/) | Medium | Map-based index redirection swaps, random bounds shrinking |

### Module 4: Bit Manipulation
*Goal: Extract binary states, manage masks, and perform fast word-level operations using bitwise operators.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Bit Manipulation** | [Number of 1 Bits](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_number_of_1_bits.md) | [LeetCode 191](https://leetcode.com/problems/number-of-1-bits/) | Easy | Brian Kernighan's bit-unset (`n & (n - 1)`) |
| **Bit Manipulation** | [Single Number](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_single_number.md) | [LeetCode 136](https://leetcode.com/problems/single-number/) | Easy | XOR self-cancellation (`x ^ x = 0`), parity accumulation |
| **Bit Manipulation** | [Counting Bits](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_counting_bits.md) | [LeetCode 338](https://leetcode.com/problems/counting-bits/) | Easy | DP bit states, offset masks (`dp[i] = dp[i >> 1] + (i & 1)`) |
| **Bit Manipulation** | [Number Complement](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_number_complement.md) | [LeetCode 476](https://leetcode.com/problems/number-complement/) | Easy | Binary bit-mask building, XOR negations |

### Module 5: Intermediate Mathematics
*Goal: Formulate probabilistic logic, coordinate distributions, and number theory solutions.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Math** | [Poor Pigs](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_poor_pigs.md) | [LeetCode 458](https://leetcode.com/problems/poor-pigs/) | Hard | Base-state info theory, dimensions representation |
| **Math** | [Random Point in Circle](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_generate_random_point_in_a_circle.md) | [LeetCode 478](https://leetcode.com/problems/generate-random-point-in-a-circle/) | Medium | Inverse transform sampling, square root radius scale |
| **Math** | [Largest Palindrome Product](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_largest_palindrome_product.md) | [LeetCode 479](https://leetcode.com/problems/largest-palindrome-product/) | Hard | Palindrome construction, search factor limits, modulo |
| **Math** | [Next Greater Element III](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_next_greater_element_iii.md) | [LeetCode 556](https://leetcode.com/problems/next-greater-element-iii/) | Medium | Next permutation algorithm, signed integer overflow check |
| **Math** | [Find Closest Palindrome](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_find_the_closest_palindrome.md) | [LeetCode 564](https://leetcode.com/problems/find-the-closest-palindrome/) | Hard | Half-string mirroring, edge cases boundaries |

### Module 6: Dynamic Programming & High-Level System Design
*Goal: Resolve complex overlapping subproblems and design cache eviction systems with strict time constraints.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Dynamic Programming** | [Climbing Stairs](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_climbing_stairs.md) | [LeetCode 70](https://leetcode.com/problems/climbing-stairs/) | Easy | Fibonacci sequence, state transition space reduction |
| **Dynamic Programming** | [House Robber](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_house_robber.md) | [LeetCode 198](https://leetcode.com/problems/house-robber/) | Medium | 1D DP state choices (`max(rob, skip)`), in-place variables |
| **Dynamic Programming** | [Coin Change](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_coin_change.md) | [LeetCode 322](https://leetcode.com/problems/coin-change/) | Medium | 1D knapsack DP, unbounded change, infinite state sentinel |
| **Dynamic Programming** | [Frog Jump](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_frog_jump.md) | [LeetCode 403](https://leetcode.com/problems/frog-jump/) | Hard | DFS with memoized states, step distance increments |
| **Dynamic Programming** | [Count The Repetitions](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_count_the_repetitions.md) | [LeetCode 466](https://leetcode.com/problems/count-the-repetitions/) | Hard | Cycle matching detection, repeating states offsets |
| **Dynamic Programming** | [Unique Substrings Wraparound](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_unique_substrings_in_wraparound_string.md) | [LeetCode 467](https://leetcode.com/problems/unique-substrings-in-wraparound-string/) | Medium | Alphabet distance loop constraints, max length tracking per char |
| **Dynamic Programming** | [Freedom Trail](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_freedom_trail.md) | [LeetCode 514](https://leetcode.com/problems/freedom-trail/) | Hard | State choice matrix, character distance transitions |
| **Dynamic Programming** | [Longest Palindromic Subseq](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_longest_palindromic_subsequence.md) | [LeetCode 516](https://leetcode.com/problems/longest-palindromic-subsequence/) | Medium | 2D substring range DP, state compression |
| **Dynamic Programming** | [Coin Change II](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_coin_change_ii.md) | [LeetCode 518](https://leetcode.com/problems/coin-change-ii/) | Medium | Unbounded knapsack combinations, loop ordering |
| **Dynamic Programming** | [Student Attendance II](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_student_attendance_record_ii.md) | [LeetCode 552](https://leetcode.com/problems/student-attendance-record-ii/) | Hard | Multi-dimensional DP states matrix, modular addition |
| **Dynamic Programming** | [Optimal Division](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_optimal_division.md) | [LeetCode 553](https://leetcode.com/problems/optimal-division/) | Medium | Math expression maximizing, division logic reduction |
| **Dynamic Programming** | [Out of Boundary Paths](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_out_of_boundary_paths.md) | [LeetCode 576](https://leetcode.com/problems/out-of-boundary-paths/) | Medium | Grid coordinate step DP, boundaries aggregation |
| **Dynamic Programming** | [Super Egg Drop](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_super_egg_drop.md) | [LeetCode 887](https://leetcode.com/problems/super-egg-drop/) | Hard | DP with binary search transition paths, step-count DP inversion |
| **Design** | [LFU Cache](file:///Users/quan/workspace/interview-prep/popular/tiers/intermediate/coding_lfu_cache.md) | [LeetCode 460](https://leetcode.com/problems/lfu-cache/) | Hard | HashMap with doubly-linked frequency lists |

---

## 💡 Intermediate Tier Interview Strategy

### 1. Integer Shift Limits & Bit Safety
*   **Bitwise Shifts (C++)**: Left-shifting a signed integer beyond 31 bits (e.g. `1 << 31`) is undefined behavior in C++ and can cause integer overflow warnings or architecture crashes. Always use unsigned integer literals (e.g. `1ULL << 31`) when building wide masks.
*   **Memory Allocations**: For bitset representations, pre-allocate space or utilize bit vectors if $n$ fits within CPU word boundaries ($64$ bits). For larger sizes, fallback to `std::vector<bool>`, which is space-optimized by the C++ compiler to pack 8 bits per byte.

### 2. Stack and Recursion Depths
*   **Python Call Stack Constraints**: In DFS graph problems, Python’s default recursion stack limit is low ($1000$ frames). For deep tree structures or large grids (such as a $1000 \times 1000$ matrix), recursive DFS can crash with a `RecursionError`. Implement algorithms iteratively using an explicit `list` as a stack, or use `sys.setrecursionlimit` defensively.

### 3. Dynamic Heap Operations
*   **Custom Heap Comparators (C++)**: To implement a custom min/max heap configuration, declare a struct functor and pass it to `std::priority_queue`:
    ```cpp
    struct CustomCompare {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.first > b.first; // Min-heap behavior
        }
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, CustomCompare> min_heap;
    ```
*   **Lazy Removal Optimization**: When elements inside a heap need updates/deletions (as in Sliding Window Median), avoid linear searching to delete. Instead, track the elements to be removed in an auxiliary "lazy removal" map, and only pop them from the heap when they reach the top.
