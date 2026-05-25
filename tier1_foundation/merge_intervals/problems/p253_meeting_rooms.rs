/*
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
use rstest::TestCase;

fn min_meeting_rooms(intervals: &[i32]) -> i32 {
    todo!()
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[0, 30, 5, 10, 15, 20], target: 0, expected: &[2] },
        TestCase { label: "example 2", input_arr: &[7, 10, 2, 4], target: 0, expected: &[1] },
        TestCase { label: "no meetings", input_arr: &[], target: 0, expected: &[0] },
        TestCase { label: "single meeting", input_arr: &[0, 1], target: 0, expected: &[1] },
        TestCase { label: "all meetings overlap", input_arr: &[0, 10, 1, 9, 2, 8, 3, 7], target: 0, expected: &[4] },
        TestCase { label: "meetings end and start at same time", input_arr: &[0, 5, 5, 10, 5, 10], target: 0, expected: &[2] },
        TestCase { label: "all same start time", input_arr: &[0, 30, 0, 30, 0, 30], target: 0, expected: &[3] },
        TestCase { label: "no overlap sequential", input_arr: &[0, 1, 1, 2, 2, 3], target: 0, expected: &[1] },
    ];
    let total = tests.len();
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = min_meeting_rooms(tc.input_arr);
        if got == tc.expected[0] {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected[0]);
            println!("    Got:      {}", got);
        }
    }
    println!("\n  {}/{} passed", passed, total);
    std::process::exit(if passed == total { 0 } else { 1 });
}
