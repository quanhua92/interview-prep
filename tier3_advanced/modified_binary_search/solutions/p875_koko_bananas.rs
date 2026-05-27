/*
 * P875: Koko Eating Bananas (Medium)
 * https://leetcode.com/problems/koko-eating-bananas/
 * Topics: Array, Binary Search
 *
 * Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
 * Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
 * Return the minimum integer k such that she can eat all the bananas within h hours.
 *
 * Example 1:
 *     Input: piles = [3,6,7,11], h = 8
 *     Output: 4
 *
 * Example 2:
 *     Input: piles = [30,11,23,4,20], h = 5
 *     Output: 30
 *
 * Example 3:
 *     Input: piles = [30,11,23,4,20], h = 6
 *     Output: 23
 *
 * Constraints:
 *     - 1 <= piles.length <= 104
 *     - piles.length <= h <= 109
 *     - 1 <= piles[i] <= 109
 *
 * Template (python3):
 *     class Solution:
 *         def minEatingSpeed(self, piles: List[int], h: int) -> int:
 *
 * Hint: Binary search on the eating speed, computing total hours for each candidate.
 */

use wasm_libs::*;

fn hours_needed(piles: &[i32], k: i64) -> i64 {
    piles.iter().map(|&p| ((p as i64 + k - 1) / k) as i64).sum()
}

fn min_eating_speed(piles: &[i32], h: i64) -> i64 {
    let mut left: i64 = 1;
    let mut right: i64 = *piles.iter().max().unwrap() as i64;
    while left < right {
        let mid = left + (right - left) / 2;
        if hours_needed(piles, mid) <= h {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    left
}

fn main() {
    let piles = read_ints();
    let h = read_int();
    write_int(min_eating_speed(&piles, h as i64) as i32);
    std::process::exit(0);
}
