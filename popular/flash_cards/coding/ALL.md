# All Coding Flashcards — Shuffled

145 cards from 29 pattern decks, shuffled with seed=42.
Read top-to-bottom. The pattern is hidden until you expand — you must recall it yourself.

---

**1 / 145**

<details><summary><b>Two strings s and t — is s a subsequence of t (order preserved, chars deletable)?</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(|t|)
Move: Greedy match pointer in t advances only on matches; if the s pointer reaches the end, it is a subsequence.
File: [coding_is_subsequence.md](../../tiers/foundation/coding_is_subsequence.md)
</details>

**2 / 145**

<details><summary><b>pick a uniformly random point across a set of non-overlapping rectangles</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Medium
Move: Prefix the weighted areas, binary-search the random pick by area, decode coords.
File: [coding_random_point_in_non_overlapping_rectangles.md](../../tiers/intermediate/coding_random_point_in_non_overlapping_rectangles.md)
</details>

**3 / 145**

<details><summary><b>smallest integer greater than n using the same digits</b></summary>

Pattern: Math &nbsp;|&nbsp; Medium
Move: Next-permutation algorithm, then verify no 32-bit signed overflow.
File: [coding_next_greater_element_iii.md](../../tiers/intermediate/coding_next_greater_element_iii.md)
</details>

**4 / 145**

<details><summary><b>number of distinct coin combinations that sum to amount</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: Unbounded knapsack combos; outer loop = coins, inner loop = amounts (no double-count).
File: [coding_coin_change_ii.md](../../tiers/intermediate/coding_coin_change_ii.md)
</details>

**5 / 145**

<details><summary><b>A sorted list of non-overlapping intervals and one new interval — insert and merge</b></summary>

Pattern: Merge Intervals &nbsp;|&nbsp; O(n)
Move: Single linear pass in 3 stages — copy intervals ending before the new one, then merge all that overlap the new one, then copy the rest.
File: [coding_insert_interval.md](../../tiers/foundation/coding_insert_interval.md)
</details>

**6 / 145**

<details><summary><b>Strings s1 and s2 — does s2 contain a permutation of s1 as a contiguous substring?</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(|s2|)
Move: Slide a fixed |s1|-width window over s2; sliding-frequency-compare against s1's frequency map and report when they match.
File: [coding_permutation_in_string.md](../../tiers/foundation/coding_permutation_in_string.md)
</details>

**7 / 145**

<details><summary><b>List of words — return each word that is a concatenation of two or more other words in the list</b></summary>

Pattern: Trie &nbsp;|&nbsp; O(N * L^2)
Move: For each word run word-break DP where the dictionary is the other words; a Trie lets every prefix lookup share the same search tree.
File: [coding_concatenated_words.md](../../tiers/advanced/coding_concatenated_words.md)
</details>

**8 / 145**

<details><summary><b>parse "[123,[456,[789]]]" into a nested integer tree</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Recursive-descent parser building NestedInteger nodes from the token stream.
File: [coding_mini_parser.md](../../tiers/intermediate/coding_mini_parser.md)
</details>

**9 / 145**

<details><summary><b>median of each sliding window of size k</b></summary>

Pattern: Two Heaps &nbsp;|&nbsp; Hard
Move: Two heaps with a lazy-deletion map for outgoing window elements.
File: [coding_sliding_window_median.md](../../tiers/intermediate/coding_sliding_window_median.md)
</details>

**10 / 145**

<details><summary><b>Array of distinct ints — return all possible permutations</b></summary>

Pattern: Subsets &nbsp;|&nbsp; O(n!)
Move: At each index i, swap it with every j ≥ i, recurse, then swap back (backtrack). Alternatively, sort and walk std::next_permutation to enumerate.
File: [coding_permutations.md](../../tiers/advanced/coding_permutations.md)
</details>

**11 / 145**

<details><summary><b>Given a singly linked list, return a random node's value with uniform probability</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n) one pass
Move: Reservoir sampling (size 1) — at the i-th node, pick it with probability 1/i; no second pass or length storage needed.
File: [coding_linked_list_random_node.md](../../tiers/foundation/coding_linked_list_random_node.md)
</details>

**12 / 145**

<details><summary><b>A string of uppercase letters and int k — longest substring achievable by replacing at most k chars</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(n)
Move: Track window char frequencies; the window is valid while (length - max_freq) <= k, so never shrink — just shift right when it exceeds.
File: [coding_longest_repeating_char.md](../../tiers/foundation/coding_longest_repeating_char.md)
</details>

**13 / 145**

<details><summary><b>Array of ints and a target diff k — count unique pairs (a, b) with |a - b| == k</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n log n)
Move: Sort, then walk two pointers; special-case k == 0 (count values appearing 2+ times) and skip duplicates to prevent double counting.
File: [coding_k_diff_pairs_in_an_array.md](../../tiers/foundation/coding_k_diff_pairs_in_an_array.md)
</details>

**14 / 145**

<details><summary><b>merge k sorted linked lists into one sorted list</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Hard
Move: Min-heap of current list-heads, or recursively partition-merge pairs of lists.
File: [coding_merge_k_sorted_lists.md](../../tiers/intermediate/coding_merge_k_sorted_lists.md)
</details>

**15 / 145**

<details><summary><b>closest integer (not equal to n) that is a palindrome</b></summary>

Pattern: Math &nbsp;|&nbsp; Hard
Move: Mirror the first half; also test half +/- 1 and the 9...9 / 10...01 edge cases.
File: [coding_find_the_closest_palindrome.md](../../tiers/intermediate/coding_find_the_closest_palindrome.md)
</details>

**16 / 145**

<details><summary><b>delete a node with a given key from a BST</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Replace with in-order successor (or predecessor), then rewire the subtree.
File: [coding_delete_node_in_a_bst.md](../../tiers/intermediate/coding_delete_node_in_a_bst.md)
</details>

**17 / 145**

<details><summary><b>A series of (time, duration) attacks — total time the target is poisoned (no stacking, later attack refreshes)</b></summary>

Pattern: Merge Intervals &nbsp;|&nbsp; O(n)
Move: Walk consecutive attacks; for each, add min(duration, gap-to-next-attack) so overlapping poison windows don't double-count.
File: [coding_teemo_attacking.md](../../tiers/foundation/coding_teemo_attacking.md)
</details>

**18 / 145**

<details><summary><b>n people and a trust list [a, b] meaning "a trusts b" — find the one who trusts nobody yet is trusted by everyone (else -1)</b></summary>

Pattern: Graph &nbsp;|&nbsp; O(n + t)
Move: Trust-score each person: trustee +1, truster -1; the judge is the single index whose net score equals n - 1.
File: [coding_town_judge.md](../../tiers/expert/coding_town_judge.md)
</details>

**19 / 145**

<details><summary><b>sort an array without using the built-in sort</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Medium
Move: Implement quicksort, mergesort, or heapsort safely with correct partitioning.
File: [coding_sort_an_array.md](../../tiers/intermediate/coding_sort_an_array.md)
</details>

**20 / 145**

<details><summary><b>m x n matrix — return elements in diagonal zigzag order</b></summary>

Pattern: Matrix Traversal &nbsp;|&nbsp; O(m * n)
Move: Group cells by r + c = const; even sums traverse up-right, odd sums traverse down-left, flipping direction at each boundary.
File: [coding_diagonal_traverse.md](../../tiers/expert/coding_diagonal_traverse.md)
</details>

**21 / 145**

<details><summary><b>volume of trapped rainwater on a 2D elevation map</b></summary>

Pattern: Top K Elements &nbsp;|&nbsp; Hard
Move: Priority-queue BFS expanding the border; each cell traps by its min-border.
File: [coding_trapping_rain_water_ii.md](../../tiers/intermediate/coding_trapping_rain_water_ii.md)
</details>

**22 / 145**

<details><summary><b>find the k points closest to the origin</b></summary>

Pattern: Top K Elements &nbsp;|&nbsp; Medium
Move: Max-heap of size k keyed by squared Euclidean distance; pop when over k.
File: [coding_k_closest_points.md](../../tiers/intermediate/coding_k_closest_points.md)
</details>

**23 / 145**

<details><summary><b>count valid attendance records of length n (no triple L, at most one A)</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: 6-state DP (A-count 0/1 x trailing-L-run 0/1/2), summed mod 1e9+7.
File: [coding_student_attendance_record_ii.md](../../tiers/intermediate/coding_student_attendance_record_ii.md)
</details>

**24 / 145**

<details><summary><b>Distinct candidates and a target — list every unique combination summing to target (unlimited reuse)</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(2^n)
Move: Sort the candidates, then backtrack passing the same start index on the recursive call (allowing reuse) while skipping earlier picks to prevent duplicate combinations.
File: [coding_combination_sum.md](../../tiers/advanced/coding_combination_sum.md)
</details>

**25 / 145**

<details><summary><b>A list of closed intervals — merge all overlapping ones and return the disjoint set</b></summary>

Pattern: Merge Intervals &nbsp;|&nbsp; O(n log n)
Move: Sort by start; iterate and either extend the running interval when starts overlap its end, or push it and start a new one.
File: [coding_merge_intervals.md](../../tiers/foundation/coding_merge_intervals.md)
</details>

**26 / 145**

<details><summary><b>Trie that supports a '.' wildcard matching any single character in search</b></summary>

Pattern: Trie &nbsp;|&nbsp; O(26^L) worst
Move: Same as a standard Trie, but on '.' recurse into every existing child and accept the first full match; prune empty branches early.
File: [coding_design_add_search.md](../../tiers/advanced/coding_design_add_search.md)
</details>

**27 / 145**

<details><summary><b>Two arrays (gas, cost) around a circular route — return the start index that completes the loop, or -1</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n)
Move: If total gas ≥ total cost a solution exists; the valid start is the index immediately after the prefix with the largest cumulative deficit.
File: [coding_gas_station.md](../../tiers/expert/coding_gas_station.md)
</details>

**28 / 145**

<details><summary><b>count contiguous subarrays whose sum equals k</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Hash cumulative sums and look up prior prefix frequencies.
File: [coding_subarray_sum_equals_k.md](../../tiers/intermediate/coding_subarray_sum_equals_k.md)
</details>

**29 / 145**

<details><summary><b>return the k most frequent elements</b></summary>

Pattern: Top K Elements &nbsp;|&nbsp; Medium
Move: Frequency map then bucket sort by count, or size-k min-heap on frequencies.
File: [coding_top_k_frequent.md](../../tiers/intermediate/coding_top_k_frequent.md)
</details>

**30 / 145**

<details><summary><b>Array of heights, two lines chosen form a container — maximize water area</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n)
Move: Greedy choice between left/right boundaries; move the shorter wall inward to seek a taller line and shrink width.
File: [coding_container_water.md](../../tiers/foundation/coding_container_water.md)
</details>

**31 / 145**

<details><summary><b>Design a prefix tree supporting insert, search, and startsWith operations</b></summary>

Pattern: Trie &nbsp;|&nbsp; O(L) per op
Move: Each node holds 26 child pointers plus an is_end flag; insert walks/creates nodes char-by-char, and search/startsWith walk down the same path.
File: [coding_implement_trie.md](../../tiers/advanced/coding_implement_trie.md)
</details>

**32 / 145**

<details><summary><b>find the element appearing more than floor(n/2) times</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Easy
Move: Boyer-Moore voting: count up for the candidate, down on mismatch.
File: [coding_majority_element.md](../../tiers/intermediate/coding_majority_element.md)
</details>

**33 / 145**

<details><summary><b>Two ints n and k — list every k-combination from [1..n]</b></summary>

Pattern: Subsets &nbsp;|&nbsp; O(C(n,k) * k)
Move: Backtrack with a running size limit; record once it hits k and prune branches that can no longer reach k. Gosper's hack enumerates the k-bit integer masks directly.
File: [coding_combinations.md](../../tiers/advanced/coding_combinations.md)
</details>

**34 / 145**

<details><summary><b>numCourses and prerequisites — return any valid topological order, or [] if none exists</b></summary>

Pattern: Graph &nbsp;|&nbsp; O(V + E)
Move: Kahn's BFS — repeatedly dequeue an in-degree-zero node, append it to the order, decrement its neighbors; if the output count is below n, return [].
File: [coding_course_schedule_ii.md](../../tiers/expert/coding_course_schedule_ii.md)
</details>

**35 / 145**

<details><summary><b>Circular array of ints — for each element find the next greater one, wrapping around the end</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: Iterate indices 0..2n-1 (mod n); push them onto a decreasing stack, and on a larger value pop and record it for the original index.
File: [coding_next_greater_element_ii.md](../../tiers/expert/coding_next_greater_element_ii.md)
</details>

**36 / 145**

<details><summary><b>Binary matrix — for each cell return the distance to the nearest 0</b></summary>

Pattern: Matrix Traversal &nbsp;|&nbsp; O(m * n)
Move: Multi-source BFS from every 0 cell, relaxing each neighbor's distance as it is dequeued; equivalently a two-pass 2D DP from opposite corners.
File: [coding_01_matrix.md](../../tiers/expert/coding_01_matrix.md)
</details>

**37 / 145**

<details><summary><b>maximum number of russian-doll-envelopes you can nest</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Hard
Move: Sort by (width asc, height desc), then LIS via patience search on heights.
File: [coding_russian_doll_envelopes.md](../../tiers/intermediate/coding_russian_doll_envelopes.md)
</details>

**38 / 145**

<details><summary><b>Tasks with durations to run across a fixed number of machines — minimize the makespan to finish all</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n log n + n log m)
Move: Sort tasks descending by duration; keep machines in a min-heap keyed by earliest free time and assign each task to the soonest-free machine.
File: [coding_task_scheduler_multi_machine.md](../../tiers/expert/coding_task_scheduler_multi_machine.md)
</details>

**39 / 145**

<details><summary><b>Rotated sorted array of distinct ints — find the target index in O(log n)</b></summary>

Pattern: Modified Binary Search &nbsp;|&nbsp; O(log n)
Move: At each midpoint, identify which half is properly sorted; check whether the target lies inside that sorted half to decide which side to keep, then narrow bounds.
File: [coding_search_rotated.md](../../tiers/advanced/coding_search_rotated.md)
</details>

**40 / 145**

<details><summary><b>Children ratings in a line — each needs ≥ 1 candy and strictly more than any lower-rated neighbor; minimize total candies</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n)
Move: Two passes — left-to-right raises the candy count when the rating rises, then right-to-left raises it to satisfy right neighbors; take the per-child max and sum.
File: [coding_candy.md](../../tiers/expert/coding_candy.md)
</details>

**41 / 145**

<details><summary><b>Projects each with a capital need and a profit, plus starting capital w and at most k picks — maximize final capital</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O((N + k) log N)
Move: Sort projects by capital need; sweep capital pushing affordable projects' profits into a max-heap and pick the top one, k times.
File: [coding_ipo.md](../../tiers/expert/coding_ipo.md)
</details>

**42 / 145**

<details><summary><b>count pairs i < j with nums[i] > 2 * nums[j]</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Hard
Move: Merge sort while counting cross inversions of nums[i] > 2*nums[j].
File: [coding_reverse_pairs.md](../../tiers/intermediate/coding_reverse_pairs.md)
</details>

**43 / 145**

<details><summary><b>Axis-aligned rectangles — do they exactly tile a single larger rectangle with no gaps or overlaps?</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n)
Move: Sum areas and verify against the bounding rectangle's area; all corners must appear an even number of times except the four bounding corners.
File: [coding_perfect_rectangle.md](../../tiers/foundation/coding_perfect_rectangle.md)
</details>

**44 / 145**

<details><summary><b>design Twitter: post tweets, follow users, fetch top-k news feed</b></summary>

Pattern: Two Heaps &nbsp;|&nbsp; Medium
Move: Per-user tweet list + follow set; merge k most-recent tweets via a heap.
File: [coding_design_twitter.md](../../tiers/intermediate/coding_design_twitter.md)
</details>

**45 / 145**

<details><summary><b>is tree s an exact subtree (structure + values) of tree t?</b></summary>

Pattern: DFS &nbsp;|&nbsp; Easy
Move: Recurse: sameTree check at every node, else recurse into t's children.
File: [coding_subtree_of_another_tree.md](../../tiers/intermediate/coding_subtree_of_another_tree.md)
</details>

**46 / 145**

<details><summary><b>Sorted array, find two elements summing to target, return 1-based indices</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n)
Move: Walk one pointer from each end; sum too small → advance left, too large → retreat right, using sorted order for O(1) space lookup.
File: [coding_two_sum.md](../../tiers/foundation/coding_two_sum.md)
</details>

**47 / 145**

<details><summary><b>Board string of colored balls plus a hand of balls — minimum insertions to clear the board</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; exponential
Move: DFS over (board, hand) states; collapse runs of ≥ 3 on each insertion, memoize visited states, and prune branches whose hand grows past the best-so-far insertion count.
File: [coding_zuma_game.md](../../tiers/advanced/coding_zuma_game.md)
</details>

**48 / 145**

<details><summary><b>smallest base b whose representation of n is all 1s</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Hard
Move: For each geometric-series length, binary-search the base representation.
File: [coding_smallest_good_base.md](../../tiers/intermediate/coding_smallest_good_base.md)
</details>

**49 / 145**

<details><summary><b>Array of n ints, each value in [1, n], some appear twice — list all duplicates without extra space</b></summary>

Pattern: Cyclic Sort &nbsp;|&nbsp; O(n)
Move: For each value x, flip nums[abs(x) - 1] negative as a marker; if it is already negative when you visit it, x is a duplicate.
File: [coding_find_duplicates.md](../../tiers/advanced/coding_find_duplicates.md)
</details>

**50 / 145**

<details><summary><b>Singly linked list head — does it contain a cycle?</b></summary>

Pattern: Fast & Slow Pointers &nbsp;|&nbsp; O(n)
Move: Floyd's cycle detection — advance a slow pointer one step and a fast pointer two; if they meet, a cycle exists, if fast hits null, none.
File: [coding_linked_list_cycle.md](../../tiers/foundation/coding_linked_list_cycle.md)
</details>

**51 / 145**

<details><summary><b>Distinct-int array — return all possible subsets (the power set)</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(2^n)
Move: Recursively decide include/exclude for each element to cascade-build subsets, or enumerate bitmask integers 0..2^n-1 and map set bits to indices.
File: [coding_subsets.md](../../tiers/advanced/coding_subsets.md)
</details>

**52 / 145**

<details><summary><b>Design a TinyURL-like service: encode a long URL to a short key and decode it back</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(1) per op
Move: Two-way map (long ↔ short) backed by a random base62 ID generator; encode generates a new key, decode looks it up.
File: [coding_encode_and_decode_tinyurl.md](../../tiers/foundation/coding_encode_and_decode_tinyurl.md)
</details>

**53 / 145**

<details><summary><b>Array of matchstick lengths — can every stick be used exactly once to form a square?</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(4^n)
Move: Sort descending so large sticks fail early, recurse into 4 sides of target sum/4, and break symmetry by skipping sibling sides with equal partial sums.
File: [coding_matchsticks_to_square.md](../../tiers/advanced/coding_matchsticks_to_square.md)
</details>

**54 / 145**

<details><summary><b>decode a string with patterns like 3[a2[c]] => accaccacc</b></summary>

Pattern: Stack &nbsp;|&nbsp; Medium
Move: Two stacks (counts and buffers); expand buffered substring on closing bracket.
File: [coding_decode_string.md](../../tiers/intermediate/coding_decode_string.md)
</details>

**55 / 145**

<details><summary><b>min steps to spell a key by rotating a ring and pressing its center button</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: dp[i][j] = min steps to spell key[i:] starting with ring at position j.
File: [coding_freedom_trail.md](../../tiers/intermediate/coding_freedom_trail.md)
</details>

**56 / 145**

<details><summary><b>parenthesize a/b/c/d/... to maximize the resulting value</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: For n >= 3 the max is nums[0] / (nums[1] / nums[2] / ... / nums[n-1]).
File: [coding_optimal_division.md](../../tiers/intermediate/coding_optimal_division.md)
</details>

**57 / 145**

<details><summary><b>Children greed factors g[] and cookie sizes s[] — maximize content children (a cookie satisfies a child iff size ≥ greed)</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n log n + m log m)
Move: Sort both arrays; two-pointer match — feed the smallest remaining cookie that satisfies the smallest unmet greed.
File: [coding_assign_cookies.md](../../tiers/expert/coding_assign_cookies.md)
</details>

**58 / 145**

<details><summary><b>A string and int k — length of the longest substring where every char appears at least k times</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(n * 26)
Move: For each candidate count h of unique chars (1..26), run a window whose char set stays at size h; valid when every in-window char count >= k.
File: [coding_longest_substring_with_at_least_k_repeating_characters.md](../../tiers/foundation/coding_longest_substring_with_at_least_k_repeating_characters.md)
</details>

**59 / 145**

<details><summary><b>find first bad version in a linear sequence via an isBadVersion API</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Easy
Move: Left-biased convergence to minimize bad API calls.
File: [coding_first_bad_version.md](../../tiers/intermediate/coding_first_bad_version.md)
</details>

**60 / 145**

<details><summary><b>count contiguous subarrays whose product is less than k</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Sliding window with combinatorial count of new subarrays per right bound.
File: [coding_subarray_product_less_than_k.md](../../tiers/intermediate/coding_subarray_product_less_than_k.md)
</details>

**61 / 145**

<details><summary><b>A single word — check if its capitalization is valid (all caps, all lower, or only first letter caps)</b></summary>

Pattern: String &nbsp;|&nbsp; O(n)
Move: Count uppercase letters; valid iff the count equals the length, equals zero, or equals one and the first char is uppercase.
File: [coding_detect_capital.md](../../tiers/foundation/coding_detect_capital.md)
</details>

**62 / 145**

<details><summary><b>build a quad tree from an n x n grid of 0s/1s</b></summary>

Pattern: Divide & Conquer &nbsp;|&nbsp; Medium
Move: Quad-partition the grid; collapse uniform quadrants into leaves.
File: [coding_construct_quad_tree.md](../../tiers/intermediate/coding_construct_quad_tree.md)
</details>

**63 / 145**

<details><summary><b>Balloons as [start, end] horizontal intervals — minimum arrows to burst them all (one arrow bursts its x-coordinate)</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n log n)
Move: Sort intervals by end; greedily fire an arrow at the earliest end and skip every interval that also covers that point.
File: [coding_minimum_number_of_arrows_to_burst_balloons.md](../../tiers/expert/coding_minimum_number_of_arrows_to_burst_balloons.md)
</details>

**64 / 145**

<details><summary><b>Array of ints — sum the minimum element across every contiguous subarray (mod 1e9+7)</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: For each value find the previous- and next-lesser-element bounds via stacks; its contribution is value * leftCount * rightCount.
File: [coding_sum_of_subarray_minimums.md](../../tiers/expert/coding_sum_of_subarray_minimums.md)
</details>

**65 / 145**

<details><summary><b>fewest pigs needed to find the one poisonous bucket given T test rounds</b></summary>

Pattern: Math &nbsp;|&nbsp; Hard
Move: Each pig has (rounds+1) states; find smallest p with (T+1)^p >= buckets.
File: [coding_poor_pigs.md](../../tiers/intermediate/coding_poor_pigs.md)
</details>

**66 / 145**

<details><summary><b>median of a stream of integers as they arrive</b></summary>

Pattern: Two Heaps &nbsp;|&nbsp; Hard
Move: Balance a max-heap (lower half) and min-heap (upper half); rebalance on each insert.
File: [coding_median_finder.md](../../tiers/intermediate/coding_median_finder.md)
</details>

**67 / 145**

<details><summary><b>n points in 2D plane — count ordered triples (i, j, k) where dist(i, j) == dist(i, k)</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n^2)
Move: For each pivot, hash distances to all others; each bucket of size m contributes m*(m-1) ordered boomerangs (permutations counting).
File: [coding_number_of_boomerangs.md](../../tiers/foundation/coding_number_of_boomerangs.md)
</details>

**68 / 145**

<details><summary><b>find the longest absolute file path in a "\t"-indented filesystem string</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Track depth via tab count; stack maintains cumulative path length per level.
File: [coding_longest_absolute_file_path.md](../../tiers/intermediate/coding_longest_absolute_file_path.md)
</details>

**69 / 145**

<details><summary><b>find the lone element that appears once while all others appear twice</b></summary>

Pattern: Bit Manipulation &nbsp;|&nbsp; Easy
Move: XOR all elements; identical pairs cancel (x ^ x = 0) and leave the singleton.
File: [coding_single_number.md](../../tiers/intermediate/coding_single_number.md)
</details>

**70 / 145**

<details><summary><b>A 2D grid with a single connected landmass of 1s surrounded by water — compute its perimeter</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(rows * cols)
Move: For each land cell, add 4 and subtract 1 for each shared land neighbor (or sum 1 per water/out-of-bounds edge); dedupe shared boundaries.
File: [coding_island_perimeter.md](../../tiers/foundation/coding_island_perimeter.md)
</details>

**71 / 145**

<details><summary><b>add to each BST node the sum of all nodes with greater value</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Reverse in-order traversal accumulating a running sum.
File: [coding_convert_bst_to_greater_tree.md](../../tiers/intermediate/coding_convert_bst_to_greater_tree.md)
</details>

**72 / 145**

<details><summary><b>Array of houses and heaters on a line — find the minimum radius so every house is warmed</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n log n + m log m)
Move: Sort both, then for each house advance the heater pointer to the nearest one; take max of per-house nearest distances.
File: [coding_heaters.md](../../tiers/foundation/coding_heaters.md)
</details>

**73 / 145**

<details><summary><b>max length of a contiguous subarray with equal 0s and 1s</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Treat 0 as -1, track first index per running offset; max distance wins.
File: [coding_contiguous_array.md](../../tiers/intermediate/coding_contiguous_array.md)
</details>

**74 / 145**

<details><summary><b>max count of s2 obtainable by repeating s1 enough times to contain s2</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: Detect the cycle of matched char counts per s1 repetition to extrapolate.
File: [coding_count_the_repetitions.md](../../tiers/intermediate/coding_count_the_repetitions.md)
</details>

**75 / 145**

<details><summary><b>A license key string and group size k — reformat into groups of k separated by dashes, all uppercase</b></summary>

Pattern: String &nbsp;|&nbsp; O(n)
Move: Strip dashes, uppercase, then process backward grouping into blocks of k; the first (leading) group absorbs the remainder.
File: [coding_license_key_formatting.md](../../tiers/foundation/coding_license_key_formatting.md)
</details>

**76 / 145**

<details><summary><b>A sentence string — count how many segments (space-separated words) it contains</b></summary>

Pattern: String &nbsp;|&nbsp; O(n)
Move: Walk the string tracking space/non-space transitions with a state flag; a segment starts when a non-space follows a space (or begins the string).
File: [coding_number_of_segments_in_a_string.md](../../tiers/foundation/coding_number_of_segments_in_a_string.md)
</details>

**77 / 145**

<details><summary><b>Cars at given positions and speeds heading to a target on a single-lane road — count fleets arriving together</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n log n)
Move: Sort cars by position and compute each one's arrival time; a car fleets with the one ahead if its time ≤ that fleet's time, so count strictly increasing times.
File: [coding_car_fleet.md](../../tiers/expert/coding_car_fleet.md)
</details>

**78 / 145**

<details><summary><b>check if a string of brackets is properly opened and closed</b></summary>

Pattern: Stack &nbsp;|&nbsp; Easy
Move: Map each opener to its expected closer; reject mismatches and leftovers.
File: [coding_valid_parentheses.md](../../tiers/intermediate/coding_valid_parentheses.md)
</details>

**79 / 145**

<details><summary><b>Array of ints — does any subsequence i < j < k satisfy nums[i] < nums[k] < nums[j]?</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: Scan right to left tracking the largest valid nums[k] candidate so far; a decreasing stack exposes a nums[j] above it to test against.
File: [coding_132_pattern.md](../../tiers/expert/coding_132_pattern.md)
</details>

**80 / 145**

<details><summary><b>pick an index at random, weighted by w[i]</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Build cumulative weight prefix sums, binary-search the random roll.
File: [coding_random_pick_with_weight.md](../../tiers/intermediate/coding_random_pick_with_weight.md)
</details>

**81 / 145**

<details><summary><b>n x n matrix — rotate it 90° clockwise in place</b></summary>

Pattern: Matrix Traversal &nbsp;|&nbsp; O(n^2)
Move: Transpose the matrix (swap across the main diagonal), then reverse each row to reflect horizontally.
File: [coding_rotate_image.md](../../tiers/expert/coding_rotate_image.md)
</details>

**82 / 145**

<details><summary><b>Array of bar heights — find the area of the largest rectangle in the histogram</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: Push indices while heights stay non-decreasing; on a smaller bar, pop and compute area = height * (i - stack.top() - 1); track the running max.
File: [coding_largest_rectangle.md](../../tiers/expert/coding_largest_rectangle.md)
</details>

**83 / 145**

<details><summary><b>Split array into m contiguous subarrays — minimize the largest subarray sum</b></summary>

Pattern: Modified Binary Search &nbsp;|&nbsp; O(n log(sum))
Move: Binary-search the answer in [max(nums), sum(nums)]; the feasibility test greedily counts how many subarrays are needed at a given cap and returns true if ≤ m.
File: [coding_split_array_sum.md](../../tiers/advanced/coding_split_array_sum.md)
</details>

**84 / 145**

<details><summary><b>count islands of connected 1s in a 2D grid</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Flood-fill (sink) each land cell discovered during a grid scan.
File: [coding_number_of_islands.md](../../tiers/intermediate/coding_number_of_islands.md)
</details>

**85 / 145**

<details><summary><b>m x n matrix — return all elements in spiral order (outside-in)</b></summary>

Pattern: Matrix Traversal &nbsp;|&nbsp; O(m * n)
Move: Maintain top/bottom/left/right boundaries; peel one layer per loop, walking the four edges, then shrink the boundaries inward.
File: [coding_spiral_matrix.md](../../tiers/expert/coding_spiral_matrix.md)
</details>

**86 / 145**

<details><summary><b>compute product of every element except self, no division allowed</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium &nbsp;|&nbsp; O(1) space
Move: Build prefix/suffix products consolidated into a single output pass.
File: [coding_product_except_self.md](../../tiers/intermediate/coding_product_except_self.md)
</details>

**87 / 145**

<details><summary><b>Array of ints, find all unique triplets summing to zero</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n^2)
Move: Sort, then fix one element and run two-pointer pair search; skip duplicates at each anchor to avoid repeated triplets.
File: [coding_three_sum.md](../../tiers/foundation/coding_three_sum.md)
</details>

**88 / 145**

<details><summary><b>Array of n distinct ints in [0, n], one missing — find it in O(n) time, O(1) space</b></summary>

Pattern: Cyclic Sort &nbsp;|&nbsp; O(n)
Move: Cyclic-sort by swapping each value into its target slot (nums[i] → index nums[i]); the index still holding a wrong value is the missing one. XOR-summing 0..n against the array is an O(1)-space alternative.
File: [coding_missing_number.md](../../tiers/advanced/coding_missing_number.md)
</details>

**89 / 145**

<details><summary><b>An array possibly with duplicates — pick a random index of a given target value, uniform over its occurrences</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n) one pass
Move: Reservoir sampling — when a value equals target, hold its index with probability 1/count_so_far; alternatively precompute a target → indices map.
File: [coding_random_pick_index.md](../../tiers/foundation/coding_random_pick_index.md)
</details>

**90 / 145**

<details><summary><b>can a frog cross stones, with next jump being k-1, k, or k+1 of the last?</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: DFS with memo on (position, last jump); jumps are last-1, last, last+1.
File: [coding_frog_jump.md](../../tiers/intermediate/coding_frog_jump.md)
</details>

**91 / 145**

<details><summary><b>generate a uniformly random point inside a unit circle</b></summary>

Pattern: Math &nbsp;|&nbsp; Medium
Move: Inverse-CDF sample: r = R * sqrt(rand()), theta = 2*pi*rand(); reject corners.
File: [coding_generate_random_point_in_a_circle.md](../../tiers/intermediate/coding_generate_random_point_in_a_circle.md)
</details>

**92 / 145**

<details><summary><b>largest palindrome that is the product of two n-digit numbers</b></summary>

Pattern: Math &nbsp;|&nbsp; Hard
Move: Construct the palindrome from the upper half, search for factors, mod 1337.
File: [coding_largest_palindrome_product.md](../../tiers/intermediate/coding_largest_palindrome_product.md)
</details>

**93 / 145**

<details><summary><b>largest island area (4-connected 1s) in a grid</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: DFS each land cell, sink visited cells, accumulate and track max area.
File: [coding_max_area_island.md](../../tiers/intermediate/coding_max_area_island.md)
</details>

**94 / 145**

<details><summary><b>n nodes and a list of undirected edges — return the number of connected components</b></summary>

Pattern: Union Find &nbsp;|&nbsp; O(E * α(V))
Move: DSU with a parent[] array; for each edge call union(u, v); the answer is the count of distinct roots (or decrement a counter on each successful union).
File: [coding_connected_components.md](../../tiers/expert/coding_connected_components.md)
</details>

**95 / 145**

<details><summary><b>Binary tree — find the leftmost value in its last (bottom) row</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n)
Move: Level-order traversal enqueuing children right-to-left; the last node dequeued is the bottom-left value (queue state preservation).
File: [coding_find_bottom_left_tree_value.md](../../tiers/foundation/coding_find_bottom_left_tree_value.md)
</details>

**96 / 145**

<details><summary><b>implement uniform rand10() using only rand7()</b></summary>

Pattern: Randomized &nbsp;|&nbsp; Medium
Move: Rejection sample on 7*(rand7()-1) + rand7()-1; accept if value < 40.
File: [coding_implement_rand10_using_rand7.md](../../tiers/intermediate/coding_implement_rand10_using_rand7.md)
</details>

**97 / 145**

<details><summary><b>maintain a set of disjoint intervals as numbers stream in</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Hard
Move: Look up ordered boundaries, merge overlapping intervals on each add.
File: [coding_data_stream_as_disjoint_intervals.md](../../tiers/intermediate/coding_data_stream_as_disjoint_intervals.md)
</details>

**98 / 145**

<details><summary><b>Array of task labels and a cooldown n between two same tasks — minimum intervals to run them all (idle allowed)</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n)
Move: Compute the max-frequency task; idle slots = (maxFreq - 1) * (n + 1) plus the count of tasks tied at that max, floored at the total task count.
File: [coding_task_scheduler.md](../../tiers/expert/coding_task_scheduler.md)
</details>

**99 / 145**

<details><summary><b>Singly linked list head — return the middle node (second of two middles for even length)</b></summary>

Pattern: Fast & Slow Pointers &nbsp;|&nbsp; O(n)
Move: Slow moves one step, fast moves two; when fast reaches the end, slow lands on the middle node by parity.
File: [coding_middle_of_linked_list.md](../../tiers/foundation/coding_middle_of_linked_list.md)
</details>

**100 / 145**

<details><summary><b>k piles of bananas, h hours to eat them all (k per hour per pile) — find the minimum eating speed</b></summary>

Pattern: Modified Binary Search &nbsp;|&nbsp; O(n log maxPile)
Move: Binary-search the speed in [1, max(piles)]; feasibility test sums ceil(pile / speed) over piles and compares against h.
File: [coding_koko_bananas.md](../../tiers/advanced/coding_koko_bananas.md)
</details>

**101 / 145**

<details><summary><b>Array of ints — return all distinct non-decreasing subsequences of length ≥ 2</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(2^n)
Move: Backtrack preserving input order; at each recursion level skip a value equal to a previously-skipped sibling so the same subsequence can never be regenerated.
File: [coding_non_decreasing_subsequences.md](../../tiers/advanced/coding_non_decreasing_subsequences.md)
</details>

**102 / 145**

<details><summary><b>find the most frequent subtree sum in a binary tree</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Post-order sum each subtree, tally frequencies in a hashmap.
File: [coding_most_frequent_subtree_sum.md](../../tiers/intermediate/coding_most_frequent_subtree_sum.md)
</details>

**103 / 145**

<details><summary><b>An even-length candy array — max number of different types a person can take if they get exactly n/2 candies</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(n)
Move: Count distinct types via a set; the answer is the min of distinct types and n/2 (you cannot take more types than candies you're allowed).
File: [coding_distribute_candies.md](../../tiers/foundation/coding_distribute_candies.md)
</details>

**104 / 145**

<details><summary><b>maximum money you can rob without touching two adjacent houses</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: dp[i] = max(dp[i-1], dp[i-2] + nums[i]); two-variable reduction.
File: [coding_house_robber.md](../../tiers/intermediate/coding_house_robber.md)
</details>

**105 / 145**

<details><summary><b>fewest coins needed to make amount, given unlimited coins of each denomination</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: 1D unbounded knapsack; dp[a] = min(dp[a], 1 + dp[a - coin]).
File: [coding_coin_change.md](../../tiers/intermediate/coding_coin_change.md)
</details>

**106 / 145**

<details><summary><b>A grid of fresh and rotten oranges — every minute, rotten oranges rot 4-directional neighbors; min time until all rotten (or -1)</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(rows * cols)
Move: Multi-source BFS — seed the queue with all initially rotten oranges, count fresh ones; expand level by level, decrementing the fresh count each infection; -1 if any fresh remains.
File: [coding_rotting_oranges.md](../../tiers/foundation/coding_rotting_oranges.md)
</details>

**107 / 145**

<details><summary><b>count distinct substrings of the infinite cyclic "abcd...xyzabcd..." string</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: For each letter, track the max cyclic-consecutive run length ending in it.
File: [coding_unique_substrings_in_wraparound_string.md](../../tiers/intermediate/coding_unique_substrings_in_wraparound_string.md)
</details>

**108 / 145**

<details><summary><b>Binary tree — return the largest value in each row (level)</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n)
Move: Level-order BFS; at each level boundary track the row's running maximum and append it to the result list.
File: [coding_find_largest_value_in_each_tree_row.md](../../tiers/foundation/coding_find_largest_value_in_each_tree_row.md)
</details>

**109 / 145**

<details><summary><b>find minimum element in a rotated sorted array with no duplicates</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Medium
Move: Identify the unsorted half; the inflection (minimum) always lies there.
File: [coding_find_min_rotated.md](../../tiers/intermediate/coding_find_min_rotated.md)
</details>

**110 / 145**

<details><summary><b>design a stack with O(1) push, pop, top, and getMin</b></summary>

Pattern: Stack &nbsp;|&nbsp; Easy
Move: Auxiliary stack mirroring the current minimum at every push.
File: [coding_min_stack.md](../../tiers/intermediate/coding_min_stack.md)
</details>

**111 / 145**

<details><summary><b>Two strings — length of the longest uncommon subsequence (a subsequence of one but not the other)</b></summary>

Pattern: String &nbsp;|&nbsp; O(min(n, m))
Move: Logical deduction — if the strings are equal, no uncommon subsequence exists (-1); otherwise the longer string itself is the answer.
File: [coding_longest_uncommon_subsequence_i.md](../../tiers/foundation/coding_longest_uncommon_subsequence_i.md)
</details>

**112 / 145**

<details><summary><b>design an LFU cache with O(1) get and put</b></summary>

Pattern: Design &nbsp;|&nbsp; Hard
Move: HashMap key -> node plus one doubly-linked list per frequency; bump freq on access.
File: [coding_lfu_cache.md](../../tiers/intermediate/coding_lfu_cache.md)
</details>

**113 / 145**

<details><summary><b>find target index in a sorted array</b></summary>

Pattern: Binary Search &nbsp;|&nbsp; Easy
Move: Classical mid-point search with overflow-safe midpoint (lo + (hi-lo)/2).
File: [coding_binary_search.md](../../tiers/intermediate/coding_binary_search.md)
</details>

**114 / 145**

<details><summary><b>find the kth largest element in an unsorted array</b></summary>

Pattern: Top K Elements &nbsp;|&nbsp; Medium
Move: Quickselect partition, or maintain a size-k min-heap of the largest seen.
File: [coding_kth_largest.md](../../tiers/intermediate/coding_kth_largest.md)
</details>

**115 / 145**

<details><summary><b>count distinct ways to climb n stairs taking 1 or 2 steps</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Easy
Move: dp[i] = dp[i-1] + dp[i-2] (Fibonacci); reduce to two rolling variables.
File: [coding_climbing_stairs.md](../../tiers/intermediate/coding_climbing_stairs.md)
</details>

**116 / 145**

<details><summary><b>count paths of length N that move a ball out of an m x n grid</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: dp[step][r][c] = sum of four neighbors' counts, aggregated mod 1e9+7.
File: [coding_out_of_boundary_paths.md](../../tiers/intermediate/coding_out_of_boundary_paths.md)
</details>

**117 / 145**

<details><summary><b>An array of meeting start/end times — minimum number of conference rooms required</b></summary>

Pattern: Merge Intervals &nbsp;|&nbsp; O(n log n)
Move: Sweep-line — sort starts and ends separately, walk a counter that +1 on a start and -1 on an end, tracking the running peak.
File: [coding_meeting_rooms.md](../../tiers/foundation/coding_meeting_rooms.md)
</details>

**118 / 145**

<details><summary><b>count the number of set bits (popcount) in an unsigned integer</b></summary>

Pattern: Bit Manipulation &nbsp;|&nbsp; Easy
Move: Brian Kernighan's n & (n-1) clears the lowest set bit each iteration.
File: [coding_number_of_1_bits.md](../../tiers/intermediate/coding_number_of_1_bits.md)
</details>

**119 / 145**

<details><summary><b>Int array that may contain duplicates — return all distinct subsets</b></summary>

Pattern: Subsets &nbsp;|&nbsp; O(2^n)
Move: Sort the array first; at each recursion level skip a value equal to the sibling you just declined at this depth to prevent regenerating the same subset.
File: [coding_subsets_ii.md](../../tiers/advanced/coding_subsets_ii.md)
</details>

**120 / 145**

<details><summary><b>Daily temperatures — for each day return the count of days until a warmer one (or 0)</b></summary>

Pattern: Monotonic Stack &nbsp;|&nbsp; O(n)
Move: Maintain a decreasing stack of indices; when a warmer day arrives, pop each cooler index and record the day-gap to it.
File: [coding_daily_temperatures.md](../../tiers/expert/coding_daily_temperatures.md)
</details>

**121 / 145**

<details><summary><b>Phone keypad digits (2-9) — list every letter string the digits could spell</b></summary>

Pattern: Backtracking &nbsp;|&nbsp; O(4^n)
Move: Map each digit to its letters and recurse by appending one letter per digit, walking the digit string left to right (equivalently, a BFS queue of growing prefixes).
File: [coding_letter_combinations.md](../../tiers/advanced/coding_letter_combinations.md)
</details>

**122 / 145**

<details><summary><b>Strings s and p — find all start indices in s of substrings that are anagrams of p</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(|s|)
Move: Fixed-width window of size |p| sliding one step; compare the window's char frequency map against p's map (diffing counters).
File: [coding_find_anagrams.md](../../tiers/foundation/coding_find_anagrams.md)
</details>

**123 / 145**

<details><summary><b>does any contiguous subarray of size >= 2 sum to a multiple of k?</b></summary>

Pattern: Prefix Sum &nbsp;|&nbsp; Medium
Move: Hash prefix-sum remainders mod k to match earlier offsets (distance >= 2).
File: [coding_continuous_subarray_sum.md](../../tiers/intermediate/coding_continuous_subarray_sum.md)
</details>

**124 / 145**

<details><summary><b>List of strings — return length of the longest one that is not a subsequence of any other string in the list</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(n^2 * L)
Move: For each candidate, check it against all others via subsequence test; longer string can never be a subsequence of a shorter one.
File: [coding_longest_uncommon_subsequence_ii.md](../../tiers/foundation/coding_longest_uncommon_subsequence_ii.md)
</details>

**125 / 145**

<details><summary><b>A list of words — return those that can be typed using letters of only one row of a US keyboard</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(total letters)
Move: Build a set per keyboard row (or a char → row map); a word qualifies iff all its chars map to the same row set.
File: [coding_keyboard_row.md](../../tiers/foundation/coding_keyboard_row.md)
</details>

**126 / 145**

<details><summary><b>A string s and a dictionary of words — find the longest word in dict that can be formed by deleting chars from s</b></summary>

Pattern: Two Pointers &nbsp;|&nbsp; O(d * |s|)
Move: Sort dict by length desc then lexicographic; greedily walk each candidate against s with a match pointer; first match wins.
File: [coding_longest_word_in_dictionary_through_deleting.md](../../tiers/foundation/coding_longest_word_in_dictionary_through_deleting.md)
</details>

**127 / 145**

<details><summary><b>List of "a==b" / "a!=b" equations — can they all be satisfied simultaneously?</b></summary>

Pattern: Union Find &nbsp;|&nbsp; O(E * α(V))
Move: Process every "==" equation first, unioning the variables; then verify each "!=" pair has different roots under find().
File: [coding_satisfiability_equations.md](../../tiers/expert/coding_satisfiability_equations.md)
</details>

**128 / 145**

<details><summary><b>flip a random unused cell in an m x n matrix until reset()</b></summary>

Pattern: Randomized &nbsp;|&nbsp; Medium
Move: Map a flat random index through a swap-dict as the available bound shrinks by one.
File: [coding_random_flip_matrix.md](../../tiers/intermediate/coding_random_flip_matrix.md)
</details>

**129 / 145**

<details><summary><b>length of the longest palindromic subsequence of a string</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Medium
Move: 2D range DP; dp[i][j] = dp[i+1][j-1] + 2 on match else max of inner.
File: [coding_longest_palindromic_subsequence.md](../../tiers/intermediate/coding_longest_palindromic_subsequence.md)
</details>

**130 / 145**

<details><summary><b>Tree edges plus one extra edge that closes a cycle — return the edge whose removal restores a tree</b></summary>

Pattern: Union Find &nbsp;|&nbsp; O(E * α(V))
Move: Iterate edges through DSU; the first edge whose two endpoints already share a root is the redundant cycle-closer — return it.
File: [coding_redundant_connection.md](../../tiers/expert/coding_redundant_connection.md)
</details>

**131 / 145**

<details><summary><b>m x n grid of chars and a list of words — return every word findable by walking adjacent cells</b></summary>

Pattern: Trie &nbsp;|&nbsp; O(m * n * 4^L)
Move: Insert all words into a Trie; DFS the grid cell-by-cell descending only when a Trie child exists; prune Trie leaves on each word hit to avoid re-reporting.
File: [coding_word_search_ii.md](../../tiers/advanced/coding_word_search_ii.md)
</details>

**132 / 145**

<details><summary><b>numCourses and prerequisite pairs [a, b] meaning "b before a" — can you finish every course?</b></summary>

Pattern: Graph &nbsp;|&nbsp; O(V + E)
Move: Build the adjacency list, then run Kahn's BFS (queue in-degree-zero nodes) or DFS color states (0/1/2) to detect a back-edge — a cycle means impossible.
File: [coding_course_schedule.md](../../tiers/expert/coding_course_schedule.md)
</details>

**133 / 145**

<details><summary><b>fewest drops to find the highest safe floor with K eggs and N floors</b></summary>

Pattern: Dynamic Programming &nbsp;|&nbsp; Hard
Move: Inverse DP: dp[moves][eggs] = max floors testable; binary-search the moves.
File: [coding_super_egg_drop.md](../../tiers/intermediate/coding_super_egg_drop.md)
</details>

**134 / 145**

<details><summary><b>flip all bits of a non-negative integer (no leading zeros kept)</b></summary>

Pattern: Bit Manipulation &nbsp;|&nbsp; Easy
Move: Build an all-ones mask the bit-length of n, then XOR n with that mask.
File: [coding_number_complement.md](../../tiers/intermediate/coding_number_complement.md)
</details>

**135 / 145**

<details><summary><b>n x n binary grid — length of the shortest clear path from (0,0) to (n-1,n-1) moving in 8 directions</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n^2)
Move: 8-directional BFS from the start; mark cells in-place on visit and expand level by level; the level when the target is dequeued is the answer.
File: [coding_shortest_path_binary.md](../../tiers/foundation/coding_shortest_path_binary.md)
</details>

**136 / 145**

<details><summary><b>Binary search tree — serialize to a string and reconstruct the BST from it</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n)
Move: Stream a level-order (or pre-order) binary sequence; on deserialize, rebuild respecting BST bounds (or split by min/max ranges at each node).
File: [coding_serialize_and_deserialize_bst.md](../../tiers/foundation/coding_serialize_and_deserialize_bst.md)
</details>

**137 / 145**

<details><summary><b>A string — length of the longest substring with no repeating characters</b></summary>

Pattern: Sliding Window &nbsp;|&nbsp; O(n)
Move: Expand right, keep a map of last-seen indices; when a repeat falls inside the window, jump the left pointer past it (dynamic left update).
File: [coding_longest_substring.md](../../tiers/foundation/coding_longest_substring.md)
</details>

**138 / 145**

<details><summary><b>return popcount for every integer from 0 to n</b></summary>

Pattern: Bit Manipulation &nbsp;|&nbsp; Easy
Move: DP on bits: dp[i] = dp[i >> 1] + (i & 1).
File: [coding_counting_bits.md](../../tiers/intermediate/coding_counting_bits.md)
</details>

**139 / 145**

<details><summary><b>Array of n ints in [1, n], some appear twice, others vanish — return all missing numbers in O(n)</b></summary>

Pattern: Cyclic Sort &nbsp;|&nbsp; O(n)
Move: For every value x, negate nums[x - 1] as a seen-flag; after the pass, indices still holding a positive value are the missing numbers.
File: [coding_find_disappeared.md](../../tiers/advanced/coding_find_disappeared.md)
</details>

**140 / 145**

<details><summary><b>longest set you can form by chaining index -> nums[index] starting anywhere</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Walk the permutation, negating visited indices to mark cycle membership.
File: [coding_array_nesting.md](../../tiers/intermediate/coding_array_nesting.md)
</details>

**141 / 145**

<details><summary><b>A positive integer — repeatedly replace it with the sum of the squares of its digits; does it converge to 1?</b></summary>

Pattern: Fast & Slow Pointers &nbsp;|&nbsp; O(log n)
Move: Treat the digit-sum sequence like a linked list; run slow/fast on the function iterates — a cycle that isn't 1 means unhappy.
File: [coding_happy_number.md](../../tiers/foundation/coding_happy_number.md)
</details>

**142 / 145**

<details><summary><b>Array of max jump lengths — starting at index 0, can you reach the last index?</b></summary>

Pattern: Greedy &nbsp;|&nbsp; O(n)
Move: Track the maximum reachable index as you scan left to right; if i ever passes it, the goal is unreachable.
File: [coding_jump_game.md](../../tiers/expert/coding_jump_game.md)
</details>

**143 / 145**

<details><summary><b>Design a set with insert, remove, and getRandom all in average O(1)</b></summary>

Pattern: Hashmap &nbsp;|&nbsp; O(1) avg per op
Move: Combine a dynamic vector (values) with a hash table (value → index); swap-remove the last element into the deleted slot to keep indices valid.
File: [coding_insert_delete_getrandom_o1.md](../../tiers/foundation/coding_insert_delete_getrandom_o1.md)
</details>

**144 / 145**

<details><summary><b>Binary tree root — return its nodes level by level, left to right (list of lists)</b></summary>

Pattern: BFS &nbsp;|&nbsp; O(n)
Move: Queue with per-level sizing — record the queue length, dequeue exactly that many to build one sub-array, enqueue their children, repeat.
File: [coding_level_order.md](../../tiers/foundation/coding_level_order.md)
</details>

**145 / 145**

<details><summary><b>can you reach any index holding value 0, jumping by +/- arr[i]?</b></summary>

Pattern: DFS &nbsp;|&nbsp; Medium
Move: Mark visited by negating arr[i]; DFS the two jump targets within bounds.
File: [coding_jump_game_three.md](../../tiers/intermediate/coding_jump_game_three.md)
</details>

---

[Back to Flashcard Index](../README.md)