/*
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 * 
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 * 
 * Example 1:
 *     Input: grid = [
 *       ["1","1","1","1","0"],
 *       ["1","1","0","1","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","0","0","0"]
 *     ]
 *     Output: 1
 * 
 * Example 2:
 *     Input: grid = [
 *       ["1","1","0","0","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","1","0","0"],
 *       ["0","0","0","1","1"]
 *     ]
 *     Output: 3
 * 
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 300
 *     - grid[i][j] is '0' or '1'.
 * 
 * Template (python3):
 *     class Solution:
 *         def numIslands(self, grid: List[List[str]]) -> int:
 * 
 * Hint: Use DFS to mark visited land cells, counting each new island.
 */
#[allow(unused_imports)]
use rstest;

fn num_islands(grid: &mut [Vec<char>]) -> i32 {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  200. Number of Islands");
    println!("============================================================");

    let mut passed = 0;

    {
        let mut g = vec![vec!['1','1','1','1','0'],vec!['1','1','0','1','0'],vec!['1','1','0','0','0'],vec!['0','0','0','0','0']];
        let got = num_islands(&mut g);
        if got == 1 { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: 1\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec!['1','1','0','0','0'],vec!['1','1','0','0','0'],vec!['0','0','1','0','0'],vec!['0','0','0','1','1']];
        let got = num_islands(&mut g);
        if got == 3 { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n    Expected: 3\n    Got:      {}", got); }
    }
    {
        let mut g: Vec<Vec<char>> = vec![];
        let got = num_islands(&mut g);
        if got == 0 { passed += 1; println!("  Test 3 (empty grid): PASS"); }
        else { println!("  Test 3 (empty grid): FAIL\n    Expected: 0\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec!['0']];
        let got = num_islands(&mut g);
        if got == 0 { passed += 1; println!("  Test 4 (single cell water): PASS"); }
        else { println!("  Test 4 (single cell water): FAIL\n    Expected: 0\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec!['1']];
        let got = num_islands(&mut g);
        if got == 1 { passed += 1; println!("  Test 5 (single cell land): PASS"); }
        else { println!("  Test 5 (single cell land): FAIL\n    Expected: 1\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec!['1','0','1','0','1']];
        let got = num_islands(&mut g);
        if got == 3 { passed += 1; println!("  Test 6 (single row): PASS"); }
        else { println!("  Test 6 (single row): FAIL\n    Expected: 3\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec!['1'],vec!['0'],vec!['1'],vec!['0'],vec!['1']];
        let got = num_islands(&mut g);
        if got == 3 { passed += 1; println!("  Test 7 (single column): PASS"); }
        else { println!("  Test 7 (single column): FAIL\n    Expected: 3\n    Got:      {}", got); }
    }
    {
        let mut g = vec![vec!['1','1','1'],vec!['1','1','1'],vec!['1','1','1']];
        let got = num_islands(&mut g);
        if got == 1 { passed += 1; println!("  Test 8 (all land 3x3): PASS"); }
        else { println!("  Test 8 (all land 3x3): FAIL\n    Expected: 1\n    Got:      {}", got); }
    }

    println!("\n  {}/8 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 8 { 0 } else { 1 });
}
