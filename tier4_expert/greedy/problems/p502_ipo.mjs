/**
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most k distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.
 * You are given n projects where the ith project has a pure profit profits[i] and a minimum capital of capital[i] is needed to start it.
 * Initially, you have w capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.
 * Pick a list of at most k distinct projects from given projects to maximize your final capital, and return the final maximized capital.
 * The answer is guaranteed to fit in a 32-bit signed integer.
 * Example 1:
 *     Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
 *     Output: 4
 *     Explanation: Since your initial capital is 0, you can only start the project indexed 0.
 *     After finishing it you will obtain profit 1 and your capital becomes 1.
 *     With capital 1, you can either start the project indexed 1 or the project indexed 2.
 *     Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
 *     Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
 *
 * Example 2:
 *     Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
 *     Output: 6
 *
 * Constraints:
 *     - 1 <= k <= 105
 *     - 0 <= w <= 109
 *     - n == profits.length
 *     - n == capital.length
 *     - 1 <= n <= 105
 *     - 0 <= profits[i] <= 104
 *     - 0 <= capital[i] <= 109
 *
 * Template (python3):
 *     class Solution:
 *         def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
 */

function solve(k, w, profits, capital) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [2, 0, [1, 2, 3], [0, 1, 1]], expected: 4 },
  { label: "example 2", input: [3, 0, [1, 2, 3], [0, 1, 2]], expected: 6 },
  { label: "k less than projects", input: [1, 0, [1, 2, 3], [0, 0, 0]], expected: 3 },
  { label: "k more than projects", input: [10, 0, [1, 2], [0, 0]], expected: 3 },
  { label: "single project", input: [1, 1, [5], [1]], expected: 6 },
  { label: "all affordable", input: [2, 5, [3, 4], [1, 2]], expected: 12 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
