"""
P621: Task Scheduler (Medium)
https://leetcode.com/problems/task-scheduler/
Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting

You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n.
Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in any order, but there's a constraint: there has to be a gap of at least n intervals between two tasks with the same label.
Return the minimum number of CPU intervals required to complete all tasks.

Example 1:
    Input: tasks = ["A","A","A","B","B","B"], n = 2
    Output: 8
    Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.
    After completing task A, you must wait two intervals before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle.

Example 2:
    Input: tasks = ["A","C","A","B","D","B"], n = 1
    Output: 6
    Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.

Example 3:
    Input: tasks = ["A","A","A", "B","B","B"], n = 3
    Output: 10
    Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.

Constraints:
    - 1 <= tasks.length <= 104
    - tasks[i] is an uppercase English letter.
    - 0 <= n <= 100

Template (python3):
    class Solution:
        def leastInterval(self, tasks: List[str], n: int) -> int:

Hint: The idle slots are determined by the most frequent task. Formula: max((maxFreq - 1) * (n + 1) + countMaxFreq, len(tasks)).
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import Counter


class Solution(Problem):
    name = "621. Task Scheduler"
    test_cases = [
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 2), expected=8, label="example 1"
        ),
        TestCase(
            input=(["A", "C", "A", "B", "D", "B"], 1), expected=6, label="example 2"
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 3), expected=10, label="example 3"
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B", "C", "C", "D"], 2),
            expected=9,
            label="tasks fill all idle slots",
        ),
        TestCase(input=(["A", "A"], 2), expected=4, label="single task type with long cooldown"),
        TestCase(input=(["A", "A", "B", "B"], 0), expected=4, label="no cooldown"),
        TestCase(input=(["A"], 5), expected=1, label="single task"),
        TestCase(input=(["A", "A", "A", "A"], 2), expected=10, label="all same task"),
        TestCase(input=(["A", "B", "C"], 100), expected=3, label="unique tasks large n"),
    ]

    def solve(self, tasks: list[str], n: int) -> int:
        freq = Counter(tasks)
        max_freq = max(freq.values())
        max_count = sum(1 for v in freq.values() if v == max_freq)
        return max(len(tasks), (max_freq - 1) * (n + 1) + max_count)


if __name__ == "__main__":
    Solution().run()
