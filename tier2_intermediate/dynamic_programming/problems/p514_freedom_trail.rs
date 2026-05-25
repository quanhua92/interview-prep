/*
 * P514: Freedom Trail [PREMIUM] (Hard)
 * https://leetcode.com/problems/freedom-trail/
 * Topics: String, Dynamic Programming, Depth-First Search, Breadth-First Search
 * 
 * In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.
 * Given a string ring that represents the code engraved on the outer ring and another string key that represents the keyword that needs to be spelled, return the minimum number of steps to spell all the characters in the keyword.
 * Initially, the first character of the ring is aligned at the "12:00" direction. You should spell all the characters in key one by one by rotating ring clockwise or anticlockwise to make each character of the string key aligned at the "12:00" direction and then by pressing the center button.
 * At the stage of rotating the ring to spell the key character key[i]:
 * Example 1:
 *     Input: ring = "godding", key = "gd"
 *     Output: 4
 *     Explanation:
 *     For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
 *     For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
 *     Also, we need 1 more step for spelling.
 *     So the final output is 4.
 * 
 * Example 2:
 *     Input: ring = "godding", key = "godding"
 *     Output: 13
 * 
 * Constraints:
 *     - 1 <= ring.length, key.length <= 100
 *     - ring and key consist of only lower case English letters.
 *     - It is guaranteed that key could always be spelled by rotating ring.
 * 
 * Template (python3):
 *     class Solution:
 *         def findRotateSteps(self, ring: str, key: str) -> int:
 */
use rstest;

fn find_rotate_steps(ring: &str, key: &str) -> i32 {
    todo!()
}

fn main() {
    struct TC<'a> { label: &'a str, ring: &'a str, key: &'a str, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", ring: "godding", key: "gd", expected: 4 },
        TC { label: "example 2", ring: "godding", key: "godding", expected: 13 },
        TC { label: "single char ring and key", ring: "a", key: "a", expected: 1 },
        TC { label: "reverse order key", ring: "abc", key: "cba", expected: 6 },
        TC { label: "repeated chars", ring: "aaaaa", key: "aaa", expected: 3 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_rotate_steps(tc.ring, tc.key);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL (expected {}, got {})", i + 1, tc.label, tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
