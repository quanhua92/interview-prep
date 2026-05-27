/*
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 *
 * Hint: Sort both arrays and use two pointers to greedily assign the smallest sufficient cookie.
 */


fn find_content_children(mut g: Vec<i32>, mut s: Vec<i32>) -> i32 {
    todo!()
}

fn main() {
    let g = wasm_libs::read_ints();
    let s = wasm_libs::read_ints();
    let result = find_content_children(g, s);
    wasm_libs::write_int(result);
}
