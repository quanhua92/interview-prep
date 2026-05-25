/*
 * P447: Number of Boomerangs [PREMIUM] (Medium)
 * https://leetcode.com/problems/number-of-boomerangs/
 * Topics: Array, Hash Table, Math
 * 
 * You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
 * Return the number of boomerangs.
 * Example 1:
 *     Input: points = [[0,0],[1,0],[2,0]]
 *     Output: 2
 *     Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
 * 
 * Example 2:
 *     Input: points = [[1,1],[2,2],[3,3]]
 *     Output: 2
 * 
 * Example 3:
 *     Input: points = [[1,1]]
 *     Output: 0
 * 
 * Constraints:
 *     - n == points.length
 *     - 1 <= n <= 500
 *     - points[i].length == 2
 *     - -104 <= xi, yi <= 104
 *     - All the points are unique.
 * 
 * Template (python3):
 *     class Solution:
 *         def numberOfBoomerangs(self, points: List[List[int]]) -> int:
 */
use std::collections::HashMap;

fn number_of_boomerangs(points: &[(i32, i32)]) -> i32 {
    todo!()
}

fn main() {
    struct Case<'a> { label: &'a str, points: &'a [(i32, i32)], expected: i32 }
    let tests: &[Case] = &[
        Case { label: "example 1", points: &[(0,0),(1,0),(2,0)], expected: 2 },
        Case { label: "example 2", points: &[(1,1),(2,2),(3,3)], expected: 2 },
        Case { label: "example 3", points: &[(1,1)], expected: 0 },
        Case { label: "only 2 points", points: &[(0,0),(1,0)], expected: 0 },
        Case { label: "square 4 points", points: &[(0,0),(0,1),(1,0),(1,1)], expected: 8 },
        Case { label: "isoceles triangle", points: &[(0,0),(1,1),(1,-1)], expected: 2 },
        Case { label: "isoceles different heights", points: &[(0,0),(3,4),(3,-4)], expected: 2 },
    ];

    println!("\n============================================================");
    println!("  447. Number of Boomerangs");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = number_of_boomerangs(tc.points);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}\n    Got:      {}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
