/*
 * P565: Array Nesting [PREMIUM] (Medium)
 * https://leetcode.com/problems/array-nesting/
 * Topics: Array, Depth-First Search
 */

use wasm_libs::*;

fn main() {
    let nums = read_ints();
    let mut visited = vec![false; nums.len()];
    let mut max_len = 0;
    for i in 0..nums.len() {
        if !visited[i] {
            let mut count = 0;
            let mut j = i;
            while !visited[j] {
                visited[j] = true;
                j = nums[j] as usize;
                count += 1;
            }
            max_len = max_len.max(count);
        }
    }
    write_int(max_len);
}
