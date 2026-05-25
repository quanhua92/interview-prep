/**
 * P456: 132 Pattern [PREMIUM] (Medium)
 * https://leetcode.com/problems/132-pattern/
 * Topics: Array, Binary Search, Stack, Monotonic Stack, Ordered Set
 * 
 * Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 * Example 1:
 *     Input: nums = [1,2,3,4]
 *     Output: false
 *     Explanation: There is no 132 pattern in the sequence.
 * 
 * Example 2:
 *     Input: nums = [3,1,4,2]
 *     Output: true
 *     Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
 * 
 * Example 3:
 *     Input: nums = [-1,3,2,0]
 *     Output: true
 *     Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 2 * 105
 *     - -109 <= nums[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def find132pattern(self, nums: List[int]) -> bool:
 */
function solve(nums)
  let third = -Infinity;
  const stack = [];
  for (let i = nums.length - 1; i >= 0; i--)
    const num = nums[i];
    if (num < third) return true;
    while (stack.length > 0 && stack[stack.length - 1] < num)
      third = stack.pop();
    }
    stack.push(num);
  }
  return false; {
    throw new Error("NotImplementedError");
}

const tests = [
  { input: [1, 2, 3, 4], expected: false, label: "example 1" },
  { input: [3, 1, 4, 2], expected: true, label: "example 2" },
  { input: [-1, 3, 2, 0], expected: true, label: "example 3" },
  { input: [1, 2], expected: false, label: "two elements" },
  { input: [2, 2, 2], expected: false, label: "all same" },
  { input: [5, 4, 3, 2, 1], expected: false, label: "strictly decreasing" },
  { input: [1, 3, 0, 2], expected: true, label: "pattern near end" },
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
