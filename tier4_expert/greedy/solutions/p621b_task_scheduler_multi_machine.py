"""
P621b: Task Scheduler with Multiple Machines (Hard)
Extension of LeetCode 621 - Task Scheduler
https://leetcode.com/problems/task-scheduler/

Topics: Array, Hash Table, Greedy, Heap (Priority Queue), Counting

You are given an array of CPU tasks, each labeled with a letter from A to Z,
a cooldown period n, and m identical parallel machines.

Each machine can execute at most one task per time interval. Tasks can be
completed in any order across the machines, but there is a global cooldown
constraint: the same task label cannot run on ANY machine within n intervals
of its last execution on any machine. In other words, if task A runs at
time t on any machine, no machine can execute task A until time t + n + 1.

Return the minimum number of time intervals required to complete all tasks
across all m machines.

Example 1:
    Input: tasks = ["A","A","A","B","B","B"], n = 2, m = 1
    Output: 8
    Explanation: This is the original LeetCode 621 problem.
    A -> B -> idle -> A -> B -> idle -> A -> B

Example 2:
    Input: tasks = ["A","A","A","B","B","B"], n = 2, m = 2
    Output: 7
    Explanation: With 2 machines, both A and B can run in parallel.
    t=0: M1=A, M2=B | t=1: idle | t=2: idle
    t=3: M1=A, M2=B | t=4: idle | t=5: idle
    t=6: M1=A, M2=B | Done in 7 intervals.

Example 3:
    Input: tasks = ["A","C","A","B","D","B"], n = 1, m = 2
    Output: 3
    Explanation: Each task appears at most twice. With 2 machines:
    t=0: M1=A, M2=B | t=1: M1=C, M2=D | t=2: M1=A, M2=B | Done in 3.

Example 4:
    Input: tasks = ["A","A","A","B","B","B"], n = 3, m = 2
    Output: 9
    Explanation: With n=3, after running A and B at t=0, both are blocked
    until t=4. t=0: A,B | t=1-3: idle | t=4: A,B | t=5-7: idle | t=8: A,B.

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

Hint: Use a max-heap to always pick the most frequent available tasks.
At each time step, schedule up to m tasks. Track cooldown with a separate
min-heap keyed by availability time. When no tasks are available, jump
directly to the next cooldown expiry (avoid simulating idle ticks).
"""

import heapq
import sys
from collections import Counter

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "621b. Task Scheduler with Multiple Machines"
    test_cases = [
        # ── Backwards compatibility: m=1 matches LeetCode 621 ──
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 2, 1),
            expected=8,
            label="LC621 ex1 m=1",
        ),
        TestCase(
            input=(["A", "C", "A", "B", "D", "B"], 1, 1),
            expected=6,
            label="LC621 ex2 m=1",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 3, 1),
            expected=10,
            label="LC621 ex3 m=1",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B", "C", "C", "D"], 2, 1),
            expected=9,
            label="fill idle slots m=1",
        ),
        TestCase(
            input=(["A", "A"], 2, 1),
            expected=4,
            label="single task type m=1",
        ),
        # ── m > 1: parallel speedup ──
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 2, 2),
            expected=7,
            label="basic parallelism m=2",
        ),
        TestCase(
            input=(["A", "C", "A", "B", "D", "B"], 1, 2),
            expected=3,
            label="unique tasks m=2",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 3, 2),
            expected=9,
            label="large cooldown m=2",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 2, 10),
            expected=7,
            label="very many machines m=10",
        ),
        # ── Edge cases ──
        TestCase(
            input=(["A"], 5, 1),
            expected=1,
            label="single task n=5 m=1",
        ),
        TestCase(
            input=(["A"], 5, 3),
            expected=1,
            label="single task n=5 m=3",
        ),
        TestCase(
            input=(["A", "B", "C"], 0, 5),
            expected=1,
            label="more machines than tasks n=0",
        ),
        TestCase(
            input=(["A", "A", "A", "A"], 0, 2),
            expected=4,
            label="n=0 same task m=2 (cooldown is per-label)",
        ),
        TestCase(
            input=(["A", "B", "C", "D"], 1, 3),
            expected=2,
            label="m=3 n=1 four unique tasks",
        ),
    ]

    def solve(self, tasks: list[str], n: int, m: int) -> int:
        freq = Counter(tasks)
        max_heap = [(-count, task) for task, count in freq.items()]
        heapq.heapify(max_heap)

        cooldown_queue: list[tuple[int, int, str]] = []
        time_elapsed = 0
        completed = 0
        total = len(tasks)

        while completed < total:
            while cooldown_queue and cooldown_queue[0][0] <= time_elapsed:
                _, neg_count, task = heapq.heappop(cooldown_queue)
                heapq.heappush(max_heap, (neg_count, task))

            scheduled = []
            for _ in range(m):
                if not max_heap:
                    break
                neg_count, task = heapq.heappop(max_heap)
                scheduled.append((-neg_count, task))

            if scheduled:
                for count, task in scheduled:
                    completed += 1
                    if count - 1 > 0:
                        heapq.heappush(
                            cooldown_queue,
                            (time_elapsed + n + 1, -(count - 1), task),
                        )
                time_elapsed += 1
            elif cooldown_queue:
                time_elapsed = cooldown_queue[0][0]
            else:
                break

        return time_elapsed


if __name__ == "__main__":
    Solution().run()
