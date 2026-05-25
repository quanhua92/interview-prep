/*
 * P407: Trapping Rain Water II [PREMIUM] (Hard)
 * https://leetcode.com/problems/trapping-rain-water-ii/
 * Topics: Array, Breadth-First Search, Heap (Priority Queue), Matrix
 * 
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
 * Example 1:
 *     Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
 *     Output: 4
 *     Explanation: After the rain, water is trapped between the blocks.
 *     We have two small ponds 1 and 3 units trapped.
 *     The total volume of water trapped is 4.
 * 
 * Example 2:
 *     Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
 *     Output: 10
 * 
 * Constraints:
 *     - m == heightMap.length
 *     - n == heightMap[i].length
 *     - 1 <= m, n <= 200
 *     - 0 <= heightMap[i][j] <= 2 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def trapRainWater(self, heightMap: List[List[int]]) -> int:
 */
use std::cmp::Reverse;
use std::collections::BinaryHeap;

fn trap_rain_water(height_map: &[Vec<i32>]) -> i32 {
    todo!()
}

fn to_2d(flat: &[i32], _m: usize, n: usize) -> Vec<Vec<i32>> {
    todo!()
}

fn main() {
    struct Case { label: &'static str, flat: &'static [i32], m: usize, n: usize, expected: i32 }
    let tests: &[Case] = &[
        Case { label: "example 1", flat: &[1,4,3,1,3,2, 3,2,1,3,2,4, 2,3,3,2,3,1], m: 3, n: 6, expected: 4 },
        Case { label: "example 2", flat: &[3,3,3,3,3, 3,2,2,2,3, 3,2,1,2,3, 3,2,2,2,3, 3,3,3,3,3], m: 5, n: 5, expected: 10 },
        Case { label: "1x1 no trap", flat: &[1], m: 1, n: 1, expected: 0 },
        Case { label: "3x3 basin", flat: &[5,5,5, 5,1,5, 5,5,5], m: 3, n: 3, expected: 4 },
        Case { label: "2x4 no interior", flat: &[5,5,5,5, 5,5,5,5], m: 2, n: 4, expected: 0 },
    ];

    println!("\n============================================================");
    println!("  407. Trapping Rain Water II");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let hm = to_2d(tc.flat, tc.m, tc.n);
        let got = trap_rain_water(&hm);
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
