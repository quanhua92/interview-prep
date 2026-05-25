/**
 * P553: Optimal Division [PREMIUM] (Medium)
 * https://leetcode.com/problems/optimal-division/
 * Topics: Array, Math, Dynamic Programming
 * 
 * You are given an integer array nums. The adjacent integers in nums will perform the float division.
 * However, you can add any number of parenthesis at any position to change the priority of operations. You want to add these parentheses such the value of the expression after the evaluation is maximum.
 * Return the corresponding expression that has the maximum value in string format.
 * Note: your expression should not contain redundant parenthesis.
 * Example 1:
 *     Input: nums = [1000,100,10,2]
 *     Output: "1000/(100/10/2)"
 *     Explanation: 1000/(100/10/2) = 1000/((100/10)/2) = 200
 *     However, the bold parenthesis in "1000/((100/10)/2)" are redundant since they do not influence the operation priority.
 *     So you should return "1000/(100/10/2)".
 *     Other cases:
 *     1000/(100/10)/2 = 50
 *     1000/(100/(10/2)) = 50
 *     1000/100/10/2 = 0.5
 *     1000/100/(10/2) = 2
 * 
 * Example 2:
 *     Input: nums = [2,3,4]
 *     Output: "2/(3/4)"
 *     Explanation: (2/(3/4)) = 8/3 = 2.667
 *     It can be shown that after trying all possibilities, we cannot get an expression with evaluation greater than 2.667
 * 
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - 2 <= nums[i] <= 1000
 *     - There is only one optimal division for the given input.
 * 
 * Template (python3):
 *     class Solution:
 *         def optimalDivision(self, nums: List[int]) -> str:
 */
function solve(nums)
  if (nums.length <= 2) return nums.join("/");
  return `${nums[0]}/(${nums.slice(1).join("/")})`; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [1000, 100, 10, 2], expected: "1000/(100/10/2)" },
  { label: "example 2", input: [2, 3, 4], expected: "2/(3/4)" },
  { label: "two elements no parens", input: [2, 3], expected: "2/3" },
  { label: "single element", input: [2], expected: "2" },
  { label: "three elements", input: [10, 2, 5], expected: "10/(2/5)" },
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
