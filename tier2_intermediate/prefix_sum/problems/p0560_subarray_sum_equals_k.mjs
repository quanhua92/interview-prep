/**
 * P560: Subarray Sum Equals K (Medium)
 * https://leetcode.com/problems/subarray-sum-equals-k/
 * Topics: Array, Hash Table, Prefix Sum
 * 
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 * 
 * Example 1:
 *     Input: nums = [1,1,1], k = 2
 *     Output: 2
 * 
 * Example 2:
 *     Input: nums = [1,2,3], k = 3
 *     Output: 2
 * 
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -1000 <= nums[i] <= 1000
 *     - -107 <= k <= 107
 * 
 * Hints:
 *     - Will Brute force work here? Try to optimize it.
 *     - Can we optimize it by using some extra space?
 *     - What about storing sum frequencies in a hash table? Will it be useful?
 *     - sum(i,j)=sum(0,j)-sum(0,i), where sum(i,j) represents the sum of all the elements from index i to j-1.
 * 
 * Can we use this property to optimize it.
 * 
 * Template (python3):
 *     class Solution:
 *         def subarraySum(self, nums: List[int], k: int) -> int:
 * 
 * Hint: Use a hash map with prefix sums to count subarrays summing to k.
 */
function solve(nums, k)
  let count = 0;
  let currSum = 0;
  const prefixFreq = new Map();
  prefixFreq.set(0, 1);

  for (const num of nums)
    currSum += num;
    count += prefixFreq.get(currSum - k) || 0;
    prefixFreq.set(currSum, (prefixFreq.get(currSum) || 0) + 1);
  }

  return count; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[1, 1, 1], 2], expected: 2 },
  { label: "example 2", input: [[1, 2, 3], 3], expected: 2 },
  { label: "empty array", input: [[], 0], expected: 0 },
  { label: "single element equals k", input: [[1], 1], expected: 1 },
  { label: "single element not k", input: [[1], 2], expected: 0 },
  { label: "negatives with zero sum", input: [[1, -1, 0], 0], expected: 3 },
  { label: "all zeros", input: [[0, 0, 0], 0], expected: 6 },
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
