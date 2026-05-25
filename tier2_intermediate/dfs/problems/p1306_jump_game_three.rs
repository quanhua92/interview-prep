/*
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 * 
 * Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
 * Notice that you can not jump outside of the array at any time.
 * 
 * Example 1:
 *     Input: arr = [4,2,3,0,3,1,2], start = 5
 *     Output: true
 *     Explanation:
 *     All possible ways to reach at index 3 with value 0 are:
 *     index 5 -> index 4 -> index 1 -> index 3
 *     index 5 -> index 6 -> index 4 -> index 1 -> index 3
 * 
 * Example 2:
 *     Input: arr = [4,2,3,0,3,1,2], start = 0
 *     Output: true
 *     Explanation:
 *     One possible way to reach at index 3 with value 0 is:
 *     index 0 -> index 4 -> index 1 -> index 3
 * 
 * Example 3:
 *     Input: arr = [3,0,2,1,2], start = 2
 *     Output: false
 *     Explanation: There is no way to reach at index 1 with value 0.
 * 
 * Constraints:
 *     - 1 <= arr.length <= 5 * 104
 *     - 0 <= arr[i] < arr.length
 *     - 0 <= start < arr.length
 * 
 * Hints:
 *     - Think of BFS to solve the problem.
 *     - When you reach a position with a value = 0 then return true.
 * 
 * Template (python3):
 *     class Solution:
 *         def canReach(self, arr: List[int], start: int) -> bool:
 * 
 * Hint: DFS with a visited set; explore start+arr[start] and start-arr[start], checking bounds and visited.
 */
#[allow(unused_imports)]
use rstest;

fn can_reach(arr: &[i32], start: usize) -> bool {
    todo!()
}

fn main() {
    struct TestCase {
        label: &'static str,
        input: &'static [i32],
        start: usize,
        expected: bool,
    }

    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input: &[4, 2, 3, 0, 3, 1, 2], start: 5, expected: true },
        TestCase { label: "start at index 0", input: &[4, 2, 3, 0, 3, 1, 2], start: 0, expected: true },
        TestCase { label: "cannot reach zero", input: &[3, 0, 2, 1, 2], start: 2, expected: false },
        TestCase { label: "single element zero", input: &[0], start: 0, expected: true },
        TestCase { label: "single element non-zero", input: &[2], start: 0, expected: false },
        TestCase { label: "start next to zero", input: &[0, 1], start: 1, expected: true },
        TestCase { label: "linear path to zero", input: &[1, 1, 1, 1, 0], start: 0, expected: true },
        TestCase { label: "jump directly to zero", input: &[7, 0, 0, 0, 0, 0, 0, 0], start: 0, expected: true },
    ];

    println!("\n============================================================");
    println!("  1306. Jump Game III");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = can_reach(tc.input, tc.start);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
