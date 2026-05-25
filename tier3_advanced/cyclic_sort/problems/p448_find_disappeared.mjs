/**
 * P448: Find All Numbers Disappeared in an Array (Easy)
 * https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 * Topics: Array, Hash Table
 * 
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
 * 
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [5,6]
 * 
 * Example 2:
 *     Input: nums = [1,1]
 *     Output: [2]
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 * 
 * Follow up:
 *     - Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
 * 
 * Hints:
 *     - This is a really easy problem if you decide to use additional memory. For those trying to write an initial solution using additional memory, think <b>counters!</b>
 *     - However, the trick really is to not use any additional space than what is already available to use. Sometimes, multiple passes over the input array help find the solution. However, there's an interesting piece of information in this problem that makes it easy to re-use the input array itself for the solution.
 *     - The problem specifies that the numbers in the array will be in the range [1, n] where n is the number of elements in the array. Can we use this information and modify the array in-place somehow to find what we need?
 * 
 * Template (python3):
 *     class Solution:
 *         def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
 * 
 * Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
 */
function solve(nums)
  for (const n of nums)
    const index = Math.abs(n) - 1;
    if (nums[index] > 0)
      nums[index] = -nums[index];
    }
  }
  const result = [];
  for (let i = 0; i < nums.length; i++)
    if (nums[i] > 0) result.push(i + 1);
  }
  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[4, 3, 2, 7, 8, 2, 3, 1]], expected: [5, 6] },
  { label: "example 2", input: [[1, 1]], expected: [2] },
  { label: "example 3", input: [[2, 2]], expected: [1] },
  { label: "single element, none missing", input: [[1]], expected: [] },
  { label: "all same value", input: [[1, 1, 1, 1]], expected: [2, 3, 4] },
  { label: "identity permutation, none missing", input: [[1, 2, 3, 4, 5]], expected: [] },
  { label: "large, many disappeared", input: [[5, 4, 6, 7, 9, 10, 9, 6, 5, 4]], expected: [1, 2, 3, 8] },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0]);
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
