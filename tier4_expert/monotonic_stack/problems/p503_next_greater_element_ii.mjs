/**
 * P503: Next Greater Element II [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-ii/
 * Topics: Array, Stack, Monotonic Stack
 * 
 * Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.
 * The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.
 * Example 1:
 *     Input: nums = [1,2,1]
 *     Output: [2,-1,2]
 *     Explanation: The first 1's next greater number is 2;
 *     The number 2 can't find next greater number.
 *     The second 1's next greater number needs to search circularly, which is also 2.
 * 
 * Example 2:
 *     Input: nums = [1,2,3,4,3]
 *     Output: [2,3,4,-1,4]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -109 <= nums[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElements(self, nums: List[int]) -> List[int]:
 */
function solve(nums)
  const n = nums.length;
  const result = new Array(n).fill(-1);
  const stack = [];
  for (let i = 0; i < 2 * n; i++)
    const idx = i % n;
    while (stack.length > 0 && nums[stack[stack.length - 1]] < nums[idx])
      result[stack.pop()] = nums[idx];
    }
    if (i < n) stack.push(idx);
  }
  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { input: [1, 2, 1], expected: [2, -1, 2], label: "example 1" },
  { input: [1, 2, 3, 4, 3], expected: [2, 3, 4, -1, 4], label: "example 2" },
  { input: [5], expected: [-1], label: "single element" },
  { input: [2, 2, 2], expected: [-1, -1, -1], label: "all same" },
  { input: [5, 4, 3, 2], expected: [-1, 5, 5, 5], label: "strictly decreasing wraps" },
  { input: [-3, -2, -1], expected: [-2, -1, -1], label: "with negatives" },
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
