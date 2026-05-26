# Greedy

## Core Idea
Make the locally optimal choice at each step, hoping it leads to a globally optimal solution. Greedy algorithms work when the problem has the "greedy-choice property" (a locally optimal choice leads to a globally optimal solution) and "optimal substructure".

## When to Recognize
- "Minimum/maximum number of ..."
- "Jump game" / "can reach the end"
- "Interval scheduling" / "meeting rooms"
- "Assign cookies" / "allocation problems"
- "Gas station"
- "Fractional knapsack"

## Complexity
- **Time:** Usually O(n log n) (often due to sorting) or O(n)
- **Space:** O(1) or O(n) depending on the problem

## Key Variants
1. **Jump game** — track the farthest reachable position
2. **Activity selection / interval scheduling** — sort by end time, greedily select
3. **Gas station** — track surplus/deficit to find the starting point

## Problems
- P055: Jump Game
- P455: Assign Cookies
- P134: Gas Station
- P135: Candy
- P452: Minimum Number of Arrows to Burst Balloons
- P502: IPO
- P621: Task Scheduler
- P621b: Task Scheduler with Multiple Machines
