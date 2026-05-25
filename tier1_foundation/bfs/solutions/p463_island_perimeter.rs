/*
 * P463: Island Perimeter [PREMIUM] (Easy)
 * https://leetcode.com/problems/island-perimeter/
 * Topics: Array, Depth-First Search, Breadth-First Search, Matrix
 *
 * You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
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
    let rows = grid.len();
    let cols = grid[0].len();
    let mut visited = vec![vec![false; cols]; rows];
    let mut perimeter = 0;
    let mut queue = VecDeque::new();
    let dirs: [(i32, i32); 4] = [(0, 1), (0, -1), (1, 0), (-1, 0)];

    for r in 0..rows {
        for c in 0..cols {
            if grid[r][c] == 1 {
                queue.push_back((r, c));
                visited[r][c] = true;
                while let Some((cr, cc)) = queue.pop_front() {
                    for &(dr, dc) in &dirs {
                        let nr = cr as i32 + dr;
                        let nc = cc as i32 + dc;
                        if nr < 0 || nr >= rows as i32 || nc < 0 || nc >= cols as i32
                            || grid[nr as usize][nc as usize] == 0
                        {
                            perimeter += 1;
                        } else if !visited[nr as usize][nc as usize] {
                            visited[nr as usize][nc as usize] = true;
                            queue.push_back((nr as usize, nc as usize));
                        }
                    }
                }
                return perimeter;
            }
        }
    }
    0
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
