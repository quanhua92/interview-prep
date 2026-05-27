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

#include "io.h"
#include <stdlib.h>

int canFinish(int numCourses, int (*prereqs)[2], int prereqSize)
{
    int *adjCount = calloc(numCourses, sizeof(int));
    int *inDegree = calloc(numCourses, sizeof(int));
    int *queue = malloc(numCourses * sizeof(int));
    int *edges = malloc(prereqSize * sizeof(int));
    int *head = calloc(numCourses, sizeof(int));
    int front = 0, back = 0, count = 0;

    for (int i = 0; i < prereqSize; i++) {
        inDegree[prereqs[i][0]]++;
    }
    int edgeIdx = 0;
    for (int i = 0; i < numCourses; i++) head[i] = -1;
    for (int i = 0; i < prereqSize; i++) {
        int course = prereqs[i][0];
        int prereq = prereqs[i][1];
        edges[edgeIdx] = course;
        adjCount[edgeIdx] = head[prereq];
        head[prereq] = edgeIdx;
        edgeIdx++;
    }
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) queue[back++] = i;
    }
    while (front < back) {
        int node = queue[front++];
        count++;
        for (int e = head[node]; e != -1; e = adjCount[e]) {
            int nb = edges[e];
            if (--inDegree[nb] == 0) queue[back++] = nb;
        }
    }
    free(adjCount);
    free(inDegree);
    free(queue);
    free(edges);
    free(head);
    return count == numCourses;
}

int main(void)
{
    int n;
    int *header = read_ints(&n);
    int numCourses = header[0];
    int pairCount = header[1];
    free(header);

    int (*prereqs)[2] = NULL;
    if (pairCount > 0) {
        prereqs = malloc(pairCount * sizeof(int[2]));
        for (int i = 0; i < pairCount; i++) {
            int k;
            int *pair = read_ints(&k);
            prereqs[i][0] = pair[0];
            prereqs[i][1] = pair[1];
            free(pair);
        }
    }

    write_bool(canFinish(numCourses, prereqs, pairCount));
    free(prereqs);
    return 0;
}
