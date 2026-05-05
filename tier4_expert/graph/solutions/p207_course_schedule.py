"""P207: Course Schedule (Medium)

TODO: Implement solve() below.
Hint: Build a graph and use topological sort (Kahn's algorithm) to detect cycles.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import deque

class Solution(Problem):
    name = "207. Course Schedule"
    test_cases = [
        TestCase(input=(2, [[1,0]]), expected=True, label="example 1"),
        TestCase(input=(2, [[1,0],[0,1]]), expected=False, label="example 2"),
        TestCase(input=(1, []), expected=True, label="no prerequisites"),
    ]

    def solve(self, num_courses: int, prerequisites: list[list[int]]) -> bool:
        graph: dict[int, list[int]] = {i: [] for i in range(num_courses)}
        in_degree = [0] * num_courses
        for course, prereq in prerequisites:
            graph[prereq].append(course)
            in_degree[course] += 1
        queue = deque(i for i in range(num_courses) if in_degree[i] == 0)
        count = 0
        while queue:
            node = queue.popleft()
            count += 1
            for neighbor in graph[node]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
        return count == num_courses

if __name__ == "__main__":
    Solution().run()
