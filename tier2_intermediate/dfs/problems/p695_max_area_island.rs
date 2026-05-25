/*
 * P695: Max Area of Island (Medium)
 * https://leetcode.com/problems/max-area-of-island/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 * 
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 * The area of an island is the number of cells with a value 1 in the island.
 * Return the maximum area of an island in grid. If there is no island, return 0.
 * 
 * Example 1:
 *     Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
 *     Output: 6
 *     Explanation: The answer is not 11, because the island must be connected 4-directionally.
 * 
 * Example 2:
 *     Input: grid = [[0,0,0,0,0,0,0,0]]
 *     Output: 0
 * 
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 50
 *     - grid[i][j] is either 0 or 1.
 * 
 * Template (python3):
 *     class Solution:
 *         def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
 * 
 * Hint: Use DFS to explore each island and track the maximum area found.
 */
#[allow(unused_imports)]
use rstest;

fn max_area_of_island(grid: &mut [Vec<i32>]) -> i32 {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  695. Max Area of Island");
    println!("============================================================");

    let mut passed = 0;

    {
        let mut g = vec![vec![0,0,1,0,0,0,0,1,0,0,0,0,0],vec![0,0,0,0,0,0,0,1,1,1,0,0,0],vec![0,1,1,0,1,0,0,0,0,0,0,0,0],vec![0,1,0,0,1,1,0,0,1,0,1,0,0],vec![0,1,0,0,1,1,0,0,1,1,1,0,0],vec![0,0,0,0,0,0,0,0,0,0,1,0,0],vec![0,0,0,0,0,0,0,1,1,1,0,0,0],vec![0,0,0,0,0,0,0,1,1,0,0,0,0]];
        let got = max_area_of_island(&mut g);
        if got == 6 { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: 6\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec![0,0,0,0,0,0,0,0]];
        let got = max_area_of_island(&mut g);
        if got == 0 { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n    Expected: 0\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec![1]];
        let got = max_area_of_island(&mut g);
        if got == 1 { passed += 1; println!("  Test 3 (single cell land): PASS"); }
        else { println!("  Test 3 (single cell land): FAIL\n    Expected: 1\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec![0]];
        let got = max_area_of_island(&mut g);
        if got == 0 { passed += 1; println!("  Test 4 (single cell water): PASS"); }
        else { println!("  Test 4 (single cell water): FAIL\n    Expected: 0\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec![1,1,1],vec![1,1,1],vec![1,1,1]];
        let got = max_area_of_island(&mut g);
        if got == 9 { passed += 1; println!("  Test 5 (all land 3x3): PASS"); }
        else { println!("  Test 5 (all land 3x3): FAIL\n    Expected: 9\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec![1,0,1,0,1]];
        let got = max_area_of_island(&mut g);
        if got == 1 { passed += 1; println!("  Test 6 (single row alternating): PASS"); }
        else { println!("  Test 6 (single row alternating): FAIL\n    Expected: 1\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec![1],vec![0],vec![1],vec![0],vec![1]];
        let got = max_area_of_island(&mut g);
        if got == 1 { passed += 1; println!("  Test 7 (single column alternating): PASS"); }
        else { println!("  Test 7 (single column alternating): FAIL\n    Expected: 1\n    Got:      {}", got); }
    }

    println!("\n  {}/7 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 7 { 0 } else { 1 });
}
