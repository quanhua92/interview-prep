/**
 * P15: 3Sum (Medium)
 * https://leetcode.com/problems/3sum/
 * Topics: Array, Two Pointers, Sorting
 * 
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * Notice that the solution set must not contain duplicate triplets.
 * 
 * Example 1:
 *     Input: nums = [-1,0,1,2,-1,-4]
 *     Output: [[-1,-1,2],[-1,0,1]]
 *     Explanation:
 *     nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 *     nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 *     nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 *     The distinct triplets are [-1,0,1] and [-1,-1,2].
 *     Notice that the order of the output and the order of the triplets does not matter.
 * 
 * Example 2:
 *     Input: nums = [0,1,1]
 *     Output: []
 *     Explanation: The only possible triplet does not sum up to 0.
 * 
 * Example 3:
 *     Input: nums = [0,0,0]
 *     Output: [[0,0,0]]
 *     Explanation: The only possible triplet sums up to 0.
 * 
 * Constraints:
 *     - 3 <= nums.length <= 3000
 *     - -105 <= nums[i] <= 105
 * 
 * Hint: Sort, iterate i, nested two pointers for remaining pair, skip duplicates.
 */

function solve(nums) {
  nums.sort((a, b) => a - b);
  const result = [];
  const n = nums.length;
  for (let i = 0; i < n - 2; i++) {
    if (i > 0 && nums[i] === nums[i - 1]) continue;
    let left = i + 1, right = n - 1;
    while (left < right) {
      const total = nums[i] + nums[left] + nums[right];
      if (total < 0) {
        left++;
      } else if (total > 0) {
        right--;
      } else {
        result.push([nums[i], nums[left], nums[right]]);
        while (left < right && nums[left] === nums[left + 1]) left++;
        while (left < right && nums[right] === nums[right - 1]) right--;
        left++;
        right--;
      }
    }
  }
  return result.map(t => t.sort((a, b) => a - b)).sort((a, b) => a[0] - b[0] || a[1] - b[1] || a[2] - b[2]);
}

// --- tests ---
const tests = [
  { label: "example 1", input: [[-1, 0, 1, 2, -1, -4]], expected: [[-1, -1, 2], [-1, 0, 1]] },
  { label: "no triplets", input: [[0, 1, 1]], expected: [] },
  { label: "all zeros", input: [[0, 0, 0]], expected: [[0, 0, 0]] },
  { label: "empty", input: [[]], expected: [] },
  { label: "adjacent duplicate pairs", input: [[-2, 0, 0, 2, 2]], expected: [[-2, 0, 2]] },
  { label: "all identical values", input: [[0, 0, 0, 0, 0]], expected: [[0, 0, 0]] },
  { label: "skip-i with left/right dup", input: [[-3, -3, 0, 1, 1, 2, 2]], expected: [[-3, 1, 2]] },
  { label: "triple duplicate", input: [[-2, 0, 0, 0, 2, 2, 2]], expected: [[-2, 0, 2], [0, 0, 0]] },
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
