/**
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
 * Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
 */

const testCases = [
  { input: [["a==b", "b!=a"]], expected: false, label: "example 1" },
  { input: [["b==a", "a==b"]], expected: true, label: "example 2" },
  { input: [["a==b", "b==c", "a==c"]], expected: true, label: "example 3" },
  { input: [["a!=a"]], expected: false, label: "contradiction" },
  { input: [["a!=b", "b!=c", "c!=a"]], expected: true, label: "all different no contradiction" },
  { input: [["a==b", "b==c", "c==d", "a!=d"]], expected: false, label: "chain equality then inequality" },
  { input: [["a==b", "c!=d"]], expected: true, label: "independent groups" },
  { input: [["a==a"]], expected: true, label: "self equality" },
];

function solve(equations) {
  throw new Error("NotImplementedError");
}

// Run tests
for (const t of testCases) {
  const got = solve(...t.input);
  const ok = JSON.stringify(got) === JSON.stringify(t.expected);
  console.log(`${ok ? "PASS" : "FAIL"} | ${t.label} | got: ${got} | expected: ${t.expected}`);
}
