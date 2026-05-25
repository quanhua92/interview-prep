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


use std::collections::VecDeque;

fn can_finish(num_courses: usize, prerequisites: &[(i32, i32)]) -> bool {
    let mut adj: Vec<Vec<usize>> = vec![vec![]; num_courses];
    let mut in_degree: Vec<i32> = vec![0; num_courses];
    for &(course, prereq) in prerequisites {
        let c = course as usize;
        let p = prereq as usize;
        adj[p].push(c);
        in_degree[c] += 1;
    }
    let mut queue: VecDeque<usize> = VecDeque::new();
    for i in 0..num_courses {
        if in_degree[i] == 0 {
            queue.push_back(i);
        }
    }
    let mut count = 0;
    while let Some(node) = queue.pop_front() {
        count += 1;
        for &nb in &adj[node] {
            in_degree[nb] -= 1;
            if in_degree[nb] == 0 {
                queue.push_back(nb);
            }
        }
    }
    count == num_courses
}

struct TC {
    label: &'static str,
    num_courses: usize,
    prereqs: &'static [(i32, i32)],
    expected: bool,
}

fn main() {
    let tests: &[TC] = &[
        TC { label: "example 1", num_courses: 2, prereqs: &[(1,0)], expected: true },
        TC { label: "example 2", num_courses: 2, prereqs: &[(1,0),(0,1)], expected: false },
        TC { label: "no prerequisites", num_courses: 1, prereqs: &[], expected: true },
        TC { label: "3-node cycle", num_courses: 3, prereqs: &[(0,1),(1,2),(2,0)], expected: false },
        TC { label: "linear chain disconnected node", num_courses: 5, prereqs: &[(0,1),(1,2),(2,3)], expected: true },
        TC { label: "two deps on one course", num_courses: 3, prereqs: &[(1,0),(2,0)], expected: true },
        TC { label: "self-contained cycle", num_courses: 4, prereqs: &[(0,1),(1,2),(2,3),(3,1)], expected: false },
    ];

    println!("\n============================================================");
    println!("  207. Course Schedule");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = can_finish(tc.num_courses, tc.prereqs);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
