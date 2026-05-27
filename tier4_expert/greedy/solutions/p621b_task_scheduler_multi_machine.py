"""
P621b: Task Scheduler with Multiple Machines (Hard)
Extension of LeetCode 621 - Task Scheduler
https://leetcode.com/problems/task-scheduler/

Topics: Array, Hash Table, Greedy, Counting

You are given an array of CPU tasks, each labeled with a letter from A to Z,
a cooldown period n, and m identical parallel machines.

Each machine can execute at most one task per time interval. Tasks can be
completed in any order across the machines. Cooldown is tracked per-machine:
if machine M runs task A at time t, that machine M cannot run task A again
until time t + n + 1. Other machines are unaffected and may run task A at
any time (including simultaneously with M).

Return the minimum number of time intervals required to complete all tasks
across all m machines.

Example 1:
    Input: tasks = ["A","A","A","B","B","B"], n = 2, m = 1
    Output: 8
    Explanation: This is the original LeetCode 621 problem.
    A -> B -> idle -> A -> B -> idle -> A -> B

Example 2:
    Input: tasks = ["A","A","A","B","B","B"], n = 2, m = 2
    Output: 4
    Explanation: Cooldown is per-machine, so machines can swap tasks.
    t=0: M1=A, M2=B | t=1: M1=B, M2=A | t=2: idle | t=3: M1=A, M2=B
    At t=1, M1 can run B (M1 never ran B) and M2 can run A (M2 never ran A).

Example 3:
    Input: tasks = ["A","C","A","B","D","B"], n = 1, m = 2
    Output: 3
    Explanation: Each task appears at most twice. With 2 machines:
    t=0: M1=A, M2=B | t=1: M1=C, M2=D | t=2: M1=A, M2=B | Done in 3.

Example 4:
    Input: tasks = ["A","A","A","B","B","B"], n = 3, m = 2
    Output: 5
    Explanation: Machines swap tasks at t=1, then wait for cooldown.
    t=0: M1=A, M2=B | t=1: M1=B, M2=A | t=2-3: idle | t=4: M1=A, M2=B

Example 5:
    Input: tasks = ["A"], n = 5, m = 3
    Output: 1
    Explanation: Only one task, completed in a single interval regardless of
    cooldown or number of machines.

Constraints:
    - 1 <= tasks.length <= 10^4
    - tasks[i] is an uppercase English letter.
    - 0 <= n <= 100
    - 1 <= m <= 26

Template (python3):
    class Solution:
        def leastInterval(self, tasks: List[str], n: int, m: int) -> int:

Hint: At each time step, greedily assign the highest-frequency remaining task
to each machine, respecting that machine's per-task cooldown. When no machine
can run any remaining task, jump directly to the next cooldown expiry.
"""

from collections import Counter

from src.wasm_libs.py.io import *


def solve(tasks: list[str], n: int, m: int) -> int:
    freq = Counter(tasks)
    cooldown = [dict() for _ in range(m)]

    time = 0
    remaining = len(tasks)

    while remaining > 0:
        assigned = False
        for i in range(m):
            best_task, best_count = None, 0
            for task, count in freq.items():
                if count > best_count and cooldown[i].get(task, 0) <= time:
                    best_task, best_count = task, count
            if best_task:
                freq[best_task] -= 1
                cooldown[i][best_task] = time + n + 1
                remaining -= 1
                assigned = True

        if assigned:
            time += 1
        else:
            next_time = min(
                t for mc in cooldown for t in mc.values() if t > time
            )
            time = next_time

    return time


if __name__ == "__main__":
    task_line = read_line()
    tasks = task_line.split() if task_line else []
    n = read_int()
    m = read_int()
    result = solve(tasks, n, m)
    write_int(result)
