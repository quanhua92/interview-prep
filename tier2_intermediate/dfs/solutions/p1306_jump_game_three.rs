/*
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 */

use wasm_libs::*;

fn main() {
    let arr = read_ints();
    let start: usize = read_line().trim().parse().unwrap();
    let n = arr.len();
    let mut visited = vec![false; n];

    fn dfs(arr: &[i32], i: i32, visited: &mut [bool], n: usize) -> bool {
        if i < 0 || i as usize >= n || visited[i as usize] {
            return false;
        }
        if arr[i as usize] == 0 {
            return true;
        }
        visited[i as usize] = true;
        let jump = arr[i as usize];
        dfs(arr, i + jump as i32, visited, n) || dfs(arr, i - jump as i32, visited, n)
    }

    write_bool(dfs(&arr, start as i32, &mut visited, n));
}
