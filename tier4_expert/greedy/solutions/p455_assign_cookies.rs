/*
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 *
 * Each child i has a greed factor g[i], and each cookie j has a size s[j].
 * Return the maximum number of content children.
 */


fn find_content_children(mut g: Vec<i32>, mut s: Vec<i32>) -> i32 {
    g.sort();
    s.sort();
    let (mut child, mut cookie) = (0usize, 0usize);
    while child < g.len() && cookie < s.len() {
        if s[cookie] >= g[child] { child += 1; }
        cookie += 1;
    }
    child as i32
}

fn main() {
    let g = wasm_libs::read_ints();
    let s = wasm_libs::read_ints();
    let result = find_content_children(g, s);
    wasm_libs::write_int(result);
}
