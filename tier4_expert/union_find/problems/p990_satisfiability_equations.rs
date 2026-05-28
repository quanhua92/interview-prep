/*
 * P990: Satisfiability of Equality Equations (Medium)
 * https://leetcode.com/problems/satisfiability-of-equality-equations/
 * Topics: Array, String, Union Find, Graph
 *
 * Return true if it is possible to assign integers to variable names so as to satisfy all the given equations.
 *
 * Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
 */

use wasm_libs::*;

fn equations_possible(equations: &[&str]) -> bool {
    todo!();
}

fn main() {
    let first_line = read_ints();
    let n = first_line[0] as usize;
    let mut eq_vec: Vec<String> = Vec::new();
    for _ in 0..n {
        eq_vec.push(read_line());
    }
    let eq_refs: Vec<&str> = eq_vec.iter().map(|s| s.as_str()).collect();
    write_bool(equations_possible(&eq_refs));
    std::process::exit(0);
}
