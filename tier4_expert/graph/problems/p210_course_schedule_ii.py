"""
P210: Course Schedule II (Medium)
https://leetcode.com/problems/course-schedule-ii/
Topics: Depth-First Search, Breadth-First Search, Graph, Topological Sort

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

Example 1:
    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: [0,1]
    Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].

Example 2:
    Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
    Output: [0,2,1,3]
    Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
    So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

Example 3:
    Input: numCourses = 1, prerequisites = []
    Output: [0]

Constraints:
    - 1 <= numCourses <= 2000
    - 0 <= prerequisites.length <= numCourses * (numCourses - 1)
    - prerequisites[i].length == 2
    - 0 <= ai, bi < numCourses
    - ai != bi
    - All the pairs [ai, bi] are distinct.

Hints:
    - This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    - <a href="https://www.youtube.com/watch?v=ozso3xxkVGU" target="_blank">Topological Sort via DFS</a> - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
    - Topological sort could also be done via <a href="http://en.wikipedia.org/wiki/Topological_sorting#Algorithms" target="_blank">BFS</a>.

Template (python3):
    class Solution:
        def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:

Hint: Use Kahn's algorithm (topological sort with BFS) to produce a valid course order.
"""

from src.wasm_libs.py.io import *


def solve(num_courses: int, prerequisites: list[list[int]]) -> list[int]:
    raise NotImplementedError


if __name__ == "__main__":
    header = read_ints()
    num_courses, pair_count = header[0], header[1]
    prerequisites = [read_ints() for _ in range(pair_count)]
    result = solve(num_courses, prerequisites)
    write_ints(result)
