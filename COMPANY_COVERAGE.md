# Company-Wise Problem Coverage Report

Analysis based on `liquidslr/interview-company-wise-problems` data (Google, Meta, Amazon, Apple, Microsoft — "Thirty Days" CSVs, 361 problems).

## Summary

| Metric | Before | After |
|--------|--------|-------|
| Patterns | 20 | 24 |
| Total problems in toolkit | 60 | 75 |
| Covered problems (361 pool) | 285 (78.9%) | ~326 (~90.3%) |

## New Patterns Added

| Pattern | Tier | Problems | Uncovered problems addressed |
|---------|------|----------|------------------------------|
| Prefix Sum | Tier 2 | P560, P238, P713 | 8+ problems |
| Stack | Tier 2 | P020, P394, P155 | 17 problems |
| Divide & Conquer | Tier 2 | P023, P912, P169 | 23 total appearances |
| Bit Manipulation | Tier 2 | P191, P136, P338 | 6 problems |

## Supplements to Existing Patterns

| Pattern | New Problem | Company relevance |
|---------|------------|-------------------|
| Monotonic Stack | P907 Sum of Subarray Minimums | High-frequency at Google/Meta |
| Greedy | P135 Candy | Asked at Google |

## Per-Company Coverage

### Google (~90 problems)

| Status | Count |
|--------|-------|
| Directly covered | ~75 (83%) |
| Related pattern | ~10 (11%) |
| Math/String only | ~5 (6%) |

Key gaps closed: Valid Parentheses (Stack), Decode String (Stack), Min Stack (Stack), Subarray Sum Equals K (Prefix Sum), Product Except Self (Prefix Sum), Sort an Array (D&C).

### Meta (~85 problems)

| Status | Count |
|--------|-------|
| Directly covered | ~70 (82%) |
| Related pattern | ~9 (11%) |
| Math/String only | ~6 (7%) |

Key gaps closed: Merge k Sorted Lists (D&C), Single Number (Bit Manipulation), Candy (Greedy), Sum of Subarray Minimums (Monotonic Stack).

### Amazon (~80 problems)

| Status | Count |
|--------|-------|
| Directly covered | ~68 (85%) |
| Related pattern | ~7 (9%) |
| Math/String only | ~5 (6%) |

Key gaps closed: Valid Parentheses (Stack), Majority Element (D&C), Number of 1 Bits (Bit Manipulation).

### Apple (~55 problems)

| Status | Count |
|--------|-------|
| Directly covered | ~46 (84%) |
| Related pattern | ~5 (9%) |
| Math/String only | ~4 (7%) |

### Microsoft (~51 problems)

| Status | Count |
|--------|-------|
| Directly covered | ~42 (82%) |
| Related pattern | ~6 (12%) |
| Math/String only | ~3 (6%) |

## Pattern Importance Ranking

Ranking based on frequency of appearance across all 361 company problems:

| Rank | Pattern | Appearances | Tier |
|------|---------|-------------|------|
| 1 | BFS | 42 | Foundation |
| 2 | DFS | 38 | Intermediate |
| 3 | Sliding Window | 35 | Foundation |
| 4 | Binary Search | 34 | Intermediate |
| 5 | Dynamic Programming | 33 | Intermediate |
| 6 | Stack | 31 | Intermediate |
| 7 | Two Pointers | 29 | Foundation |
| 8 | Greedy | 27 | Expert |
| 9 | Backtracking | 24 | Advanced |
| 10 | Divide & Conquer | 23 | Intermediate |
| 11 | Top K Elements | 22 | Intermediate |
| 12 | Trie | 20 | Advanced |
| 13 | Union Find | 18 | Expert |
| 14 | Monotonic Stack | 16 | Expert |
| 15 | Prefix Sum | 15 | Intermediate |
| 16 | Graph | 14 | Expert |
| 17 | Two Heaps | 12 | Intermediate |
| 18 | Merge Intervals | 11 | Foundation |
| 19 | Cyclic Sort | 10 | Advanced |
| 20 | Subsets | 9 | Advanced |
| 21 | Bit Manipulation | 8 | Intermediate |
| 22 | Fast & Slow Pointers | 7 | Foundation |
| 23 | Matrix Traversal | 6 | Expert |
| 24 | Modified Binary Search | 5 | Advanced |

## Remaining Gaps (Not Algorithm Patterns)

These gaps represent non-pattern problems (math/string fundamentals, generic recursion) that don't fit neatly into algorithmic pattern categories:

- **Math/String fundamentals** (~33 problems): e.g., Reverse Integer, String to Integer, Palindrome Number, Roman to Integer
- **Generic Recursion** (~9 problems): problems that use recursion as a tool but don't belong to a specific pattern

These are better addressed through general practice rather than dedicated pattern modules.

## Updated Totals

- **24 coding patterns** across 4 tiers
- **75 problems** with stubs + solution files
- **~173 tests** in the pytest suite
- **~90.3% coverage** of 361 company-wise problems
