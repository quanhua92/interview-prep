/**
 * P495: Teemo Attacking [PREMIUM] (Easy)
 * https://leetcode.com/problems/teemo-attacking/
 * Topics: Array, Simulation
 * 
 * Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a exactly duration seconds. More formally, an attack at second t will mean Ashe is poisoned during the inclusive time interval [t, t + duration - 1]. If Teemo attacks again before the poison effect ends, the timer for it is reset, and the poison effect will end duration seconds after the new attack.
 * You are given a non-decreasing integer array timeSeries, where timeSeries[i] denotes that Teemo attacks Ashe at second timeSeries[i], and an integer duration.
 * Return the total number of seconds that Ashe is poisoned.
 * Example 1:
 *     Input: timeSeries = [1,4], duration = 2
 *     Output: 4
 *     Explanation: Teemo's attacks on Ashe go as follows:
 *     - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
 *     - At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
 *     Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.
 * 
 * Example 2:
 *     Input: timeSeries = [1,2], duration = 2
 *     Output: 3
 *     Explanation: Teemo's attacks on Ashe go as follows:
 *     - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
 *     - At second 2 however, Teemo attacks again and resets the poison timer. Ashe is poisoned for seconds 2 and 3.
 *     Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.
 * 
 * Constraints:
 *     - 1 <= timeSeries.length <= 104
 *     - 0 <= timeSeries[i], duration <= 107
 *     - timeSeries is sorted in non-decreasing order.
 * 
 * Template (python3):
 *     class Solution:
 *         def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:
 */
function solve(timeSeries, duration)
  if (timeSeries.length === 0) return 0;
  let total = 0;
  for (let i = 0; i < timeSeries.length - 1; i++)
    total += Math.min(duration, timeSeries[i + 1] - timeSeries[i]);
  }
  return total + duration; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[1, 4], 2], expected: 4 },
  { label: "example 2", input: [[1, 2], 2], expected: 3 },
  { label: "single attack", input: [[1], 2], expected: 2 },
  { label: "consecutive attacks, duration 1", input: [[1, 2, 3, 4, 5], 1], expected: 5 },
  { label: "non-overlapping attacks", input: [[1, 3, 5, 7, 9], 2], expected: 10 },
  { label: "duplicate timestamps", input: [[1, 1, 1, 1], 5], expected: 5 },
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
