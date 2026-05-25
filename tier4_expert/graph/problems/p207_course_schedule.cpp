/*
 * P207: Course Schedule (Medium)
 * https://leetcode.com/problems/course-schedule/
 * Topics: Depth-First Search, Breadth-First Search, Graph, Topological Sort
 * 
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
 * Return true if you can finish all courses. Otherwise, return false.
 * 
 * Example 1:
 *     Input: numCourses = 2, prerequisites = [[1,0]]
 *     Output: true
 *     Explanation: There are a total of 2 courses to take.
 *     To take course 1 you should have finished course 0. So it is possible.
 * 
 * Example 2:
 *     Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
 *     Output: false
 *     Explanation: There are a total of 2 courses to take.
 *     To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
 * 
 * Constraints:
 *     - 1 <= numCourses <= 2000
 *     - 0 <= prerequisites.length <= 5000
 *     - prerequisites[i].length == 2
 *     - 0 <= ai, bi < numCourses
 *     - All the pairs prerequisites[i] are unique.
 * 
 * Hints:
 *     - This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
 *     - <a href="https://www.cs.princeton.edu/~wayne/kleinberg-tardos/pdf/03Graphs.pdf" target="_blank">Topological Sort via DFS</a> - A great tutorial explaining the basic concepts of Topological Sort.
 *     - Topological sort could also be done via <a href="http://en.wikipedia.org/wiki/Topological_sorting#Algorithms" target="_blank">BFS</a>.
 * 
 * Template (python3):
 *     class Solution:
 *         def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
 * 
 * Hint: Build a graph and use topological sort (Kahn's algorithm) to detect cycles.
 */
#include "cpptest.h"

static bool canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites) {
    abort();
}

struct TC {
    const char *label;
    int numCourses;
    std::vector<std::vector<int>> prereqs;
    bool expected;
};

int main(void) {
    (void)print_arr;
    TC tests[] = {
        {"example 1", 2, {{1,0}}, true},
        {"example 2", 2, {{1,0},{0,1}}, false},
        {"no prerequisites", 1, {}, true},
        {"3-node cycle", 3, {{0,1},{1,2},{2,0}}, false},
        {"linear chain disconnected node", 5, {{0,1},{1,2},{2,3}}, true},
        {"two deps on one course", 3, {{1,0},{2,0}}, true},
        {"self-contained cycle", 4, {{0,1},{1,2},{2,3},{3,1}}, false},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        bool got = canFinish(tests[i].numCourses, tests[i].prereqs);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
