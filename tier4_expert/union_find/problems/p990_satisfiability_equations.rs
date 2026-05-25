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
fn equations_possible(equations: &[&str]) -> bool {
    todo!()
}

struct TC {
    label: &'static str,
    equations: &'static [&'static str],
    expected: bool,
}

fn main() {
    let tcs: &[TC] = &[
        TC { label: "example 1", equations: &["a==b","b!=a"], expected: false },
        TC { label: "example 2", equations: &["b==a","a==b"], expected: true },
        TC { label: "example 3", equations: &["a==b","b==c","a==c"], expected: true },
        TC { label: "contradiction", equations: &["a!=a"], expected: false },
        TC { label: "all different no contradiction", equations: &["a!=b","b!=c","c!=a"], expected: true },
        TC { label: "chain equality then inequality", equations: &["a==b","b==c","c==d","a!=d"], expected: false },
        TC { label: "independent groups", equations: &["a==b","c!=d"], expected: true },
        TC { label: "self equality", equations: &["a==a"], expected: true },
    ];

    println!("\n============================================================");
    println!("  990. Satisfiability of Equality Equations");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tcs.iter().enumerate() {
        let got = equations_possible(tc.equations);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}\n    Got:      {}", tc.expected, got);
        }
    }

    println!("\n  {}/{} passed", passed, tcs.len());
    println!("============================================================\n");

    std::process::exit(if passed == tcs.len() { 0 } else { 1 });
}
