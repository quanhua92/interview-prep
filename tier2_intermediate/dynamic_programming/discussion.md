# Dynamic Programming — Discussion Guide

## One-Liner
Break a problem into overlapping subproblems with optimal substructure, solve each once, and cache results to avoid exponential recomputation.

## Core Concepts

### Recognizing a DP Problem
DP applies when two conditions hold:
1. **Overlapping subproblems** -- the same subproblem is solved multiple times in naive recursion.
2. **Optimal substructure** -- the optimal solution to a problem contains optimal solutions to its subproblems.

Signal words in problem statements: "count the number of ways", "find the minimum cost", "find the longest/shortest", "can you reach X". DP is NOT the right pattern if you can make a greedy choice that is always optimal.

### 5-Step DP Formulation
1. **Define the state** -- What does dp[i] represent? Be precise. Example: dp[i] = minimum coins needed to make amount i. State definition is the hardest and most important step.
2. **Identify base cases** -- What is the simplest instance? Example: dp[0] = 0 (0 coins for amount 0).
3. **Write the recurrence** -- How does dp[i] relate to smaller subproblems? Example: dp[i] = min(dp[i - coin] + 1) for each coin <= i.
4. **Determine order of computation** -- Bottom-up (tabulation) or top-down (memoization). Ensure each subproblem is solved before it is needed.
5. **Extract the answer** -- Often dp[n], but could be max(dp) or dp[n][m] depending on the problem.

## DP Pattern Taxonomy

| DP Type | State Shape | Classic Problems |
|---------|-------------|------------------|
| 1D Linear | dp[i] | Climbing Stairs, Coin Change, House Robber, Decode Ways |
| 2D Grid | dp[i][j] | Unique Paths, Minimum Path Sum, Edit Distance, LCS |
| 0/1 Knapsack | dp[i][w] | 0/1 Knapsack, Partition Equal Subset Sum, Target Sum |
| Interval DP | dp[l][r] | Burst Balloons, Matrix Chain Multiplication, Palindrome Partitioning |
| Sequence DP | dp[i] or dp[i][j] | LIS, LCS, Russian Doll Envelopes |
| DP on Trees | dp[node][state] | Tree Diameter, Max Path Sum, Binary Tree Robbery |

## Key Templates

### Top-Down (Memoization)
```python
def solve(n):
    memo = {}

    def dp(i):
        if i in memo:
            return memo[i]
        if i == 0:
            return BASE_CASE_VALUE
        result = min/max(dp(i-1), dp(i-2), ...)
        memo[i] = result
        return result

    return dp(n)
```

### Bottom-Up (Tabulation)
```python
def solve(n):
    dp = [INITIAL_VALUE] * (n + 1)
    dp[0] = BASE_CASE_VALUE

    for i in range(1, n + 1):
        dp[i] = min/max(dp[i-1], dp[i-2], ...)

    return dp[n]
```

## Space Optimization
Many 2D DP problems can be reduced to 1D by observing that dp[i][j] only depends on the previous row. Use a rolling array: `dp = dp_prev` after each row. This reduces space from O(n*m) to O(m). Common in: Knapsack, Edit Distance, LCS.

## Classic Problem Walkthroughs

### Coin Change (1D DP)
- State: dp[i] = min coins to make amount i
- Base: dp[0] = 0
- Recurrence: dp[i] = min(dp[i - c] + 1) for c in coins if c <= i
- Answer: dp[amount] (or -1 if unreachable)
- Time: O(amount * len(coins)), Space: O(amount)

### Longest Increasing Subsequence (Two Approaches)
1. **DP O(n^2)**: dp[i] = length of LIS ending at index i. Recurrence: dp[i] = max(dp[j] + 1) for all j < i where nums[j] < nums[i].
2. **Patience Sorting O(n log n)**: Maintain `tails` array where tails[i] = smallest tail of all increasing subsequences of length i+1. Binary search for insert position.

### Edit Distance (2D DP with Space Optimization)
- State: dp[i][j] = min edits to convert word1[:i] to word2[:j]
- Recurrence: If chars match, dp[i][j] = dp[i-1][j-1]. Else dp[i][j] = 1 + min(delete, insert, replace).
- Space optimization: only need previous row, reducing O(m*n) to O(min(m,n)).

### 0-1 Knapsack (Classic 2D DP)
- State: dp[i][w] = max value using first i items with capacity w
- Recurrence: dp[i][w] = max(dp[i-1][w], dp[i-1][w-wt] + val)
- Space optimization: iterate capacity BACKWARDS to prevent using item twice (0-1 constraint)
- Unbounded variant: iterate FORWARD (item can be used multiple times)

## Interview Questions

1. **DP vs Greedy** -- How do you know which to use? Give an example where greedy fails but DP succeeds.
2. **Top-down vs Bottom-up** -- When to choose memoization vs tabulation?
3. **0/1 Knapsack state definition** -- Explain why iterating capacity backwards is required in the 1D space-optimized version.
4. **Optimization ladder** -- Your DP passes all test cases but TLEs on large inputs. Walk through the optimizations you would apply.

## Follow-Up Variations
- How would you reconstruct the actual solution (not just the value) for a DP problem?
- What if the state space is too large for full tabulation -- can you use meet-in-the-middle or bitmask DP?
- How does DP on trees differ from standard DP -- what additional state do you track?

Source: [Dynamic Programming: From Recursion to Optimization (CalibreOS)](https://www.calibreos.com/learn/dsa-dynamic-programming)

---

## Knapsack DP Deep Dive: 0/1, Unbounded, Bounded, and Disguised Variants

Source: [Knapsack DP: 0/1, Unbounded, and Subset Sum Variants (CalibreOS)](https://www.calibreos.com/learn/dsa-dp-knapsack)

### The Unified Mental Model

Every knapsack variant reduces to one structural question: **given items with associated weights (and optionally values), can we fill a capacity W optimally?** The state is always `dp[i][w] = best result` (max value, boolean reachability, or number of ways) using the first i items with remaining capacity w.

Recognizing a knapsack problem requires seeing past the surface framing. Keywords: "subset," "select," "fill exactly," "maximum/minimum given a constraint," and critically, "each element used at most once" (0/1) vs "unlimited" (unbounded). Problems saying "partition" or "split the array" are almost always 0/1 knapsack. Problems saying "coins" or "unlimited supply" are almost always unbounded knapsack.

The three structural variants:
- **0/1 Knapsack**: each item used at most once. 1D space optimization iterates capacity in **reverse** to prevent reusing items.
- **Unbounded Knapsack**: each item used unlimited times. 1D space optimization iterates capacity **forward** so updates from the current pass feed back in.
- **Bounded Knapsack**: each item used up to k_i times. Reduces to 0/1 by replicating each item k_i times, or solved in O(nW log max_k) with a deque-based sliding window optimization.

The forward-vs-reverse iteration insight is the single most important thing to understand about knapsack.

### What Interviewers Test

Knapsack problems at FAANG test two distinct skills: (1) can you **recognize the reduction**? Problems like Partition Equal Subset Sum and Target Sum don't say "knapsack" -- you must see the disguise. (2) do you **know the forward vs reverse iteration rule** and can you explain *why*, not just recite which direction? The answer "reverse because forward would double-count" is acceptable. "I just remember reverse for 0/1" is not -- follow-up questions will expose the gap. Expect interviewers to flip one condition ("what if items can be reused?") and ask you to adapt on the spot.

### 0/1 Knapsack -- Both 2D and Space-Optimized

```python
def knapsack_01_2d(weights, values, capacity):
    """0/1 Knapsack, 2D DP. O(nW) time, O(nW) space.
    Use in interviews to establish correctness before optimizing."""
    n = len(weights)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        wt, val = weights[i - 1], values[i - 1]
        for w in range(capacity + 1):
            dp[i][w] = dp[i - 1][w]                      # skip item i
            if wt <= w:
                dp[i][w] = max(dp[i][w], dp[i - 1][w - wt] + val)  # take item i
    return dp[n][capacity]


def knapsack_01(weights, values, capacity):
    """0/1 Knapsack, space-optimized. O(nW) time, O(W) space.
    CRITICAL: iterate w from capacity DOWN to weights[i].
    Reverse order ensures dp[w - wt] reflects the PREVIOUS item's row."""
    dp = [0] * (capacity + 1)

    for i in range(len(weights)):
        wt, val = weights[i], values[i]
        for w in range(capacity, wt - 1, -1):  # reverse: high -> low
            dp[w] = max(dp[w], dp[w - wt] + val)

    return dp[capacity]
```

### Partition Equal Subset Sum -- 0/1 Knapsack in Disguise

LC 416: given an integer array, can you partition it into two subsets with equal sum?

**The reduction**: if total sum is odd, return False immediately. Otherwise, ask: "can we find a subset that sums to total/2?" This is exactly 0/1 knapsack where weight = value = each number, capacity = total/2, and we ask if dp[total/2] is reachable.

**State change**: instead of `dp[w] = max value`, use `dp[w] = True/False` (can we achieve sum exactly w?). Transition: `dp[w] = dp[w] or dp[w - num]`. Still iterate in reverse. Base case: `dp[0] = True`.

**Early termination**: if any single element equals total/2, return True. If any element exceeds total/2, return False. These checks show you're thinking about edge cases.

The same reduction works for: LC 698 (Partition to K Equal Subsets), LC 474 (Ones and Zeroes -- 2D knapsack with two capacity dimensions), LC 494 (Target Sum -- count paths instead of boolean reachability).

```python
def can_partition(nums):
    """Partition Equal Subset Sum (LC 416). Reduce to 0/1 knapsack.
    Time: O(n * total), Space: O(total)"""
    total = sum(nums)
    if total % 2 != 0:
        return False
    target = total // 2
    if max(nums) > target:
        return False

    dp = [False] * (target + 1)
    dp[0] = True  # empty subset achieves sum 0

    for num in nums:
        for w in range(target, num - 1, -1):  # reverse, 0/1
            dp[w] = dp[w] or dp[w - num]
        if dp[target]:
            return True  # early termination

    return dp[target]
```

### Unbounded Knapsack -- Forward Iteration Unlocks Reuse

In 2D, when taking item i, instead of looking at `dp[i-1][w-wt]` (previous row, before item i was available), you look at `dp[i][w-wt]` (current row, where item i has already been counted). This allows using item i again.

In the 1D version, this translates to iterating capacity **forward** (from wt to W). When you compute dp[w] and look up dp[w-wt], forward direction means dp[w-wt] was already updated in this pass -- it may already incorporate item i. That's exactly what we want for unbounded.

Coin Change (LC 322) is unbounded knapsack where value = 1 for all coins (minimizing coins = minimizing total "cost"). `dp[w] = min(dp[w], dp[w - coin] + 1)`. Initialize dp[0] = 0, all others to infinity.

Coin Change II (LC 518) counts the number of ways to make the amount. `dp[w] += dp[w - coin]`, base dp[0] = 1. **Crucial**: coins outer loop, amounts inner loop (forward), to count combinations not permutations.

```python
def coin_change(coins, amount):
    """Coin Change (LC 322), min coins. Unbounded knapsack.
    FORWARD iteration. Time: O(amount * len(coins)), Space: O(amount)"""
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0

    for coin in coins:
        for w in range(coin, amount + 1):  # FORWARD, unbounded
            if dp[w - coin] != float('inf'):
                dp[w] = min(dp[w], dp[w - coin] + 1)

    return dp[amount] if dp[amount] != float('inf') else -1


def change(amount, coins):
    """Coin Change II (LC 518), number of combinations.
    Key: coins outer, amounts inner. Swapping loops counts permutations."""
    dp = [0] * (amount + 1)
    dp[0] = 1

    for coin in coins:
        for w in range(coin, amount + 1):  # FORWARD, unbounded
            dp[w] += dp[w - coin]

    return dp[amount]
```

### The Forward vs Reverse Iteration Deep Dive

**0/1 Knapsack (reverse, W down to wt)**: When computing `dp[w] = max(dp[w], dp[w - wt] + val)`, we need dp[w-wt] to reflect the state *before* item i was considered. Since w-wt < w and we iterate from large to small, dp[w-wt] has **not yet been updated** in the current pass. It still holds the value from the previous item. Correctness guaranteed.

**Unbounded Knapsack (forward, wt up to W)**: We want item i to be used multiple times. Since we iterate forward, dp[w-wt] **has already been updated** in the current pass, possibly with item i's contribution. dp[w-wt] saying "I already used item i once" allows the current update to add item i again.

Intuition pump: reverse = reading "dp[w-wt] from yesterday (previous item)." Forward = reading "dp[w-wt] from today (current item may already be included)."

**Coin Change II loop order subtlety**: for counting combinations (not permutations), outer loop = coins, inner loop = amounts, both forward. Swapping to outer=amounts, inner=coins gives permutations. For coins [1,2], amount 3: combinations = 2 ({1,2}, {1,1,1}), permutations = 3 ({1,2}, {2,1}, {1,1,1}). FAANG interviewers test this directly.

### Target Sum -- Counting Paths in 0/1 Knapsack

LC 494: add +/- signs to each number to hit a target. Naive DFS is O(2^n). DP reduction brings it to O(n * sum).

**The reduction**: let S+ be the subset assigned '+' and S- the subset assigned '-'.
- S+ - S- = target
- S+ + S- = total_sum
- Adding: 2 * S+ = total_sum + target, so S+ = (total_sum + target) / 2
- Problem reduces to: **count subsets that sum to S+**. This is 0/1 knapsack where dp[w] = number of ways.

**Edge cases** (FAANG interviewers love these):
- If (total_sum + target) is odd -> return 0 (can't achieve half an integer)
- If abs(target) > total_sum -> return 0 (unreachable)
- If S+ < 0 -> return 0
- Transition: `dp[w] += dp[w - num]`, reverse iteration (0/1)
- Base case: dp[0] = 1

The shift from boolean to count: Partition uses `dp[w] |= dp[w - num]`. Target Sum uses `dp[w] += dp[w - num]`. Same iteration direction because both are 0/1.

```python
def find_target_sum_ways(nums, target):
    """Target Sum (LC 494). Count ways to assign +/- to reach target.
    Reduction: count subsets summing to S+ = (total + target) // 2.
    Time: O(n * total), Space: O(total)"""
    total = sum(nums)

    if (total + target) % 2 != 0:
        return 0
    if abs(target) > total:
        return 0

    s_plus = (total + target) // 2
    if s_plus < 0:
        return 0

    dp = [0] * (s_plus + 1)
    dp[0] = 1

    for num in nums:
        for w in range(s_plus, num - 1, -1):  # REVERSE, 0/1
            dp[w] += dp[w - num]

    return dp[s_plus]
```

### Knapsack Variant Problem Map

| LC # | Problem | Knapsack Type | State dp[w] | Iteration | Base Case |
|------|---------|---------------|-------------|-----------|-----------|
| Classic | 0/1 Knapsack | 0/1 | max value | Reverse | dp[0]=0 |
| 416 | Partition Equal Subset Sum | 0/1 (boolean) | sum w reachable? | Reverse | dp[0]=True |
| 494 | Target Sum | 0/1 (count) | # subsets summing to w | Reverse | dp[0]=1 |
| 474 | Ones and Zeroes | 0/1 (2D) | max strings given 0-budget, 1-budget | Reverse (2D) | dp[0][0]=0 |
| 322 | Coin Change (min coins) | Unbounded (min) | min coins for amount w | Forward | dp[0]=0, rest=inf |
| 518 | Coin Change II (count ways) | Unbounded (count) | # combos for amount w | Forward (coins outer) | dp[0]=1 |
| 377 | Combination Sum IV | Unbounded (permutations) | # ordered ways for target | Forward (amounts outer) | dp[0]=1 |
| 279 | Perfect Squares | Unbounded (min) | min squares summing to n | Forward | dp[0]=0, rest=inf |
| 1049 | Last Stone Weight II | 0/1 (boolean) | reachable sums | Reverse | dp[0]=True |
| 698 | Partition to K Equal Subsets | 0/1 (boolean) | can k subsets each sum to total/k | Backtracking preferred | -- |
| Classic | Bounded Knapsack | Bounded | max value, item i used <= k_i times | Binary expansion -> 0/1 | dp[0]=0 |

### Four Classic Knapsack Mistakes

1. **Forward iteration for 0/1**: Iterating w from wt to W in a 0/1 problem allows dp[w-wt] to be updated by the current item in the same pass. You're now computing unbounded knapsack. This passes small test cases (where no item fits twice), making it insidious to debug.

2. **Odd-total check for Partition problems**: If total sum is odd, you cannot split into two equal-sum subsets. Return False before running any DP. Forgetting this causes wrong answers -- DP would claim success for target 4.5, which doesn't exist in integer arithmetic.

3. **Wrong base case for min-cost vs count**: For Coin Change (min coins), dp[0] = 0 and all other dp[w] = infinity. For Coin Change II (count ways), dp[0] = 1 and all other dp[w] = 0. Swapping these silently corrupts every cell.

4. **Permutations vs combinations in Coin Change II**: If you put amounts in the outer loop and coins in the inner loop, you count ordered ways (permutations). To count unordered combinations, coins must be the outer loop. Subtle loop-order bug that passes most test cases but fails inputs like coins=[1,2], amount=3 (correct answer 2, permutation answer 3).

### Knapsack Problem Recognition Checklist

1. **Identify the "items" and the "capacity"** -- Every knapsack problem has a set of choices (items) and a constraint budget (capacity). In Coin Change, coins are items and amount is capacity. In Partition Subset Sum, array elements are items and total/2 is capacity. If you can't identify these two, it's probably not knapsack.

2. **Determine 0/1 vs unbounded** -- Can each item be used more than once? Array partition/subset problems -> 0/1 (each element once). Coin/tile/resource problems with "unlimited supply" -> unbounded. Bounded: explicit per-item count limits -> binary expansion trick.

3. **Decide the state value type** -- Max/min value (standard optimization), boolean (can we reach exactly w? -> subset sum/partition), or count of ways (dp[w] sums instead of max). Choose initialization accordingly: 0 for max, True/False for boolean, 1 at dp[0] for count.

4. **Set base cases** -- dp[0] = 0 (max value, zero capacity -> nothing). dp[0] = True (can we reach sum 0? yes, empty set). dp[0] = 1 (one way to reach sum 0: select nothing). All other cells: 0/False for max/count; infinity for min-cost.

5. **Write the transition and fix iteration direction** -- 0/1: `for w in range(capacity, item_weight - 1, -1)`. Unbounded: `for w in range(item_weight, capacity + 1)`. For Coin Change II combinations, outer loop over coins. For permutations (LC 377), outer loop over amounts.

6. **Check for mathematical reduction first** -- Target Sum: reduce to subset count with target = (total + target) / 2. Partition: target = total / 2. Last Stone Weight II: minimize |S1 - S2| = minimize abs(total - 2*S1) -> find max reachable S1 <= total/2. Always reduce to a simpler known variant before writing a custom recurrence.

### Combinations vs Permutations in Counting Knapsack

Coin Change II (LC 518) counts **combinations** -- [1,2] and [2,1] are the same. Combination Sum IV (LC 377) counts **permutations** -- [1,2] and [2,1] are different sequences. The only code difference: Coin Change II puts coins in the outer loop, amounts in the inner loop. LC 377 puts amounts in the outer loop, coins in the inner loop. Both iterate amounts forward (unbounded). In an interview, explicitly state whether you're counting ordered or unordered selections before writing the loop structure.

### Knapsack Interview Questions

1. Why does 0/1 knapsack iterate capacity in reverse, but unbounded knapsack iterates forward?
2. How do you recognize that a problem is a knapsack variant in disguise?
3. Explain the reduction from Target Sum (LC 494) to subset count knapsack.
4. What changes in code between Coin Change II (combination count) and Combination Sum IV (permutation count)?
5. What is bounded knapsack, and how do you solve it efficiently?

---

## DP on Strings Deep Dive: LCS, Edit Distance, Regex Matching, and Distinct Subsequences

Source: [DP on Strings: LCS, Edit Distance, and Regex Matching (CalibreOS)](https://www.calibreos.com/learn/dsa-dp-strings)

### The Universal String DP Template

Every string DP problem reduces to one mental model: **dp[i][j] represents something about the first i characters of s1 and the first j characters of s2.** The key insight that trips up most candidates: **dp[i][j] uses 1-indexed positions, but accesses s1[i-1] and s2[j-1].** The first row (i=0) and first column (j=0) represent the empty string -- they hold your base cases.

The 2D table fills left-to-right, top-to-bottom. This guarantees that when you compute dp[i][j], the three cells it depends on are already filled:
- **Diagonal (dp[i-1][j-1])**: the characters at position i and j "matched" somehow, reduces both strings simultaneously.
- **Above (dp[i-1][j])**: something happened to s1[i] alone, you "consumed" a character from s1.
- **Left (dp[i][j-1])**: something happened to s2[j] alone, you "consumed" a character from s2.

Once you see that LCS, Edit Distance, and Distinct Subsequences all decompose into these three directions, the recurrences stop feeling like magic formulas. The state definition *is* the hardest part -- everything else is mechanical.

### What Interviewers Test in String DP

String DP problems are a FAANG litmus test for **pattern recognition under pressure**:
1. **Can you independently derive the state definition from the problem statement?**
2. **Do you know the space optimization trick and when to apply it?**
3. **Can you recognize when LPS reduces to LCS instead of requiring a separate recurrence?**

The answer that impresses: derive the recurrence live, code it with the 1D space optimization by default (not as an afterthought), and explain *why* the index goes from W to 0 for the rolling array.

### 5-Step State Definition Process for String DP

1. **Read for "subsequence" vs "substring"**: Subsequence = characters don't need to be contiguous -> DP likely. Substring = must be contiguous -> sometimes expand-around-center or sliding window beats DP. Never default to DP for substring problems without checking O(n) alternatives.
2. **Define dp[i][j] precisely**: Write the English sentence: "dp[i][j] is the [minimum/maximum/number of ways] to [do X] when considering [s1[:i]] and [s2[:j]]." If you can't write it in one clear sentence, your state is wrong.
3. **Identify the base cases**: Empty string is always a base case. What is the answer when one string is empty? LCS = 0, Edit Distance = j or i (all insertions/deletions), Distinct Subsequences = 0 or 1 depending on whether t is empty.
4. **Derive the transition**: Ask: "if s1[i-1] == s2[j-1], what happens?" Then: "if they don't match, what are my choices?" Map each choice to a neighbor cell. If choosing min/max over 2-3 options -> optimization problem. If summing -> counting problem.
5. **Determine space optimization potential**: If dp[i][j] only depends on dp[i-1][*] and dp[i][*-1], you can use a 1D rolling array. Space drops from O(nm) to O(min(n,m)).

### Longest Common Subsequence (LC 1143) -- Full Implementation

LCS is the canonical string DP problem. Every other string DP either reduces to LCS or uses the same mental model.

- **State**: dp[i][j] = length of LCS of s1[:i] and s2[:j].
- **Base cases**: dp[0][j] = dp[i][0] = 0 (LCS with an empty string is 0).
- **Transition**: If s1[i-1] == s2[j-1], dp[i][j] = dp[i-1][j-1] + 1. Otherwise dp[i][j] = max(dp[i-1][j], dp[i][j-1]).
- The non-obvious insight: the "not-match" case never looks at dp[i-1][j-1]. If both characters don't match, the diagonal tells you nothing useful.
- **Space optimization**: 1D rolling array (prev/curr). O(min(n,m)) by iterating over shorter string in inner loop.

```python
def lcs(s1: str, s2: str) -> int:
    """
    Longest Common Subsequence. O(nm) time, O(min(n,m)) space.
    Space trick: iterate over shorter string in inner loop.
    """
    if len(s1) < len(s2):
        s1, s2 = s2, s1

    m, n = len(s1), len(s2)
    prev = [0] * (n + 1)

    for i in range(1, m + 1):
        curr = [0] * (n + 1)
        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                curr[j] = prev[j - 1] + 1      # diagonal + 1
            else:
                curr[j] = max(prev[j], curr[j - 1])
        prev = curr

    return prev[n]


def lcs_reconstruct(s1: str, s2: str) -> str:
    """Reconstruct the actual LCS string. Requires full 2D table, O(nm) space."""
    m, n = len(s1), len(s2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    result = []
    i, j = m, n
    while i > 0 and j > 0:
        if s1[i - 1] == s2[j - 1]:
            result.append(s1[i - 1])
            i -= 1
            j -= 1
        elif dp[i - 1][j] > dp[i][j - 1]:
            i -= 1
        else:
            j -= 1
    return "".join(reversed(result))
```

### Edit Distance (LC 72) -- Space-Optimized Implementation

Three operations map directly to three transitions:
- **Insert into s1** -> dp[i][j-1] + 1 (left neighbor)
- **Delete from s1** -> dp[i-1][j] + 1 (above neighbor)
- **Replace s1[i-1]** -> dp[i-1][j-1] + 1 (diagonal)

If chars match, no operation needed: dp[i][j] = dp[i-1][j-1] (free diagonal move).

Base cases: dp[0][j] = j (j insertions), dp[i][0] = i (i deletions).

The connection to LCS: edit distance and LCS are dual perspectives on the same 2D table structure. If only insert/delete allowed (no replace), edit distance = n + m - 2 * LCS_length.

```python
def min_distance(word1: str, word2: str) -> int:
    """
    Edit Distance (LC 72). O(nm) time, O(min(n,m)) space.
    """
    if len(word1) < len(word2):
        word1, word2 = word2, word1

    m, n = len(word1), len(word2)
    prev = list(range(n + 1))  # base case: dp[0][j] = j

    for i in range(1, m + 1):
        curr = [i] + [0] * n   # base case: dp[i][0] = i
        for j in range(1, n + 1):
            if word1[i - 1] == word2[j - 1]:
                curr[j] = prev[j - 1]               # free match
            else:
                curr[j] = 1 + min(
                    prev[j - 1],   # replace
                    prev[j],       # delete from word1
                    curr[j - 1],   # insert into word1
                )
        prev = curr

    return prev[n]
```

### Longest Palindromic Subsequence vs Substring -- A Critical Distinction

**Longest Palindromic Subsequence (LC 516)**: characters need not be contiguous. **The trick: LPS(s) = LCS(s, reverse(s))**. A palindromic subsequence is exactly a subsequence common to both s and its reverse. O(n^2) time, O(n) space with rolling array.

```python
def longest_palindrome_subseq(s: str) -> int:
    """LPS via LCS reduction. O(n^2) time, O(n) space."""
    rev = s[::-1]
    n = len(s)
    prev = [0] * (n + 1)
    for i in range(1, n + 1):
        curr = [0] * (n + 1)
        for j in range(1, n + 1):
            if s[i - 1] == rev[j - 1]:
                curr[j] = prev[j - 1] + 1
            else:
                curr[j] = max(prev[j], curr[j - 1])
        prev = curr
    return prev[n]
```

**Longest Palindromic Substring (LC 5)**: characters must be contiguous. Expand-around-center dominates: for each position (and each pair of adjacent positions for even-length palindromes), expand outward while s[left] == s[right]. O(n^2) time, O(1) space. No DP table needed.

```python
def longest_palindrome_substr(s: str) -> str:
    """Expand-around-center: O(n^2) time, O(1) space. Better than DP."""
    best_start, best_len = 0, 1

    def expand(left: int, right: int) -> None:
        nonlocal best_start, best_len
        while left >= 0 and right < len(s) and s[left] == s[right]:
            left -= 1
            right += 1
        if right - left - 1 > best_len:
            best_len = right - left - 1
            best_start = left + 1

    for i in range(len(s)):
        expand(i, i)       # odd-length palindromes
        expand(i, i + 1)   # even-length palindromes

    return s[best_start: best_start + best_len]
```

When to use DP for palindromic substring: never for the basic problem. Use DP only when a parent problem requires the palindrome information as a subresult (e.g., Palindrome Partitioning II, LC 132, where you're minimizing cuts and need to query dp[i][j] many times).

**Interview-critical insight**: defaulting to DP for palindrome substring problems signals memorization, not understanding. An interviewer who asks "is there a better approach?" is testing whether you know expand-around-center exists.

### Regular Expression Matching (LC 10) -- The Hardest String DP

- **State**: dp[i][j] = True if s[:i] matches p[:j].
- **Base cases**: dp[0][0] = True. dp[0][j]: empty string can match patterns like `a*b*c*` -- if p[j-1] is `*`, then dp[0][j] = dp[0][j-2] (the `x*` pair matches zero occurrences).
- **Transitions**:
  - If p[j-1] is a regular character or `.`: dp[i][j] = dp[i-1][j-1] and (s[i-1] == p[j-1] or p[j-1] == `.`)
  - If p[j-1] is `*`: the `x*` pair can match zero or more of character p[j-2].
    - **Zero occurrences**: dp[i][j] = dp[i][j-2] (erase the `x*` pair from pattern)
    - **One or more occurrences**: dp[i][j] |= dp[i-1][j] if s[i-1] == p[j-2] or p[j-2] == `.` (consume one more s character, keep `*` active)

The "one or more" case uses dp[i-1][j] (not dp[i-1][j-2]) because you keep j fixed -- the same `x*` can still consume more characters, you only advance i. Common mistake: writing dp[i-1][j-2] which only handles exactly one match.

```python
def is_match(s: str, p: str) -> bool:
    """
    Regular Expression Matching (LC 10).
    '.' matches any single character.
    '*' matches zero or more of the preceding element.
    Time: O(len(s) * len(p)), Space: O(len(s) * len(p))
    """
    m, n = len(s), len(p)
    dp = [[False] * (n + 1) for _ in range(m + 1)]
    dp[0][0] = True

    # Base case: empty string matching patterns like a*b*c*
    for j in range(2, n + 1):
        if p[j - 1] == '*':
            dp[0][j] = dp[0][j - 2]

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if p[j - 1] == '*':
                dp[i][j] = dp[i][j - 2]  # zero occurrences
                if p[j - 2] == '.' or p[j - 2] == s[i - 1]:
                    dp[i][j] = dp[i][j] or dp[i - 1][j]  # one or more
            elif p[j - 1] == '.' or p[j - 1] == s[i - 1]:
                dp[i][j] = dp[i - 1][j - 1]

    return dp[m][n]
```

### Distinct Subsequences (LC 115) -- Counting with String DP

- **State**: dp[i][j] = number of ways s[:i] contains t[:j] as a subsequence.
- **Transition**: If s[i-1] == t[j-1]: dp[i][j] = dp[i-1][j-1] + dp[i-1][j] (use it or skip it). If they don't match: dp[i][j] = dp[i-1][j] (must skip).
- **Base cases**: dp[i][0] = 1 (one way to form empty string: select nothing). dp[0][j] = 0 for j > 0 (can't form non-empty string from empty s).
- The pattern shift: in LCS you take max, in Edit Distance you take min+1, here you take sum. The table structure and fill order are identical -- only the arithmetic changes.

### String DP Classic Problems Map

| LC # | Problem | State dp[i][j] | Transition Type | Space Opt. | Difficulty |
|------|---------|----------------|-----------------|------------|------------|
| 1143 | Longest Common Subsequence | LCS length of s1[:i], s2[:j] | max: diagonal+1 or skip | O(min(n,m)) | Medium |
| 72 | Edit Distance | Min edits: s1[:i] -> s2[:j] | min: match/insert/delete/replace | O(min(n,m)) | Medium |
| 516 | Longest Palindromic Subseq | LCS of s and reverse(s) | Reduce to LCS | O(n) | Medium |
| 5 | Longest Palindromic Substring | s[i..j] is palindrome? | expand-around-center preferred | O(1) w/ EAC | Medium |
| 10 | Regular Expression Matching | s[:i] matches p[:j]? | boolean: char match or * wildcard | O(len(p)) | Hard |
| 44 | Wildcard Matching | s[:i] matches p[:j]? | like LC 10 but simpler * rule | O(len(p)) | Hard |
| 115 | Distinct Subsequences | Ways s[:i] contains t[:j] | sum: use or skip match | O(len(t)) | Hard |
| 1092 | Shortest Common Supersequence | SCS length of s1[:i], s2[:j] | build on LCS length | O(min(n,m)) | Hard |
| 583 | Delete Operation for Two Strings | Min deletions to make equal | n+m - 2*LCS | O(min(n,m)) | Medium |
| 712 | Min ASCII Delete Sum | Min ASCII cost to equalize | weighted variant of LCS | O(min(n,m)) | Medium |

### Three Classic Off-by-One Traps in String DP

1. **Index mismatch**: dp[i][j] covers s[:i], so the character at position i in dp-land is s[i-1] in string-land. Forgetting this causes silent wrong answers, not crashes. Fix: write `s1[i-1]` and `s2[j-1]` everywhere in the transition, never `s1[i]`.

2. **Wrong base case for counting problems**: For Distinct Subsequences, dp[i][0] = 1 (one way to form empty string), NOT 0. For Edit Distance, dp[0][j] = j (j insertions needed), NOT 0. Getting base cases wrong makes the entire table incorrect.

3. **Empty-pattern base case in Regex Matching**: Patterns like `a*b*` match the empty string, requiring the dp[0][j] initialization loop that handles `x*` pairs. Skipping this fails all test cases where s is empty or the pattern has leading `x*`.

### The 1D Space Optimization -- When and Why

Apply the rolling array when dp[i][j] depends only on the current row and the previous row. Replace the 2D table with `prev = [0]*(n+1)` and `curr = [0]*(n+1)`, then `prev = curr` after each outer loop iteration.

**Gotcha**: in LCS, curr[j] depends on curr[j-1] (same row, earlier column), so you must fill j left-to-right and cannot combine into a single 1D array with in-place updates. Edit Distance has the same constraint. Both are correctly handled by the two-array (prev/curr) approach.

**In interviews**: implement the 2D version first and get it correct, then say "we can reduce space to O(min(n,m)) with a rolling array, want me to implement that?" This signals depth without risking a bug-prone optimization muddying your initial solution.

### String DP Interview Questions

1. How do you come up with the state definition for a string DP problem?
2. Explain the difference between Longest Palindromic Subsequence and Longest Palindromic Substring. Which requires DP?
3. Walk me through the `*` wildcard handling in Regular Expression Matching (LC 10). Why does the "one or more" case use dp[i-1][j] and not dp[i-1][j-2]?
4. How does the Distinct Subsequences recurrence differ from LCS? Why?
5. What is the base case for Edit Distance, and why is dp[0][j] = j not 0?
