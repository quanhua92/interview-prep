"""
P207: Course Schedule (Medium)
https://leetcode.com/problems/course-schedule/
Topics: Depth-First Search, Breadth-First Search, Graph, Topological Sort

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
Return true if you can finish all courses. Otherwise, return false.

Example 1:
    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: true
    Explanation: There are a total of 2 courses to take.
    To take course 1 you should have finished course 0. So it is possible.

Example 2:
    Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
    Output: false
    Explanation: There are a total of 2 courses to take.
    To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Constraints:
    - 1 <= numCourses <= 2000
    - 0 <= prerequisites.length <= 5000
    - prerequisites[i].length == 2
    - 0 <= ai, bi < numCourses
    - All the pairs prerequisites[i] are unique.

Hints:
    - This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    - <a href="https://www.cs.princeton.edu/~wayne/kleinberg-tardos/pdf/03Graphs.pdf" target="_blank">Topological Sort via DFS</a> - A great tutorial explaining the basic concepts of Topological Sort.
    - Topological sort could also be done via <a href="http://en.wikipedia.org/wiki/Topological_sorting#Algorithms" target="_blank">BFS</a>.

Template (python3):
    class Solution:
        def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:

Hint: Build a graph and use topological sort (Kahn's algorithm) to detect cycles.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "207. Course Schedule"
    test_cases = [
        TestCase(input=(2, [[1, 0]]), expected=True, label="example 1"),
        TestCase(input=(2, [[1, 0], [0, 1]]), expected=False, label="example 2"),
        TestCase(input=(1, []), expected=True, label="no prerequisites"),
        TestCase(input=(3, [[0, 1], [1, 2], [2, 0]]), expected=False, label="3-node cycle"),
        TestCase(input=(5, [[0, 1], [1, 2], [2, 3]]), expected=True, label="linear chain disconnected node"),
        TestCase(input=(3, [[1, 0], [2, 0]]), expected=True, label="two deps on one course"),
        TestCase(input=(4, [[0, 1], [1, 2], [2, 3], [3, 1]]), expected=False, label="self-contained cycle"),
    ]

    def solve(self, num_courses: int, prerequisites: list[list[int]]) -> bool:
        raise NotImplementedError(
            "TODO: Implement solve(self, num_courses: int, prerequisites: list[list[int]]) -> bool"
        )


if __name__ == "__main__":
    Solution().run()
