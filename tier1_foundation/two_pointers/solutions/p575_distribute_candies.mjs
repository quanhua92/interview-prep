/**
 * P575: Distribute Candies [PREMIUM] (Easy)
 * https://leetcode.com/problems/distribute-candies/
 * Topics: Array, Hash Table
 *
 * Alice has n candies, where the ith candy is of type candyType[i]. Alice noticed that she started to gain weight, so she visited a doctor.
 * The doctor advised Alice to only eat n / 2 of the candies she has (n is always even). Alice likes her candies very much, and she wants to eat the maximum number of different types of candies while still following the doctor's advice.
 * Given the integer array candyType of length n, return the maximum number of different types of candies she can eat if she only eats n / 2 of them.
 * Example 1:
 *     Input: candyType = [1,1,2,2,3,3]
 *     Output: 3
 *     Explanation: Alice can only eat 6 / 2 = 3 candies. Since there are only 3 types, she can eat one of each type.
 *
 * Example 2:
 *     Input: candyType = [1,1,2,3]
 *     Output: 2
 *     Explanation: Alice can only eat 4 / 2 = 2 candies. Whether she eats types [1,2], [1,3], or [2,3], she still can only eat 2 different types.
 *
 * Example 3:
 *     Input: candyType = [6,6,6,6]
 *     Output: 1
 *     Explanation: Alice can only eat 4 / 2 = 2 candies. Even though she can eat 2 candies, she only has 1 type.
 *
 * Constraints:
 *     - n == candyType.length
 *     - 2 <= n <= 104
 *     - n is even.
 *     - -105 <= candyType[i] <= 105
 *
 * Hint: To maximize the number of kinds of candies, we should try to distribute candies such that Alice will gain all kinds.
 * Hint: What is the upper limit of the number of kinds of candies Alice will gain? Remember candies are to distributed equally.
 * Hint: Which data structure is the most suitable for finding the number of kinds of candies?
 * Hint: Will hashset solves the problem? Inserting all candies kind in the hashset and then checking its size with upper limit.
 *
 * Template (python3):
 *     class Solution:
 *         def distributeCandies(self, candyType: List[int]) -> int:
 */

function solve(candyType) {
  candyType.sort((a, b) => a - b);
  let unique = 1;
  const limit = Math.floor(candyType.length / 2);
  let left = 0;
  let right = 1;
  while (right < candyType.length && unique < limit) {
    if (candyType[right] !== candyType[left]) {
      unique++;
      left = right;
    }
    right++;
  }
  return Math.min(unique, limit);
}

const tests = [
  { label: "example 1", input: [1, 1, 2, 2, 3, 3], expected: 3 },
  { label: "example 2", input: [1, 1, 2, 3], expected: 2 },
  { label: "example 3", input: [6, 6, 6, 6], expected: 1 },
  { label: "all unique types", input: [1, 2, 3, 4], expected: 2 },
  { label: "negative candy types", input: [-1, -1, 2, 2], expected: 2 },
  { label: "boundary values", input: [100000, -100000, 0, 50000], expected: 2 },
  { label: "eight candies mixed", input: [1, 2, 1, 2, 1, 2, 3, 4], expected: 4 },
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
