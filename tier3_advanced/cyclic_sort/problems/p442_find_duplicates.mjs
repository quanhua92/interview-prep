/**
 * P442: Find All Duplicates in an Array (Medium)
 * https://leetcode.com/problems/find-all-duplicates-in-an-array/
 * Topics: Array, Hash Table
 * 
 * Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.
 * You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output
 * 
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [2,3]
 * 
 * Example 2:
 *     Input: nums = [1,1,2]
 *     Output: [1]
 * 
 * Example 3:
 *     Input: nums = [1]
 *     Output: []
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 *     - Each element in nums appears once or twice.
 * 
 * Template (python3):
 *     class Solution:
 *         def findDuplicates(self, nums: List[int]) -> List[int]:
 * 
 * Hint: Negate the value at index abs(num)-1 to mark seen numbers in-place.
 */
function solve(nums)
  const result = [];
  for (const num of nums)
    const idx = Math.abs(num) - 1;
    if (nums[idx] < 0)
      result.push(Math.abs(num));
    } else
      nums[idx] = -nums[idx];
    }
  }
  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[4, 3, 2, 7, 8, 2, 3, 1]], expected: [2, 3] },
  { label: "example 2", input: [[1, 1, 2]], expected: [1] },
  { label: "single", input: [[1]], expected: [] },
  { label: "all same, n=2", input: [[2, 2]], expected: [2] },
  { label: "all duplicates, n=4", input: [[1, 2, 2, 1]], expected: [2, 1] },
  { label: "no duplicates", input: [[1, 2]], expected: [] },
  { label: "large, multiple duplicates", input: [[10, 2, 5, 10, 9, 1, 1, 7, 9, 6]], expected: [10, 1, 9] },
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
