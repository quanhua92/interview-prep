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
 *     So one correct course order is [0,1,2,3]. Another valid ordering is [0,2,1,3].
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

#include "io.h"
#include <stdlib.h>
#include <string.h>

int *findOrder(int numCourses, int (*prereqs)[2], int prereqSize, int *returnSize)
{
    int *inDegree = calloc(numCourses, sizeof(int));
    int *queue = malloc(numCourses * sizeof(int));
    int *order = malloc(numCourses * sizeof(int));
    int *adj_count = calloc(numCourses, sizeof(int));
    int *adj_list = malloc(prereqSize * sizeof(int));

    for (int i = 0; i < prereqSize; i++) {
        inDegree[prereqs[i][0]]++;
        adj_count[prereqs[i][1]]++;
    }
    int offset = 0;
    int *adj_offset = malloc(numCourses * sizeof(int));
    for (int i = 0; i < numCourses; i++) {
        adj_offset[i] = offset;
        offset += adj_count[i];
    }
    int *adj_pos = malloc(numCourses * sizeof(int));
    memcpy(adj_pos, adj_offset, numCourses * sizeof(int));
    for (int i = 0; i < prereqSize; i++) {
        adj_list[adj_pos[prereqs[i][1]]++] = prereqs[i][0];
    }

    int front = 0, back = 0, count = 0;
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) queue[back++] = i;
    }
    while (front < back) {
        int node = queue[front++];
        order[count++] = node;
        for (int e = adj_offset[node]; e < adj_offset[node] + adj_count[node]; e++) {
            if (--inDegree[adj_list[e]] == 0) queue[back++] = adj_list[e];
        }
    }

    free(inDegree);
    free(queue);
    free(adj_count);
    free(adj_list);
    free(adj_offset);
    free(adj_pos);

    if (count == numCourses) {
        *returnSize = numCourses;
        return order;
    }
    free(order);
    *returnSize = 0;
    return NULL;
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

    int returnSize;
    int *order = findOrder(numCourses, prereqs, pairCount, &returnSize);
    write_ints(order, returnSize);
    free(order);
    free(prereqs);
    return 0;
}
