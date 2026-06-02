/*
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend.
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 *
 * Example 1:
 *     Input: points = [[10,16],[2,8],[1,6],[7,12]]
 *     Output: 2
 *
 * Example 2:
 *     Input: points = [[1,2],[3,4],[5,6],[7,8]]
 *     Output: 4
 *
 * Example 3:
 *     Input: points = [[1,2],[2,3],[3,4],[4,5]]
 *     Output: 2
 *
 * Constraints:
 *     - 1 <= points.length <= 10^5
 *     - points[i].length == 2
 *     - -2^31 <= xstart < xend <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def findMinArrowShots(self, points: List[List[int]]) -> int:
 */

use wasm_libs::*;
use std::io::{self, BufRead};

fn find_min_arrow_shots(points: &mut [(i64, i64)]) -> i32 {
    if points.is_empty() { return 0; }
    points.sort_by_key(|p| p.1);
    let mut arrows = 1i32;
    let mut end = points[0].1;
    for i in 1..points.len() {
        if points[i].0 > end {
            arrows += 1;
            end = points[i].1;
        }
    }
    arrows
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let _cols: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    let mut points: Vec<(i64, i64)> = Vec::new();
    for line in lines {
        let l = line.unwrap();
        let nums: Vec<i64> = l.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        if nums.len() >= 2 {
            points.push((nums[0], nums[1]));
        }
    }
    let result = find_min_arrow_shots(&mut points);
    write_int(result);
}
