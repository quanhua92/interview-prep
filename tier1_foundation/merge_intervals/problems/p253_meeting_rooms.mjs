/**
 * P253: Meeting Rooms II (Medium)
 * https://leetcode.com/problems/meeting-rooms-ii/
 * Topics: Array, Two Pointers, Sorting, Heap (Priority Queue), Prefix Sum
 * 
 * Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.
 * 
 * Example 1:
 *     Input: intervals = [[0,30],[5,10],[15,20]]
 *     Output: 2
 * 
 * Example 2:
 *     Input: intervals = [[7,10],[2,4]]
 *     Output: 1
 * 
 * Constraints:
 *     - 1 <= intervals.length <= 10^4
 *     - 0 <= starti < endi <= 10^6
 * 
 * Hints:
 *     - Think about how we would approach this problem if we were given the intervals sorted by start time.
 *     - What if we use a min-heap to track the ending times of meetings?
 * 
 * Template (python3):
 *     class Solution:
 *         def minMeetingRooms(self, intervals: List[List[int]]) -> int:
 * 
 * Hint: Sort start and end times separately, then use two pointers to count concurrent meetings.
 */
function solve(intervals)
  if (intervals.length === 0) return 0;
  const events = [];
  for (const [start, end] of intervals)
    events.push([start, 1]);
    events.push([end, -1]);
  }
  events.sort((a, b) => a[0] - b[0] || a[1] - b[1]);
  let concurrent = 0;
  let maxRooms = 0;
  for (const [, delta] of events)
    concurrent += delta;
    maxRooms = Math.max(maxRooms, concurrent);
  }
  return maxRooms; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[[0, 30], [5, 10], [15, 20]]], expected: 2 },
  { label: "example 2", input: [[[7, 10], [2, 4]]], expected: 1 },
  { label: "no meetings", input: [[]], expected: 0 },
  { label: "single meeting", input: [[[0, 1]]], expected: 1 },
  { label: "all meetings overlap", input: [[[0, 10], [1, 9], [2, 8], [3, 7]]], expected: 4 },
  { label: "meetings end and start at same time", input: [[[0, 5], [5, 10], [5, 10]]], expected: 2 },
  { label: "all same start time", input: [[[0, 30], [0, 30], [0, 30]]], expected: 3 },
  { label: "no overlap sequential", input: [[[0, 1], [1, 2], [2, 3]]], expected: 1 },
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
