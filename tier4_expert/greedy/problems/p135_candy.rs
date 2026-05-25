/*
 * P135: Candy (Hard)
 * https://leetcode.com/problems/candy/
 * Topics: Array, Greedy
 * 
 * There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
 * You are giving candies to these children subjected to the following requirements:
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 * 
 * Example 1:
 *     Input: ratings = [1,0,2]
 *     Output: 5
 *     Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
 * 
 * Example 2:
 *     Input: ratings = [1,2,2]
 *     Output: 4
 *     Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
 *     The third child gets 1 candy because it satisfies the above two conditions.
 * 
 * Constraints:
 *     - n == ratings.length
 *     - 1 <= n <= 2 * 104
 *     - 0 <= ratings[i] <= 2 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def candy(self, ratings: List[int]) -> int:
 * 
 * Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
 */
fn candy(ratings: &[i32]) -> i32 {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  135. Candy");
    println!("============================================================");
    let tests: &[(&str, &[i32], i32)] = &[
        ("example 1", &[1,0,2], 5),
        ("example 2", &[1,2,2], 4),
        ("decreasing then flat", &[1,3,2,2,1], 7),
        ("single child", &[1], 1),
        ("all same ratings", &[2,2,2,2], 4),
        ("strictly increasing", &[1,2,3,4], 10),
        ("strictly decreasing", &[4,3,2,1], 10),
        ("increase then drop", &[1,3,4,5,2], 11),
    ];
    let mut passed = 0;
    for (i, (label, ratings, expected)) in tests.iter().enumerate() {
        let got = candy(ratings);
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {}, Got: {}", expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
