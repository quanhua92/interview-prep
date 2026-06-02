/*
 * P475: Heaters [PREMIUM] (Medium)
 * https://leetcode.com/problems/heaters/
 * Topics: Array, Two Pointers, Binary Search, Sorting
 *
 * Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.
 * Every house can be warmed, as long as the house is within the heater's warm radius range.
 * Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.
 * Notice that all the heaters follow your radius standard, and the warm radius will the same.
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
 *     - 1 <= houses.length, heaters.length <= 3 * 10^4
 *     - 1 <= houses[i], heaters[i] <= 10^9
 *
 * Template (python3):
 *     class Solution:
 *         def findRadius(self, houses: List[int], heaters: List[int]) -> int:
 */

use wasm_libs::*;

impl Solution {
    fn find_radius(mut houses: Vec<i32>, mut heaters: Vec<i32>) -> i32 {
        houses.sort();
        heaters.sort();
        let mut result = 0;
        let mut j = 0;
        for i in 0..houses.len() {
            while j + 1 < heaters.len() && (houses[i] - heaters[j]).abs() >= (houses[i] - heaters[j + 1]).abs() {
                j += 1;
            }
            let d = (houses[i] - heaters[j]).abs();
            if d > result { result = d; }
        }
        result
    }
}

struct Solution;

fn main() {
    let houses = read_ints();
    let heaters = read_ints();
    write_int(Solution::find_radius(houses, heaters));
    std::process::exit(0);
}
