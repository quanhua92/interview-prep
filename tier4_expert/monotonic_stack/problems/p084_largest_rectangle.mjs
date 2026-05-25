/**
 * P84: Largest Rectangle in Histogram (Hard)
 * https://leetcode.com/problems/largest-rectangle-in-histogram/
 * Topics: Array, Stack, Monotonic Stack
 *
 * Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.
 *
 * Example 1:
 *     Input: heights = [2,1,5,6,2,3]
 *     Output: 10
 *     Explanation: The above is a histogram where width of each bar is 1.
 *     The largest rectangle is shown in the red area, which has an area = 10 units.
 *
 * Example 2:
 *     Input: heights = [2,4]
 *     Output: 4
 *
 * Constraints:
 *     - 1 <= heights.length <= 105
 *     - 0 <= heights[i] <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def largestRectangleArea(self, heights: List[int]) -> int:
 *
 * Hint: Use a monotonic increasing stack with a sentinel to compute max rectangle area.
 */

function solve(heights) {
  throw new Error("NotImplementedError");
}

const tests = [
  { input: [2, 1, 5, 6, 2, 3], expected: 10, label: "example 1" },
  { input: [2, 4], expected: 4, label: "example 2" },
  { input: [5], expected: 5, label: "single element" },
  { input: [3, 3, 3], expected: 9, label: "all same heights" },
  { input: [2, 0, 2], expected: 2, label: "contains zero height" },
  { input: [1, 2, 3, 4, 5], expected: 9, label: "strictly increasing" },
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
