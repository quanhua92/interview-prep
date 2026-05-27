/*
 * P135: Candy (Hard)
 * https://leetcode.com/problems/candy/
 * Topics: Array, Greedy
 *
 * Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
 */


fn candy(ratings: &[i32]) -> i32 {
    todo!()
}

fn main() {
    let ratings = wasm_libs::read_ints();
    let result = candy(&ratings);
    wasm_libs::write_int(result);
}
