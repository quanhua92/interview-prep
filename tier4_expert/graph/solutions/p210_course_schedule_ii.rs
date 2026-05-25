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


use std::collections::VecDeque;

fn find_order(num_courses: usize, prerequisites: &[(i32, i32)]) -> Vec<i32> {
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
    let mut order: Vec<i32> = Vec::new();
    while let Some(node) = queue.pop_front() {
        order.push(node as i32);
        for &nb in &adj[node] {
            in_degree[nb] -= 1;
            if in_degree[nb] == 0 {
                queue.push_back(nb);
            }
        }
    }
    if order.len() == num_courses { order } else { vec![] }
}

struct TC {
    label: &'static str,
    num_courses: usize,
    prereqs: &'static [(i32, i32)],
    expected: &'static [i32],
}

fn main() {
    let tests: &[TC] = &[
        TC { label: "example 1", num_courses: 2, prereqs: &[(1,0)], expected: &[0,1] },
        TC { label: "example 2", num_courses: 4, prereqs: &[(1,0),(2,0),(3,1),(3,2)], expected: &[0,1,2,3] },
        TC { label: "no prerequisites", num_courses: 1, prereqs: &[], expected: &[0] },
        TC { label: "cycle returns empty", num_courses: 2, prereqs: &[(1,0),(0,1)], expected: &[] },
        TC { label: "3-node cycle", num_courses: 3, prereqs: &[(0,1),(1,2),(2,0)], expected: &[] },
        TC { label: "all depend on course 0", num_courses: 4, prereqs: &[(0,1),(0,2),(0,3)], expected: &[1,2,3,0] },
        TC { label: "linear chain", num_courses: 3, prereqs: &[(2,1),(1,0)], expected: &[0,1,2] },
    ];

    println!("\n============================================================");
    println!("  210. Course Schedule II");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_order(tc.num_courses, tc.prereqs);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", tc.expected);
            println!("    Got:      {:?}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
