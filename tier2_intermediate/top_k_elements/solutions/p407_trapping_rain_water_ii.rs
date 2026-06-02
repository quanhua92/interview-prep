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
 *     - 0 <= heightMap[i][j] <= 2 * 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def trapRainWater(self, heightMap: List[List[int]]) -> int:
 */

use wasm_libs::*;
use std::cmp::Reverse;
use std::collections::BinaryHeap;

fn trap_rain_water(height_map: &[Vec<i32>]) -> i32 {
    let m = height_map.len();
    if m == 0 { return 0; }
    let n = height_map[0].len();
    if n < 3 || m < 3 { return 0; }

    let mut visited = vec![vec![false; n]; m];
    let mut heap: BinaryHeap<Reverse<(i32, usize, usize)>> = BinaryHeap::new();

    for r in 0..m {
        heap.push(Reverse((height_map[r][0], r, 0)));
        visited[r][0] = true;
        heap.push(Reverse((height_map[r][n - 1], r, n - 1)));
        visited[r][n - 1] = true;
    }
    for c in 1..n - 1 {
        heap.push(Reverse((height_map[0][c], 0, c)));
        visited[0][c] = true;
        heap.push(Reverse((height_map[m - 1][c], m - 1, c)));
        visited[m - 1][c] = true;
    }

    let dirs: [(i32, i32); 4] = [(-1, 0), (1, 0), (0, -1), (0, 1)];
    let mut water = 0;

    while let Some(Reverse((h, r, c))) = heap.pop() {
        for (dr, dc) in dirs {
            let nr = r as i32 + dr;
            let nc = c as i32 + dc;
            if nr >= 0 && nr < m as i32 && nc >= 0 && nc < n as i32 {
                let nr = nr as usize;
                let nc = nc as usize;
                if !visited[nr][nc] {
                    visited[nr][nc] = true;
                    let nh = height_map[nr][nc];
                    if h > nh { water += h - nh; }
                    heap.push(Reverse((h.max(nh), nr, nc)));
                }
            }
        }
    }

    water
}

fn main() {
    let dims = read_ints();
    let m = dims[0] as usize;
    let n = dims[1] as usize;
    let mut height_map: Vec<Vec<i32>> = Vec::new();
    for _ in 0..m {
        height_map.push(read_ints());
    }
    write_int(trap_rain_water(&height_map));
    std::process::exit(0);
}
