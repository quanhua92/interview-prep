/**
 * P238: Product of Array Except Self (Medium)
 * https://leetcode.com/problems/product-of-array-except-self/
 * Topics: Array, Prefix Sum
 * 
 * Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 * 
 * Example 1:
 *     Input: nums = [1,2,3,4]
 *     Output: [24,12,8,6]
 * 
 * Example 2:
 *     Input: nums = [-1,1,0,-3,3]
 *     Output: [0,0,9,0,0]
 * 
 * Constraints:
 *     - 2 <= nums.length <= 105
 *     - -30 <= nums[i] <= 30
 *     - The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
 * 
 * Follow up:
 *     - Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)
 * 
 * Hints:
 *     - Think how you can efficiently utilize prefix and suffix products to calculate the product of all elements except self for each index. Can you pre-compute the prefix and suffix products in linear time to avoid redundant calculations?
 *     - Can you minimize additional space usage by reusing memory or modifying the input array to store intermediate results?
 * 
 * Template (python3):
 *     class Solution:
 *         def productExceptSelf(self, nums: List[int]) -> List[int]:
 * 
 * Hint: Build left and right product arrays, then combine.
 */
function solve(nums)
  const n = nums.length;
  const output = new Array(n).fill(1);

  let leftProduct = 1;
  for (let i = 0; i < n; i++)
    output[i] = leftProduct;
    leftProduct *= nums[i];
  }

  let rightProduct = 1;
  for (let i = n - 1; i >= 0; i--)
    output[i] *= rightProduct;
    rightProduct *= nums[i];
  }

  return output; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [1, 2, 3, 4], expected: [24, 12, 8, 6] },
  { label: "example 2", input: [-1, 1, 0, -3, 3], expected: [0, 0, 9, 0, 0] },
  { label: "two elements", input: [1, 2], expected: [2, 1] },
  { label: "all ones", input: [1, 1, 1], expected: [1, 1, 1] },
  { label: "all negatives", input: [-1, -1, -1], expected: [1, 1, 1] },
  { label: "two elements negative", input: [1, -1], expected: [-1, 1] },
  { label: "all zeros", input: [0, 0, 0, 0], expected: [0, 0, 0, 0] },
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
