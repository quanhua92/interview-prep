# Greedy Algorithms — Working Checklist

Use this checklist each time you practice a greedy problem.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Identify the Greedy Strategy (1-2 min)
- [ ] Restate the problem: is it asking to maximize/minimize a count, cost, or distance?
- [ ] Identify signal words: "maximum number of", "minimum cost", "earliest deadline", "can you reach", "schedule"
- [ ] Determine if greedy is appropriate:
  - [ ] Does making the locally optimal choice at each step guarantee a globally optimal solution?
  - [ ] Can I prove this with an exchange argument? (If not, consider DP)
  - [ ] Try constructing a counterexample: "can two lower-scoring options ever beat one high-scoring option?" If yes -> not greedy
- [ ] Identify the sorting key: end time, deadline, start time, value, weight ratio?

## Phase 2: Classify the Problem (30 sec)
- [ ] **Interval scheduling:** sort by end time, greedily select non-overlapping -> P452, P435
- [ ] **Activity selection / EDF:** sort by deadline, earliest-deadline-first
- [ ] **Jump game:** forward reach tracking (max_reach) or BFS-like range expansion
- [ ] **Gas station:** total surplus check + reset-on-negative start finding
- [ ] **Task scheduler:** most-frequent-first, formula `(max_freq - 1) * (n + 1) + count_of_max_freq`
- [ ] **Allocation / assignment:** sort both arrays, greedily match -> P455
- [ ] **Other:** identify what "locally best" means for this specific problem

## Phase 3: Implement (5-10 min)
- [ ] Sort the input with the correct key (most common source of bugs)
- [ ] Initialize tracking variables:
  - [ ] For intervals: `last_end = -inf`, `count = 0`
  - [ ] For jump game: `max_reach = 0` or `jumps = current_end = farthest = 0`
  - [ ] For gas station: `total_surplus = current_surplus = start = 0`
  - [ ] For task scheduler: frequency counter, `max_freq`, `max_freq_count`
- [ ] Write the greedy scan loop:
  - [ ] For intervals: `if start >= last_end: select; update last_end`
  - [ ] For jump game: `if i > max_reach: return False; update max_reach`
  - [ ] For gas station: `if current_surplus < 0: reset start`
- [ ] Handle edge cases:
  - [ ] Empty input
  - [ ] Single element
  - [ ] All same values / all zeros
  - [ ] Already sorted / reverse sorted
- [ ] State time and space complexity:
  - [ ] Time: usually O(n log n) from sorting + O(n) scan
  - [ ] Space: usually O(1) or O(n) for the sort

## Phase 4: Prove Correctness (2-3 min)
- [ ] State the greedy choice: "I sort by [X] and always pick the [earliest/latest/highest/lowest]"
- [ ] Give the exchange argument: "If an optimal solution makes a different choice, I can swap in the greedy choice without worsening the result because [reason]"
- [ ] Distinguish from DP: "If this problem had [weights/arbitrary denominations/negative edges], greedy would fail because [counterexample], and I'd need DP"
- [ ] Connect to known algorithms if applicable: Huffman coding, Prim's, Kruskal's, Dijkstra's

## Phase 5: Test and Verify (2-3 min)
- [ ] Trace through the given example step by step
- [ ] Verify against a second test case
- [ ] Check boundary conditions:
  - [ ] Can greedy ever overcount or undercount?
  - [ ] Does the sort key handle ties correctly? (e.g., sort by end time, then start time)
- [ ] Confirm the output format matches what the problem asks (count vs list vs boolean)

## Greedy vs DP Quick Decision Guide
| If the problem... | Use |
|---|---|
| Asks "maximize COUNT of items" (unweighted) | Greedy |
| Asks "maximize VALUE of items" (weighted) | DP |
| Has arbitrary coin denominations | DP |
| Has standard (power-of-each-other) denominations | Greedy |
| Items can be fractionally taken | Greedy |
| Items are all-or-nothing (0/1) | DP |
| Needs to consider ALL subproblems | DP |
| Local choice never blocks a better global choice | Greedy |

## Common Pitfalls
- [ ] Sorting by the wrong key (start time instead of end time for interval scheduling)
- [ ] Using greedy when DP is needed (weighted interval scheduling, 0/1 knapsack, arbitrary coin change)
- [ ] Forgetting to check the tie-breaking condition (start >= last_end vs start > last_end)
- [ ] Not handling the case where greedy produces same count but different items (often fine, but verify)
- [ ] O(n^2) solution when O(n log n) greedy exists

## Practice Notes
- Date: _______  Problem: _______  Score: ___/10  Notes:
- Date: _______  Problem: _______  Score: ___/10  Notes:
- Date: _______  Problem: _______  Score: ___/10  Notes:

Source: [Greedy Patterns: Interval Scheduling, Jump Game & Activity Selection (CalibreOS)](https://www.calibreos.com/learn/dsa-greedy-patterns)
