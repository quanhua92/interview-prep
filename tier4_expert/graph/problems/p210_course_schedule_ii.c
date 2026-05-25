/*
 * P210: Course Schedule II (Medium)
 * https://leetcode.com/problems/course-schedule-ii/
 * Topics: Depth-First Search, Breadth-First Search, Graph, Topological Sort
 * 
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
 * Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.
 * 
 * Example 1:
 *     Input: numCourses = 2, prerequisites = [[1,0]]
 *     Output: [0,1]
 *     Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
 * 
 * Example 2:
 *     Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
 *     Output: [0,2,1,3]
 *     Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
 *     So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
 * 
 * Example 3:
 *     Input: numCourses = 1, prerequisites = []
 *     Output: [0]
 * 
 * Constraints:
 *     - 1 <= numCourses <= 2000
 *     - 0 <= prerequisites.length <= numCourses * (numCourses - 1)
 *     - prerequisites[i].length == 2
 *     - 0 <= ai, bi < numCourses
 *     - ai != bi
 *     - All the pairs [ai, bi] are distinct.
 * 
 * Hints:
 *     - This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
 *     - <a href="https://www.youtube.com/watch?v=ozso3xxkVGU" target="_blank">Topological Sort via DFS</a> - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
 *     - Topological sort could also be done via <a href="http://en.wikipedia.org/wiki/Topological_sorting#Algorithms" target="_blank">BFS</a>.
 * 
 * Template (python3):
 *     class Solution:
 *         def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
 * 
 * Hint: Use Kahn's algorithm (topological sort with BFS) to produce a valid course order.
 */
#include "ctest.h"

static int *findOrder(int numCourses, int prerequisites[][2], int prereqSize, int *returnSize);
__attribute__((unused)) static void _u(void) {
    abort();
}

static int *findOrder(int numCourses, int prerequisites[][2], int prereqSize, int *returnSize) {
    abort();
}

typedef struct {
    const char *label;
    int numCourses;
    int prereqs[10000][2];
    int prereqSize;
    int expected[2000];
    int expected_n;
} TC;

static int is_valid_order(int *order, int n, int prereqs[][2], int prereqSize) {
    abort();
}

int main(void) {
    TC tests[] = {
        {"example 1", 2, {{1,0}}, 1, {0,1}, 2},
        {"example 2", 4, {{1,0},{2,0},{3,1},{3,2}}, 4, {0,1,2,3}, 4},
        {"no prerequisites", 1, {{0}}, 0, {0}, 1},
        {"cycle returns empty", 2, {{1,0},{0,1}}, 2, {0}, 0},
        {"3-node cycle", 3, {{0,1},{1,2},{2,0}}, 3, {0}, 0},
        {"all depend on course 0", 4, {{0,1},{0,2},{0,3}}, 3, {1,2,3,0}, 4},
        {"linear chain", 3, {{2,1},{1,0}}, 2, {0,1,2}, 3},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        int got_n = 0;
        int *got = findOrder(tests[i].numCourses, tests[i].prereqs, tests[i].prereqSize, &got_n);
        int ok;
        if (tests[i].expected_n == 0) {
            ok = (got_n == 0);
        } else {
            ok = (got_n == tests[i].expected_n) && is_valid_order(got, got_n, tests[i].prereqs, tests[i].prereqSize);
        }
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: ");
            th_print_arr(tests[i].expected, tests[i].expected_n);
            printf("\n    Got:      ");
            if (got) th_print_arr(got, got_n);
            else printf("NULL");
            printf("\n");
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
