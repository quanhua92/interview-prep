/*
 * P990: Satisfiability of Equality Equations (Medium)
 * https://leetcode.com/problems/satisfiability-of-equality-equations/
 * Topics: Array, String, Union Find, Graph
 *
 * You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
 * Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.
 *
 * Example 1:
 *     Input: equations = ["a==b","b!=a"]
 *     Output: false
 *     Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
 *     There is no way to assign the variables to satisfy both equations.
 *
 * Example 2:
 *     Input: equations = ["b==a","a==b"]
 *     Output: true
 *     Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
 *
 * Constraints:
 *     - 1 <= equations.length <= 500
 *     - equations[i].length == 4
 *     - equations[i][0] is a lowercase letter.
 *     - equations[i][1] is either '=' or '!'.
 *     - equations[i][2] is '='.
 *     - equations[i][3] is a lowercase letter.
 *
 * Template (python3):
 *     class Solution:
 *         def equationsPossible(self, equations: List[str]) -> bool:
 *
 * Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
 */

use wasm_libs::*;

fn equations_possible(equations: &[&str]) -> bool {
    let mut parent: Vec<i32> = (0..26).collect();
    let mut rank_: Vec<i32> = vec![0; 26];

    fn find(parent: &mut Vec<i32>, x: i32) -> i32 {
        if parent[x as usize] != x {
            parent[x as usize] = find(parent, parent[x as usize]);
        }
        parent[x as usize]
    }

    fn unite(parent: &mut Vec<i32>, rank_: &mut Vec<i32>, x: i32, y: i32) {
        let mut rx = find(parent, x);
        let mut ry = find(parent, y);
        if rx == ry { return; }
        if rank_[rx as usize] < rank_[ry as usize] {
            std::mem::swap(&mut rx, &mut ry);
        }
        parent[ry as usize] = rx;
        if rank_[rx as usize] == rank_[ry as usize] {
            rank_[rx as usize] += 1;
        }
    }

    for eq in equations {
        let bytes = eq.as_bytes();
        if bytes[1] == b'=' {
            unite(&mut parent, &mut rank_, (bytes[0] - b'a') as i32, (bytes[3] - b'a') as i32);
        }
    }

    for eq in equations {
        let bytes = eq.as_bytes();
        if bytes[1] == b'!' {
            if find(&mut parent, (bytes[0] - b'a') as i32) == find(&mut parent, (bytes[3] - b'a') as i32) {
                return false;
            }
        }
    }
    true
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
