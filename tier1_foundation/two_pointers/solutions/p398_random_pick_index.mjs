/**
 * P398: Random Pick Index [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-pick-index/
 * Topics: Hash Table, Math, Reservoir Sampling, Randomized
 * 
 * Given an integer array nums with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "pick", "pick", "pick"]
 *     [[[1, 2, 3, 3, 3]], [3], [1], [3]]
 *     Output
 *     [null, 4, 0, 2]
 * 
 *     Explanation
 *     Solution solution = new Solution([1, 2, 3, 3, 3]);
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 *     solution.pick(1); // It should return 0. Since in the array only nums[0] is equal to 1.
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -231 <= nums[i] <= 231 - 1
 *     - target is an integer from nums.
 *     - At most 104 calls will be made to pick.
 */

class Solution {
  constructor(nums) {
    this.idx = new Map();
    for (let i = 0; i < nums.length; i++) {
      const v = nums[i];
      if (!this.idx.has(v)) this.idx.set(v, []);
      this.idx.get(v).push(i);
    }
  }

  pick(target) {
    const indices = this.idx.get(target);
    return indices[Math.floor(Math.random() * indices.length)];
  }
}

// --- tests ---
function test() {
  const tests = [
    { label: "returns valid index for target 3", input: [[1, 2, 3, 3, 3], 3], expected: [2, 3, 4] },
    { label: "single occurrence", input: [[1, 2, 3, 3, 3], 1], expected: [0] },
    { label: "single element array", input: [[5], 5], expected: [0] },
    { label: "non-contiguous duplicates", input: [[1, 2, 1, 2, 1], 1], expected: [0, 2, 4] },
    { label: "negative numbers with duplicates", input: [[-1, -2, -1, -3, -1], -1], expected: [0, 2, 4] },
    { label: "all same elements", input: [[1, 1, 1, 1, 1], 1], expected: [0, 1, 2, 3, 4] },
  ];
  let passed = 0;
  for (let i = 0; i < tests.length; i++) {
    const t = tests[i];
    const sol = new Solution(t.input[0]);
    const got = sol.pick(t.input[1]);
    if (t.expected.includes(got)) {
      passed++;
      console.log(`  Test ${i + 1} (${t.label}): PASS`);
    } else {
      console.log(`  Test ${i + 1} (${t.label}): FAIL`);
      console.log(`    Expected one of: ${JSON.stringify(t.expected)}\n    Got:            ${got}`);
    }
  }
  console.log(`\n  ${passed}/${tests.length} passed`);
  process.exit(passed === tests.length ? 0 : 1);
}

test();
