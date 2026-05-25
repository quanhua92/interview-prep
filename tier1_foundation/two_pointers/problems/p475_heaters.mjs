/**
 * P475: Heaters [PREMIUM] (Medium)
 * https://leetcode.com/problems/heaters/
 * Topics: Array, Two Pointers, Binary Search, Sorting
 * 
 * Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.
 * Every house can be warmed, as long as the house is within the heater's warm radius range.
 * Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.
 * Notice that all the heaters follow your radius standard, and the warm radius will the same.
 * Example 1:
 *     Input: houses = [1,2,3], heaters = [2]
 *     Output: 1
 *     Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
 * 
 * Example 2:
 *     Input: houses = [1,2,3,4], heaters = [1,4]
 *     Output: 1
 *     Explanation: The two heaters were placed at positions 1 and 4. We need to use a radius 1 standard, then all the houses can be warmed.
 * 
 * Example 3:
 *     Input: houses = [1,5], heaters = [2]
 *     Output: 3
 * 
 * Constraints:
 *     - 1 <= houses.length, heaters.length <= 3 * 104
 *     - 1 <= houses[i], heaters[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def findRadius(self, houses: List[int], heaters: List[int]) -> int:
 */
function solve(houses, heaters)
  houses = [...houses].sort((a, b) => a - b);
  heaters = [...heaters].sort((a, b) => a - b);
  let result = 0;
  let i = 0, j = 0;
  while (i < houses.length)
    while (j + 1 < heaters.length && Math.abs(houses[i] - heaters[j]) >= Math.abs(houses[i] - heaters[j + 1]))
      j++;
    }
    result = Math.max(result, Math.abs(houses[i] - heaters[j]));
    i++;
  }
  return result; {
    throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: [[1, 2, 3], [2]], expected: 1 },
  { label: "example 2", input: [[1, 2, 3, 4], [1, 4]], expected: 1 },
  { label: "example 3", input: [[1, 5], [2]], expected: 3 },
  { label: "house at heater position", input: [[1], [1]], expected: 0 },
  { label: "houses between heaters", input: [[1, 2, 3, 4, 5, 6], [1, 6]], expected: 2 },
  { label: "single heater center", input: [[10, 20, 30], [15]], expected: 15 },
  { label: "all houses before heaters", input: [[1, 2, 3], [4, 5, 6]], expected: 3 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0], t.input[1]);
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
