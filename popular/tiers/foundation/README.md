# Tier 1: Foundation — Coding Interview Preparation Roadmap

Welcome to the **Foundation (Tier 1) Coding Roadmap**. This directory serves as your structured study guide and reference repository for mastering foundational coding patterns. These patterns represent the core building blocks of algorithmic problem-solving and constitute approximately **60-70%** of coding interview questions at top-tier technology companies (such as Google, Meta, NVIDIA, and Microsoft).

---

## 🗺️ Progression Roadmap

To build strong algorithmic intuition, we recommend following a progressive learning order. Rather than jumping randomly between topics, master them sequentially as each builds on the mathematical and structural concepts of the previous one.

```text
┌────────────────────────────────────────┐
│  Step 1: Arrays & Strings              │
│  (Two Pointers & String)               │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 2: Linear Structures             │
│  (Fast & Slow Pointers)                │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 3: Subarrays & Substrings        │
│  (Sliding Window)                      │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 4: Coordinate Ranges             │
│  (Merge Intervals)                     │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 5: Hash & Value Lookups          │
│  (Hashmap)                             │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 6: Tree & Graph Traversal        │
│  (Breadth-First Search)                │
└────────────────────────────────────────┘
```

---

## 📈 Detailed Learning Modules & File Index

Here is the complete catalog of the 39 Foundation problems, categorized by pattern, and arranged in recommended learning order.

### Module 1: Two Pointers & String Manipulation
*Goal: Master in-place array/string traversal, reducing $\mathcal{O}(n^2)$ naive nested loops to $\mathcal{O}(n)$ linear scans.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Two Pointers** | [Container With Most Water](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_container_water.md) | [LeetCode 11](https://leetcode.com/problems/container-with-most-water/) | Medium | Greedy choice, area calculation, boundary convergence |
| **Two Pointers** | [3Sum](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_three_sum.md) | [LeetCode 15](https://leetcode.com/problems/3sum/) | Medium | Sorting, duplicate avoidance, triplet generation |
| **Two Pointers** | [Two Sum II - Sorted Input](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_two_sum.md) | [LeetCode 167](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | Medium | Constant space lookup, sorted array properties |
| **Two Pointers** | [Is Subsequence](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_is_subsequence.md) | [LeetCode 392](https://leetcode.com/problems/is-subsequence/) | Easy | Greedy match pointer, sequence order validation |
| **Two Pointers** | [Heaters](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_heaters.md) | [LeetCode 475](https://leetcode.com/problems/heaters/) | Medium | Sorting, nearest distance search, binary search alternative |
| **Two Pointers** | [Longest Uncommon Subsequence II](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_longest_uncommon_subsequence_ii.md) | [LeetCode 522](https://leetcode.com/problems/longest-uncommon-subsequence-ii/) | Medium | Subsequence checking, string length comparison |
| **Two Pointers** | [Longest Word in Dict by Deleting](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_longest_word_in_dictionary_through_deleting.md) | [LeetCode 524](https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/) | Medium | Custom sorting, deletion mapping, greediness |
| **Two Pointers** | [K-diff Pairs in an Array](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_k_diff_pairs_in_an_array.md) | [LeetCode 532](https://leetcode.com/problems/k-diff-pairs-in-an-array/) | Medium | Two-pointer vs hashmap, duplicate prevention |
| **String** | [Number of Segments in String](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_number_of_segments_in_a_string.md) | [LeetCode 434](https://leetcode.com/problems/number-of-segments-in-a-string/) | Easy | Space transitions, state flags |
| **String** | [License Key Formatting](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_license_key_formatting.md) | [LeetCode 482](https://leetcode.com/problems/license-key-formatting/) | Easy | Backward processing, group indexing |
| **String** | [Detect Capital](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_detect_capital.md) | [LeetCode 520](https://leetcode.com/problems/detect-capital/) | Easy | Capital casing rules, simple state counters |
| **String** | [Longest Uncommon Subsequence I](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_longest_uncommon_subsequence_i.md) | [LeetCode 521](https://leetcode.com/problems/longest-uncommon-subsequence-i/) | Easy | Logical deduction, string equality checks |

### Module 2: Fast & Slow Pointers (Tortoise & Hare)
*Goal: Detect cycles and locate structures in linked lists or mathematical sequences with $\mathcal{O}(1)$ space complexity.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Fast & Slow Pointers** | [Linked List Cycle](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_linked_list_cycle.md) | [LeetCode 141](https://leetcode.com/problems/linked-list-cycle/) | Easy | Floyd's Cycle-Finding Algorithm, loop invariants |
| **Fast & Slow Pointers** | [Happy Number](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_happy_number.md) | [LeetCode 202](https://leetcode.com/problems/happy-number/) | Easy | Digit sum cycles, sequence convergence |
| **Fast & Slow Pointers** | [Middle of the Linked List](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_middle_of_linked_list.md) | [LeetCode 876](https://leetcode.com/problems/middle-of-the-linked-list/) | Easy | Node traversal parity, list splitting |

### Module 3: Sliding Window
*Goal: Dynamically resize a subsegment of an array or string to track constraints, avoiding nested-loop recalibration.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Sliding Window** | [Longest Substring without Duplicates](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_longest_substring.md) | [LeetCode 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | Medium | Map-based index skips, dynamic left-pointer updates |
| **Sliding Window** | [Longest Substring with At Least K Repeats](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_longest_substring_with_at_least_k_repeating_characters.md) | [LeetCode 395](https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/) | Medium | Multi-sliding window with unique char constraint limits |
| **Sliding Window** | [Longest Repeating Character Replacement](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_longest_repeating_char.md) | [LeetCode 424](https://leetcode.com/problems/longest-repeating-character-replacement/) | Medium | Substring character frequency tracking, maximum frequency preservation |
| **Sliding Window** | [Find All Anagrams in a String](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_find_anagrams.md) | [LeetCode 438](https://leetcode.com/problems/find-all-anagrams-in-a-string/) | Medium | Static-width sliding window, character frequency map diffing |
| **Sliding Window** | [Permutation in String](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_permutation_in_string.md) | [LeetCode 567](https://leetcode.com/problems/permutation-in-string/) | Medium | Slide over fixed window, sliding frequency comparison |

### Module 4: Merge Intervals
*Goal: Process time segments, coordinates, and overlaps by sorting boundaries and sequentially merging.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Merge Intervals** | [Merge Intervals](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_merge_intervals.md) | [LeetCode 56](https://leetcode.com/problems/merge-intervals/) | Medium | Boundary sorting, overlap consolidation, in-place moving |
| **Merge Intervals** | [Insert Interval](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_insert_interval.md) | [LeetCode 57](https://leetcode.com/problems/insert-interval/) | Medium | 3-stage linear processing (before, during, after) |
| **Merge Intervals** | [Meeting Rooms II (Rooms Required)](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_meeting_rooms.md) | [LeetCode 253](https://leetcode.com/problems/meeting-rooms-ii/) | Medium | Sweep-line technique, priority queues, start-end sorting |
| **Merge Intervals** | [Teemo Attacking](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_teemo_attacking.md) | [LeetCode 495](https://leetcode.com/problems/teemo-attacking/) | Easy | Poison state calculation, simple step progression |

### Module 5: Hashmap & Dynamic Lookups
*Goal: Achieve $\mathcal{O}(1)$ insertion, deletion, and lookup times, combining associative maps with contiguous arrays for specialized data structures.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Hashmap** | [Insert Delete GetRandom O(1)](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_insert_delete_getrandom_o1.md) | [LeetCode 380](https://leetcode.com/problems/insert-delete-getrandom-o1/) | Medium | Combination of hash table (indexes) & dynamic vector (elements) |
| **Hashmap** | [Linked List Random Node](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_linked_list_random_node.md) | [LeetCode 382](https://leetcode.com/problems/linked-list-random-node/) | Medium | Reservoir Sampling, streaming data selection under memory limits |
| **Hashmap** | [Perfect Rectangle](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_perfect_rectangle.md) | [LeetCode 391](https://leetcode.com/problems/perfect-rectangle/) | Hard | Area calculation, corner coordinate set validation |
| **Hashmap** | [Random Pick Index](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_random_pick_index.md) | [LeetCode 398](https://leetcode.com/problems/random-pick-index/) | Medium | Reservoir sampling, duplicate values lookup indexing |
| **Hashmap** | [Number of Boomerangs](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_number_of_boomerangs.md) | [LeetCode 447](https://leetcode.com/problems/number-of-boomerangs/) | Medium | Distance hashing, permutations counting |
| **Hashmap** | [Keyboard Row](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_keyboard_row.md) | [LeetCode 500](https://leetcode.com/problems/keyboard-row/) | Easy | Set memberships, string categorization |
| **Hashmap** | [Encode and Decode TinyURL](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_encode_and_decode_tinyurl.md) | [LeetCode 535](https://leetcode.com/problems/encode-and-decode-tinyurl/) | Medium | Two-way hash matching, random base62 ID generation |
| **Hashmap** | [Distribute Candies](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_distribute_candies.md) | [LeetCode 575](https://leetcode.com/problems/distribute-candies/) | Easy | Set hashing, logical min boundaries |

### Module 6: Breadth-First Search (BFS) & Tree Traversal
*Goal: Traverse tree structures level-by-level or find the shortest path in unweighted spatial grids.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **BFS** | [Binary Tree Level Order Traversal](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_level_order.md) | [LeetCode 102](https://leetcode.com/problems/binary-tree-level-order-traversal/) | Medium | Level-by-level BFS queue sizing, dynamic sub-array construction |
| **BFS** | [Shortest Path in Binary Matrix](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_shortest_path_binary.md) | [LeetCode 1091](https://leetcode.com/problems/shortest-path-in-binary-matrix/) | Medium | 8-directional spatial grid BFS, queue invariants, in-place marking |
| **BFS** | [Serialize and Deserialize BST](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_serialize_and_deserialize_bst.md) | [LeetCode 449](https://leetcode.com/problems/serialize-and-deserialize-bst/) | Medium | Binary sequence streaming, pre-order reconstruction boundaries |
| **BFS** | [Island Perimeter](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_island_perimeter.md) | [LeetCode 463](https://leetcode.com/problems/island-perimeter/) | Easy | Geometric cell counting, shared boundary deduplication |
| **BFS** | [Find Bottom Left Tree Value](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_find_bottom_left_tree_value.md) | [LeetCode 513](https://leetcode.com/problems/find-bottom-left-tree-value/) | Medium | Right-to-Left level order traversal queue state preservation |
| **BFS** | [Find Largest Value in Tree Rows](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_find_largest_value_in_each_tree_row.md) | [LeetCode 515](https://leetcode.com/problems/find-largest-value-in-each-tree-row/) | Medium | Row maximum tracking, BFS level boundaries |
| **BFS** | [Rotting Oranges](file:///Users/quan/workspace/interview-prep/popular/tiers/foundation/coding_rotting_oranges.md) | [LeetCode 994](https://leetcode.com/problems/rotting-oranges/) | Medium | Multi-source BFS, fresh item counts, level-based state progression |

---

## 💡 Foundation Tier Interview Strategy

### 1. Pointer Boundary Safeties
*   **Unsigned Underflow (C++)**: Avoid running loops with `0` limits using unsigned size types (e.g. `size_t`). Subtracting `1` from an empty array's size yields `18446744073709551615`. Cast to `int` or perform explicit empty checks.
*   **Pointer Slices (Python)**: Avoid using slice syntax like `nums[left:right]` during partition operations. Slicing creates shallow copies, making your space complexity $\mathcal{O}(k)$ instead of $\mathcal{O}(1)$. Use explicit pointer variables instead.

### 2. Space Optimization
*   **BFS Memory Overhead**: The space complexity of BFS is dominated by the queue size, which reaches $\mathcal{O}(w)$ where $w$ is the maximum width of the tree/graph. For a full binary tree, the maximum width is $n/2$ (at the leaf level). Keep this in mind when discussing memory constraints with the interviewer.
*   **Hash Maps Memory Bloat**: C++ `std::unordered_map` and Python `dict` have substantial memory overheads due to hash bucket allocation. For small, fixed key sets (like lowercase English letters), use a static array of size 26 (e.g., `int freq[26] = {0}`) to gain massive performance increases and optimal cache locality.

### 3. Cycle Detection
*   **In-Place Array Modification**: If the array elements lie within the bounds $[0, n-1]$, you can use the array elements themselves as pointers to detect cycles and duplicates in-place by negating the values at indices (e.g., `nums[abs(nums[i])] *= -1`), saving auxiliary space.
