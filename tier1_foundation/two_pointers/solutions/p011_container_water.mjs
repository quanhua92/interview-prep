/**
 * P11: Container With Most Water (Medium)
 * https://leetcode.com/problems/container-with-most-water/
 * Topics: Array, Two Pointers, Greedy
 * 
 * You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container, such that the container contains the most water.
 * Return the maximum amount of water a container can store.
 * Notice that you may not slant the container.
 * 
 * Example 1:
 *     Input: height = [1,8,6,2,5,4,8,3,7]
 *     Output: 49
 *     Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
 * 
 * Example 2:
 *     Input: height = [1,1]
 *     Output: 1
 * 
 * Constraints:
 *     - n == height.length
 *     - 2 <= n <= 105
 *     - 0 <= height[i] <= 104
 * 
 * Hints:
 *     - If you simulate the problem, it will be O(n^2) which is not efficient.
 *     - Try to use two-pointers. Set one pointer to the left and one to the right of the array. Always move the pointer that points to the lower line.
 *     - How can you calculate the amount of water at each step?
 * 
 * Hint: Start with pointers at both ends and move the shorter one inward.
 */

function solve(height) {
  let left = 0, right = height.length - 1;
  let maxArea = 0;
  while (left < right) {
    const area = Math.min(height[left], height[right]) * (right - left);
    maxArea = Math.max(maxArea, area);
    if (height[left] < height[right]) {
      left++;
    } else {
      right--;
    }
  }
  return maxArea;
}

// --- tests ---
const tests = [
  { label: "example 1", input: [[1, 8, 6, 2, 5, 4, 8, 3, 7]], expected: 49 },
  { label: "example 2", input: [[1, 1]], expected: 1 },
  { label: "symmetric", input: [[4, 3, 2, 1, 4]], expected: 16 },
  { label: "all zeros", input: [[0, 0, 0, 0]], expected: 0 },
  { label: "strictly increasing", input: [[1, 2, 3, 4, 5]], expected: 6 },
  { label: "strictly decreasing", input: [[5, 4, 3, 2, 1]], expected: 6 },
  { label: "max height two elements", input: [[10000, 10000]], expected: 10000 },
  { label: "all same height", input: [[2, 2, 2, 2, 2]], expected: 8 },
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
