/*
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 */


use std::io::{self, BufRead};

fn find_min_arrow_shots(points: &mut [(i64, i64)]) -> i32 {
    todo!()
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
    wasm_libs::write_int(result);
}
