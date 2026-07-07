# Tier 3: Advanced — Coding Interview Preparation Roadmap

Welcome to the **Advanced (Tier 3) Coding Roadmap**. This directory serves as your structured study guide and indexed reference repository for advanced algorithmic design. These patterns cover complex in-place cycle sorting, search space bisections, NP-complete recursive state pruning, and efficient prefix tree search systems.

---

## 🗺️ Progression Roadmap

To build advanced algorithmic intuition, start with linear index-cycle logic, move to threshold binary searches, then explore backtracking state-spaces and prefix structures.

```text
┌────────────────────────────────────────┐
│  Step 1: Cycle Indexing                │
│  (Cyclic Sort)                         │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 2: Search Thresholds             │
│  (Modified Binary Search)              │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 3: State-Space Traversals        │
│  (Backtracking & Subsets)              │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 4: Prefix Retrieval Systems      │
│  (Trie)                                │
└────────────────────────────────────────┘
```

---

## 📈 Detailed Learning Modules & File Index

Here is the complete catalog of the 19 Advanced problems, categorized by pattern, and arranged in recommended learning order.

### Module 1: Cyclic Sort (In-Place Index Matching)
*Goal: Sort arrays containing values in the range $[0, n]$ in $\mathcal{O}(n)$ time using $\mathcal{O}(1)$ auxiliary space by swap-positioning.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Cyclic Sort** | [Missing Number](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_missing_number.md) | [LeetCode 268](https://leetcode.com/problems/missing-number/) | Easy | Value-to-index swap checks, XOR alternative |
| **Cyclic Sort** | [Find All Duplicates in Array](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_find_duplicates.md) | [LeetCode 442](https://leetcode.com/problems/find-all-duplicates-in-an-array/) | Medium | Index-negation marker flag, in-place cycle sort |
| **Cyclic Sort** | [Find All Numbers Disappeared](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_find_disappeared.md) | [LeetCode 448](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/) | Easy | Value sign-negation state mapping, swap cycle |

### Module 2: Modified Binary Search
*Goal: Divide search spaces over non-standard ranges, rotated arrays, and numeric threshold bounds.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Modified Binary Search** | [Search in Rotated Sorted Array](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_search_rotated.md) | [LeetCode 33](https://leetcode.com/problems/search-in-rotated-sorted-array/) | Medium | Rotated partition identification, boundary narrowing |
| **Modified Binary Search** | [Split Array Largest Sum](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_split_array_sum.md) | [LeetCode 410](https://leetcode.com/problems/split-array-largest-sum/) | Hard | Feasibility test function, search space bisection |
| **Modified Binary Search** | [Koko Eating Bananas](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_koko_bananas.md) | [LeetCode 875](https://leetcode.com/problems/koko-eating-bananas/) | Medium | Monotonic rate search space, ceiling divisions |

### Module 3: Backtracking & Subsets
*Goal: Traverse permutations, combinations, and partitioned state-spaces using recursion, backtracks, and early structural pruning.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Backtracking** | [Letter Combinations of a Phone Number](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_letter_combinations.md) | [LeetCode 17](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) | Medium | String-mapping array backtracking, BFS queue |
| **Backtracking** | [Combination Sum](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_combination_sum.md) | [LeetCode 39](https://leetcode.com/problems/combination-sum/) | Medium | Array sorting, backtracking pruning, index preservation |
| **Backtracking** | [Subsets](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_subsets.md) | [LeetCode 78](https://leetcode.com/problems/subsets/) | Medium | Cascading subsets build, bitmask integer indices |
| **Backtracking** | [Matchsticks to Square](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_matchsticks_to_square.md) | [LeetCode 473](https://leetcode.com/problems/matchsticks-to-square/) | Medium | Descending sorting optimization, symmetry breaks |
| **Backtracking** | [Zuma Game](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_zuma_game.md) | [LeetCode 488](https://leetcode.com/problems/zuma-game/) | Hard | String board collapsing, DFS memoization, heuristic pruning |
| **Backtracking** | [Non-decreasing Subsequences](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_non_decreasing_subsequences.md) | [LeetCode 491](https://leetcode.com/problems/non-decreasing-subsequences/) | Medium | Subsequence order preservation, index duplicate skipping |
| **Subsets** | [Permutations](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_permutations.md) | [LeetCode 46](https://leetcode.com/problems/permutations/) | Medium | In-place swapping backtracking, std::next_permutation |
| **Subsets** | [Combinations](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_combinations.md) | [LeetCode 77](https://leetcode.com/problems/combinations/) | Medium | Size boundary limits pruning, Gosper's Hack |
| **Subsets** | [Subsets II](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_subsets_ii.md) | [LeetCode 90](https://leetcode.com/problems/subsets-ii/) | Medium | Array sorting, recursion-level duplicate skipping |

### Module 4: Trie (Prefix Trees)
*Goal: Design and build efficient character prefix retrieval systems for spelling lookups, wildcard searches, and grid board validations.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Trie** | [Implement Trie (Prefix Tree)](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_implement_trie.md) | [LeetCode 208](https://leetcode.com/problems/implement-trie-prefix-tree/) | Medium | Alphabet child-pointer nodes, insertion, prefix searches |
| **Trie** | [Design Add and Search Words](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_design_add_search.md) | [LeetCode 211](https://leetcode.com/problems/design-add-and-search-words-data-structure/) | Medium | Dot wildcard recursive character tree search |
| **Trie** | [Word Search II](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_word_search_ii.md) | [LeetCode 212](https://leetcode.com/problems/word-search-ii/) | Hard | Matrix floodfill combined with Trie search prefix pruning |
| **Trie** | [Concatenated Words](file:///Users/quan/workspace/interview-prep/popular/tiers/advanced/coding_concatenated_words.md) | [LeetCode 472](https://leetcode.com/problems/concatenated-words/) | Hard | DP string word-break partitioning with Trie lookups |

---

## 💡 Advanced Tier Interview Strategy

### 1. Cyclic Sort index mappings
*   **Loop Invariants**: The key invariant of cyclic sort is that at each index `i`, we repeatedly swap the element `nums[i]` with the element at its target index `nums[nums[i] - 1]` until the value at `i` is in its correct place (i.e. `nums[i] == i + 1` or `nums[i]` is out of bounds).
*   **Infinite Loop Safety**: Always verify that the swap target index does not contain the same value as the source (`nums[i] != nums[nums[i] - 1]`). If they are equal, do not swap, otherwise your loop will run infinitely.

### 2. Backtracking Pruning for NP-Complete Problems
*   **Descending Sorting**: In partitioning problems (such as Matchsticks to Square), sorting the input array in descending order before running backtracking allows the algorithm to try larger values first. This triggers early failures on large items and prunes search branches much faster.
*   **Symmetry Breaking**: If multiple sub-buckets/sides are identical (e.g. side sums), and a search step fails for one side, do not try it on other identical sides with the same sum. Immediately exit or skip.

### 3. Trie Memory Management
*   **C++ RAII Destructors**: Trie nodes contain heap-allocated child pointers. To prevent memory leaks, you must write a recursive destructor in C++:
    ```cpp
    ~TrieNode() {
        for (TrieNode* child : children) {
            delete child;
        }
    }
    ```
*   **Python Memory Savings**: Trie node allocations can create millions of small objects, which bloats Python's memory due to instance `__dict__` overhead. Declare `__slots__ = ('children', 'is_end')` in your node classes to restrict dynamic attributes and reduce heap space by up to **70%**.
