/*
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 * A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:
 * We can construct a Quad-Tree from a two-dimensional area using the following steps:
 * If you want to know more about the Quad-Tree, you can refer to the wiki.
 * Quad-Tree format:
 * You don't need to read this section for solving the problem. This is only if you want to understand the output format here. The output represents the serialized format of a Quad-Tree using level order traversal, where null signifies a path terminator where no node exists below.
 * It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list [isLeaf, val].
 * If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val] and if the value of isLeaf or val is False we represent it as 0.
 *     class Node {
 *     public boolean val;
 *     public boolean isLeaf;
 *     public Node topLeft;
 *     public Node topRight;
 *     public Node bottomLeft;
 *     public Node bottomRight;
 *     }
 *
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
 *     Explanation: The explanation of this example is shown below:
 *     Notice that 0 represents False and 1 represents True in the photo representing the Quad-Tree.
 *
 * Example 2:
 *     Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
 *     Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
 *     Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
 *     The topLeft, bottomLeft and bottomRight each has the same value.
 *     The topRight have different values so we divide it into 4 sub-grids where each has the same value.
 *     Explanation is shown in the photo below:
 *
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 *
 * Template (python3):
 *     '''
 *     # Definition for a QuadTree node.
 *     class Node:
 *         def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
 *             self.val = val
 *             self.isLeaf = isLeaf
 *             self.topLeft = topLeft
 *             self.topRight = topRight
 *             self.bottomLeft = bottomLeft
 *             self.bottomRight = bottomRight
 *     '''
 *
 *     class Solution:
 *         def construct(self, grid: List[List[int]]) -> 'Node':
 */

use wasm_libs::*;

fn all_same(grid: &[Vec<i32>], row: usize, col: usize, size: usize) -> bool {
    let v = grid[row][col];
    for i in row..row + size {
        for j in col..col + size {
            if grid[i][j] != v { return false; }
        }
    }
    true
}

enum QNode {
    Leaf(i32),
    Internal(i32, usize),
}

fn main() {
    let header = read_ints();
    let cols = header[0] as usize;
    let mut grid: Vec<Vec<i32>> = Vec::with_capacity(cols);
    for _ in 0..cols {
        grid.push(read_ints());
    }

    let mut flat: Vec<i32> = Vec::new();
    fn build_flat(grid: &[Vec<i32>], row: usize, col: usize, size: usize, flat: &mut Vec<i32>) -> usize {
        if all_same(grid, row, col, size) {
            flat.push(1);
            flat.push(grid[row][col]);
            flat.len() - 2
        } else {
            let half = size / 2;
            let idx = flat.len();
            flat.push(0);
            flat.push(1);
            build_flat(grid, row, col, half, flat);
            build_flat(grid, row, col + half, half, flat);
            build_flat(grid, row + half, col, half, flat);
            build_flat(grid, row + half, col + half, half, flat);
            idx
        }
    }
    build_flat(&grid, 0, 0, cols, &mut flat);

    use std::io::Write;
    let mut out = std::io::stdout().lock();

    fn compute_child_sizes(flat: &[i32], pos: usize) -> usize {
        if flat[pos] == 1 { return 2; }
        let mut total = 2;
        let mut p = pos + 2;
        for _ in 0..4 {
            let cs = compute_child_sizes(flat, p);
            p += cs;
            total += cs;
        }
        total
    }

    fn bfs_print(flat: &[i32], root_pos: usize, out: &mut std::io::StdoutLock) {
        let mut queue = std::collections::VecDeque::new();
        queue.push_back(root_pos);
        while let Some(pos) = queue.pop_front() {
            if flat[pos] == 1 {
                writeln!(out, "{} {}", flat[pos], flat[pos + 1]).unwrap();
            } else {
                writeln!(out, "{} {}", flat[pos], flat[pos + 1]).unwrap();
                let mut child_pos = pos + 2;
                for _ in 0..4 {
                    queue.push_back(child_pos);
                    child_pos += compute_child_sizes(flat, child_pos);
                }
            }
        }
    }

    bfs_print(&flat, 0, &mut out);
    std::process::exit(0);
}
