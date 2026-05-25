/**
 * P56: Merge Intervals (Medium)
 * https://leetcode.com/problems/merge-intervals/
 * Topics: Array, Sorting
 *
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
 *
 * Example 1:
 *     Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 *     Output: [[1,6],[8,10],[15,18]]
 *     Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
 *
 * Example 2:
 *     Input: intervals = [[1,4],[4,5]]
 *     Output: [[1,5]]
 *     Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 *
 * Constraints:
 *     - 1 <= intervals.length <= 104
 *     - intervals[i].length == 2
 *     - 0 <= starti <= endi <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def merge(self, intervals: List[List[int]]) -> List[List[int]]:
 *
 * Hint: Sort intervals by start time, then merge overlapping ones.
 */

function mergeIntervals(intervals) {
  if (!intervals || intervals.length === 0) return [];
  intervals.sort((a, b) => a[0] - b[0]);
  const merged = [intervals[0]];
  for (let i = 1; i < intervals.length; i++) {
    const [start, end] = intervals[i];
    const last = merged[merged.length - 1];
    if (start <= last[1]) {
      last[1] = Math.max(last[1], end);
    } else {
      merged.push([start, end]);
    }
  }
  return merged;
}

function solve(input) {
  return mergeIntervals(input);
}

// --- tests ---
const tests = [
  { label: "example 1", input: [[1, 3], [2, 6], [8, 10], [15, 18]], expected: [[1, 6], [8, 10], [15, 18]] },
  { label: "example 2", input: [[1, 4], [4, 5]], expected: [[1, 5]] },
  { label: "overlapping start", input: [[1, 4], [0, 4]], expected: [[0, 4]] },
  { label: "single interval", input: [[1, 1]], expected: [[1, 1]] },
  { label: "all overlap into one", input: [[1, 4], [2, 3], [3, 5]], expected: [[1, 5]] },
  { label: "no overlaps", input: [[1, 2], [3, 4], [5, 6]], expected: [[1, 2], [3, 4], [5, 6]] },
  { label: "interval contains others", input: [[1, 10], [2, 3], [4, 5]], expected: [[1, 10]] },
  { label: "adjacent intervals touching", input: [[1, 2], [2, 3], [3, 4]], expected: [[1, 4]] },
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
