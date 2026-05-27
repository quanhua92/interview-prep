/**
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
 * Hint: Build a graph and use topological sort (Kahn's algorithm) to detect cycles.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(numCourses, prerequisites) {
  const graph = {};
  for (let i = 0; i < numCourses; i++) graph[i] = [];
  const inDegree = new Array(numCourses).fill(0);
  for (const [course, prereq] of prerequisites) {
    graph[prereq].push(course);
    inDegree[course]++;
  }
  const queue = [];
  for (let i = 0; i < numCourses; i++) {
    if (inDegree[i] === 0) queue.push(i);
  }
  let count = 0;
  while (queue.length > 0) {
    const node = queue.shift();
    count++;
    for (const neighbor of graph[node]) {
      inDegree[neighbor]--;
      if (inDegree[neighbor] === 0) queue.push(neighbor);
    }
  }
  return count === numCourses;
}

const header = readInts();
const numCourses = header[0];
const pairCount = header[1];
const prerequisites = [];
for (let i = 0; i < pairCount; i++) {
  prerequisites.push(readInts());
}
writeBool(solve(numCourses, prerequisites));
