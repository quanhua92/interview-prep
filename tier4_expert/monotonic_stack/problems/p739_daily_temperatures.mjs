/**
 * P739: Daily Temperatures (Medium)
 * https://leetcode.com/problems/daily-temperatures/
 * Topics: Array, Stack, Monotonic Stack
 * 
 * Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
 * 
 * Example 1:
 *     Input: temperatures = [73,74,75,71,69,72,76,73]
 *     Output: [1,1,4,2,1,1,0,0]
 * 
 * Example 2:
 *     Input: temperatures = [30,40,50,60]
 *     Output: [1,1,1,0]
 * 
 * Example 3:
 *     Input: temperatures = [30,60,90]
 *     Output: [1,1,0]
 * 
 * Constraints:
 *     - 1 <= temperatures.length <= 105
 *     - 30 <= temperatures[i] <= 100
 * 
 * Hints:
 *     - If the temperature is say, 70 today, then in the future a warmer temperature must be either 71, 72, 73, ..., 99, or 100.  We could remember when all of them occur next.
 * 
 * Template (python3):
 *     class Solution:
 *         def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
 * 
 * Hint: Use a monotonic decreasing stack to track indices of warmer days.
 */
function solve(temperatures)
  const n = temperatures.length;
  const answer = new Array(n).fill(0);
  const stack = [];
  for (let i = 0; i < n; i++)
    while (stack.length > 0 && temperatures[i] > temperatures[stack[stack.length - 1]])
      const j = stack.pop();
      answer[j] = i - j;
    }
    stack.push(i);
  }
  return answer; {
    throw new Error("NotImplementedError");
}

const tests = [
  { input: [73, 74, 75, 71, 69, 72, 76, 73], expected: [1, 1, 4, 2, 1, 1, 0, 0], label: "example 1" },
  { input: [30, 40, 50, 60], expected: [1, 1, 1, 0], label: "example 2" },
  { input: [30, 60, 90], expected: [1, 1, 0], label: "example 3" },
  { input: [50], expected: [0], label: "single element" },
  { input: [50, 50, 50], expected: [0, 0, 0], label: "all same temps" },
  { input: [90, 80, 70, 60], expected: [0, 0, 0, 0], label: "strictly decreasing" },
  { input: [50, 50, 50, 60], expected: [3, 2, 1, 0], label: "all same then warmer" },
];

let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input);
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
