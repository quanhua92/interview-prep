"""P210: Course Schedule II (Medium)

TODO: Implement solve() below.
Hint: Use Kahn's algorithm (topological sort with BFS) to produce a valid course order.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import deque

class Solution(Problem):
    name = "210. Course Schedule II"
    test_cases = [
        TestCase(input=(2, [[1,0]]), expected=[0,1], label="example 1"),
        TestCase(input=(4, [[1,0],[2,0],[3,1],[3,2]]), expected=[0,1,2,3], label="example 2"),
        TestCase(input=(1, []), expected=[0], label="no prerequisites"),
    ]

    def solve(self, num_courses: int, prerequisites: list[list[int]]) -> list[int]:
        graph: dict[int, list[int]] = {i: [] for i in range(num_courses)}
        in_degree = [0] * num_courses
        for course, prereq in prerequisites:
            graph[prereq].append(course)
            in_degree[course] += 1

        queue = deque(i for i in range(num_courses) if in_degree[i] == 0)
        order: list[int] = []
        while queue:
            node = queue.popleft()
            order.append(node)
            for neighbor in graph[node]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)

        return order if len(order) == num_courses else []

if __name__ == "__main__":
    Solution().run()
