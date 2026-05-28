/*
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 *
 * Each child i has a greed factor g[i], and each cookie j has a size s[j].
 * Return the maximum number of content children.
 */

use wasm_libs::*;

fn find_content_children(mut g: Vec<i32>, mut s: Vec<i32>) -> i32 {
    todo!();
}

fn main() {
    let g = read_ints();
    let s = read_ints();
    let result = find_content_children(g, s);
    write_int(result);
}
