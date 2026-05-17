# Greedy Algorithms — Discussion & Deep Dive

## One-Liner
Make the locally optimal choice at each step; when the problem has the greedy-choice property, this leads to a globally optimal solution in O(n log n) or O(n) time.

## Core Insight: Local Optimal = Global Optimal
A greedy algorithm works by making the best available choice at each step without reconsidering previous choices. This is fundamentally different from dynamic programming, which considers all subproblems. The critical question for any greedy problem is: **does making the locally optimal choice at each step guarantee the globally optimal solution?**

### The Exchange Argument
The standard proof technique for greedy correctness:
1. Assume an optimal solution makes a different choice at some step.
2. Show that you can "exchange" that choice for the greedy choice without making the solution worse.
3. If you can always exchange, the greedy solution is at least as good as optimal — therefore it IS optimal.

### Signal Words in Problem Statements
- "Maximize the number of" (activities, tasks)
- "Minimize the cost of" (connections, resources)
- "Earliest deadline"
- "Job scheduling"
- "Can you reach the end?"

## Greedy Problem Categories

### 1. Interval Scheduling — Sort by End Time
- **Goal:** Select the maximum number of non-overlapping intervals.
- **Strategy:** Sort intervals by end time. Always pick the interval that ends earliest (that doesn't overlap the last selected).
- **Why:** The interval ending earliest leaves the most time for future intervals.
- **Proof:** If an optimal solution picks interval A (ends later) instead of interval B (ends earlier), swapping B for A doesn't worsen the solution — B ends before A so B fits wherever A fits, and leaves MORE room.
- **Complexity:** O(n log n) sort + O(n) scan.

### 2. Activity Selection — Earliest Deadline First (EDF)
- **Goal:** Minimize lateness (each job has deadline and duration; lateness = finish_time - deadline).
- **Strategy:** Sort jobs by deadline, execute in that order.
- **Proof:** If two adjacent jobs are out of deadline order, swapping them reduces or maintains total lateness.
- **The EDF schedule minimizes maximum lateness.**
- **Used in:** Real-time scheduling, CPU task queues.

### 3. Jump Game — Forward Reach Tracking
- **Goal:** Can you reach the end from position 0, where nums[i] is the max jump distance?
- **Strategy:** Maintain `max_reach = 0`. For each position i: if i > max_reach, return False. Update `max_reach = max(max_reach, i + nums[i])`.
- **Greedy insight:** We never need to track which jump we take, only the farthest reachable position.
- **Variant (Jump Game II):** Use BFS-like greedy — track `current_end` (end of current jump range) and `farthest` (max reachable within current range). When i reaches `current_end`, increment jumps and set `current_end = farthest`.

### 4. Gas Station — Total Surplus Check
- **Goal:** Can you complete a circular tour if station i provides gas[i] and costs cost[i]?
- **Key insight:** If `total(gas) >= total(cost)`, a solution always exists.
- **Proof:** If total surplus is non-negative, there's always a starting point where you don't go negative.
- **Strategy:** Reset accumulated surplus to 0 whenever it goes negative; the next station after the reset is the candidate start.

### 5. Task Scheduler — Most-Frequent-First
- **Goal:** Minimum time to execute all tasks with cooldown n between same-type tasks.
- **Strategy:** Schedule the most frequent task first, then others, then idle if needed.
- **Formula:** `(max_freq - 1) x (n + 1) + count_of_tasks_with_max_freq` gives minimum intervals needed.
- **Edge case:** If total tasks > formula result, all tasks can be scheduled without idle time.

## Core Templates

### Max Non-Overlapping Intervals (interval scheduling)
```python
def eraseOverlapIntervals(intervals: list[list[int]]) -> int:
    intervals.sort(key=lambda x: x[1])  # sort by END time
    count = 0
    last_end = float('-inf')
    for start, end in intervals:
        if start >= last_end:
            count += 1
            last_end = end
    return len(intervals) - count  # intervals to REMOVE
# O(n log n) sort + O(n) scan
```

### Jump Game I (can you reach end?)
```python
def canJump(nums: list[int]) -> bool:
    max_reach = 0
    for i, jump in enumerate(nums):
        if i > max_reach:
            return False
        max_reach = max(max_reach, i + jump)
    return True
# O(n) time, O(1) space
```

### Jump Game II (minimum jumps to reach end)
```python
def jump(nums: list[int]) -> int:
    jumps = current_end = farthest = 0
    for i in range(len(nums) - 1):
        farthest = max(farthest, i + nums[i])
        if i == current_end:
            jumps += 1
            current_end = farthest
    return jumps
# O(n) time, O(1) space
```

### Gas Station
```python
def canCompleteCircuit(gas: list[int], cost: list[int]) -> int:
    total_surplus = current_surplus = start = 0
    for i in range(len(gas)):
        diff = gas[i] - cost[i]
        total_surplus += diff
        current_surplus += diff
        if current_surplus < 0:
            start = i + 1
            current_surplus = 0
    return start if total_surplus >= 0 else -1
# O(n) time, O(1) space
```

## Greedy vs DP: When to Use Which

| Problem type | Use greedy when | Use DP when | Example |
|---|---|---|---|
| Interval scheduling | Maximize # of non-overlapping intervals | Maximize TOTAL VALUE (weighted) | Unweighted: greedy. Weighted: DP |
| Coin change | Denominations are powers of each other (US coins) | Denominations are arbitrary | US coins: greedy. [1,3,4]: greedy fails (4+1+1 vs 3+3) |
| Path problems | All positive weights, no cycles | Negative weights or cycles exist | Dijkstra (greedy). Bellman-Ford (DP) |
| Scheduling with cost | Minimize max lateness (EDF) | Minimize total weighted lateness | Single machine: EDF. Weighted: DP |
| Subset selection | Greedy choice property provable | Overlapping subproblems, no greedy property | Fractional knapsack: greedy. 0/1 knapsack: DP |

## When Greedy Fails

### Counterexample: Coin Change with Non-Standard Denominations
Coins = [1, 3, 4], target = 6. Greedy picks 4 (largest <= 6), then 1, 1 = 3 coins. Optimal: 3 + 3 = 2 coins. Greedy fails because choosing the largest coin locally prevents finding the better 3+3 combination.

### Counterexample: Weighted Interval Scheduling
Jobs with values and time windows. Greedy "pick highest-value non-overlapping job" fails: you might skip two medium-value jobs that together outweigh the one high-value job. DP solves this (sort by end time, for each job choose max of: skip it, or take it + best for jobs ending before it starts).

### Counterexample: 0/1 Knapsack
Items have weight and value. Greedy "pick highest value/weight ratio" fails because items can't be fractionally taken. Fractional knapsack (items can be split) = greedy. 0/1 knapsack = DP.

### How to Test Greedy in an Interview
Try to construct a counterexample. If your greedy strategy is "pick the one with highest X," ask: can two lower-X options ever beat one high-X option? If yes, not greedy — use DP. If no (provably, via exchange argument), greedy is correct.

## Interview Delivery Tips
- Always state the greedy choice explicitly: "I'll sort by end time and greedily select intervals that don't overlap the last selected. The key insight is that choosing the interval that ends earliest maximizes remaining space for future selections."
- Distinguish from DP: "If this were the weighted version, where each interval has a profit, greedy wouldn't work because we'd need to consider whether skipping a profitable late-ending interval is worth it. That would be DP."
- State time complexity from the sort: "O(n log n) from sorting, O(n) for the greedy scan."
- Connect greedy to real algorithms: Huffman coding, Prim's/Kruskal's, Dijkstra's.

## Scoring Rubric (What Interviewers Evaluate)
- **6/10:** Recognizes greedy is applicable. Gets a correct solution after hints. Can't prove it.
- **8/10:** Identifies the greedy choice and sorts correctly (sort by end time for interval scheduling, sort by deadline for EDF). Implements cleanly. Explains why greedy works for this specific problem.
- **10/10:** Distinguishes greedy from DP with the greedy-choice property. Proves correctness via exchange argument. Identifies when greedy appears to work but doesn't. Connects greedy to real algorithms (Huffman, Prim's/Kruskal's, Dijkstra's).

## Interview Practice Questions
1. Find the minimum number of intervals to remove from [[1,2],[2,3],[3,4],[1,3]] to make the rest non-overlapping. (Answer: 1 — remove [1,3])
2. Explain why greedy works for interval scheduling but not for weighted interval scheduling.
3. Can you reach the last index? nums = [2,3,1,1,4] -> Yes. [3,2,1,0,4] -> No.

## Problems in This Tier
- P055: Jump Game
- P455: Assign Cookies
- P134: Gas Station
- P135: Candy
- P452: Minimum Number of Arrows to Burst Balloons
- P502: IPO
- P556: Next Greater Element III
- P564: Find the Closest Palindrome
- P621: Task Scheduler
- P621b: Task Scheduler with Multiple Machines

Source: [Greedy Patterns: Interval Scheduling, Jump Game & Activity Selection (CalibreOS)](https://www.calibreos.com/learn/dsa-greedy-patterns)
