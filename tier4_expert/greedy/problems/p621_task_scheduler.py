"""
P621: Task Scheduler (Medium)
https://leetcode.com/problems/task-scheduler/
Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting

Given tasks and cooldown n, return minimum CPU intervals.

Constraints:
    - 1 <= tasks.length <= 104
    - tasks[i] is an uppercase English letter.
    - 0 <= n <= 100

Hint: Formula: max((maxFreq - 1) * (n + 1) + countMaxFreq, len(tasks)).
"""

from src.wasm_libs.py.io import *


def solve(tasks: list[str], n: int) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    task_line = read_line()
    tasks = task_line.split() if task_line else []
    n = read_int()
    result = solve(tasks, n)
    write_int(result)
