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
 * Template (python3):
 *     class Solution:
 *         def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
 * 
 * Hint: Build a graph and use topological sort (Kahn's algorithm) to detect cycles.
 */
function solve(numCourses, prerequisites)
  const graph = {};
  for (let i = 0; i < numCourses; i++) graph[i] = [];
  const inDegree = new Array(numCourses).fill(0);
  for (const [course, prereq] of prerequisites)
    graph[prereq].push(course);
    inDegree[course]++;
  }
  const queue = [];
  for (let i = 0; i < numCourses; i++)
    if (inDegree[i] === 0) queue.push(i);
  }
  let count = 0;
  while (queue.length > 0)
    const node = queue.shift();
    count++;
    for (const neighbor of graph[node])
      inDegree[neighbor]--;
      if (inDegree[neighbor] === 0) queue.push(neighbor);
    }
  }
  return count === numCourses; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [2, [[1, 0]]], expected: true },
  { label: "example 2", input: [2, [[1, 0], [0, 1]]], expected: false },
  { label: "no prerequisites", input: [1, []], expected: true },
  { label: "3-node cycle", input: [3, [[0, 1], [1, 2], [2, 0]]], expected: false },
  { label: "linear chain disconnected node", input: [5, [[0, 1], [1, 2], [2, 3]]], expected: true },
  { label: "two deps on one course", input: [3, [[1, 0], [2, 0]]], expected: true },
  { label: "self-contained cycle", input: [4, [[0, 1], [1, 2], [2, 3], [3, 1]]], expected: false },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
