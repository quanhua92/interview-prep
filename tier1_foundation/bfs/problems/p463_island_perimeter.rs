/*
 * P463: Island Perimeter [PREMIUM] (Easy)
 * https://leetcode.com/problems/island-perimeter/
 * Topics: Array, Depth-First Search, Breadth-First Search, Matrix
 * 
 * You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
 * Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
 * The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
 * Example 1:
 *     Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
 *     Output: 16
 *     Explanation: The perimeter is the 16 yellow stripes in the image above.
 * 
 * Example 2:
 *     Input: grid = [[1]]
 *     Output: 4
 * 
 * Example 3:
 *     Input: grid = [[1,0]]
 *     Output: 4
 * 
 * Constraints:
 *     - row == grid.length
 *     - col == grid[i].length
 *     - 1 <= row, col <= 100
 *     - grid[i][j] is 0 or 1.
 *     - There is exactly one island in grid.
 * 
 * Template (python3):
 *     class Solution:
 *         def islandPerimeter(self, grid: List[List[int]]) -> int:
 */
use std::collections::VecDeque;

fn island_perimeter(grid: &[Vec<i32>]) -> i32 {
    todo!()
}

fn main() {
    let tests: Vec<(&str, Vec<Vec<i32>>, i32)> = vec![
        ("example 1", vec![vec![0,1,0,0], vec![1,1,1,0], vec![0,1,0,0], vec![1,1,0,0]], 16),
        ("example 2", vec![vec![1]], 4),
        ("example 3", vec![vec![1,0]], 4),
        ("horizontal line of 3", vec![vec![1,1,1]], 8),
        ("vertical line of 3", vec![vec![1], vec![1], vec![1]], 8),
        ("2x2 block", vec![vec![1,1], vec![1,1]], 8),
        ("3x2 block", vec![vec![1,1,1], vec![1,1,1]], 10),
    ];
    let mut passed = 0;
    for (i, (label, grid, expected)) in tests.iter().enumerate() {
        let got = island_perimeter(grid);
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {}", expected);
            println!("    Got:      {}", got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
