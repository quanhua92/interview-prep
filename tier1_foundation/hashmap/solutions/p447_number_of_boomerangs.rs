/*
 * P447: Number of Boomerangs [PREMIUM] (Medium)
 * https://leetcode.com/problems/number-of-boomerangs/
 * Topics: Array, Hash Table, Math
 *
 * You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
 * Return the number of boomerangs.
 * Example 1:
 *     Input: points = [[0,0],[1,0],[2,0]]
 *     Output: 2
 *     Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
 *
 * Example 2:
 *     Input: points = [[1,1],[2,2],[3,3]]
 *     Output: 2
 *
 * Example 3:
 *     Input: points = [[1,1]]
 *     Output: 0
 *
 * Constraints:
 *     - n == points.length
 *     - 1 <= n <= 500
 *     - points[i].length == 2
 *     - -10^4 <= xi, yi <= 10^4
 *     - All the points are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def numberOfBoomerangs(self, points: List[List[int]]) -> int:
 */

use wasm_libs::*;
use std::collections::HashMap;

fn number_of_boomerangs(points: &[(i32, i32)]) -> i32 {
    let mut result = 0;
    for i in 0..points.len() {
        let mut dist_count: HashMap<i64, i32> = HashMap::new();
        for j in 0..points.len() {
            if i == j { continue; }
            let dx = (points[i].0 - points[j].0) as i64;
            let dy = (points[i].1 - points[j].1) as i64;
            *dist_count.entry(dx * dx + dy * dy).or_insert(0) += 1;
        }
        for &count in dist_count.values() {
            result += count * (count - 1);
        }
    }
    result
}

fn main() {
    let header = read_ints();
    let n = header[0] as usize;
    let mut points: Vec<(i32, i32)> = Vec::new();
    for _ in 0..n {
        let row = read_ints();
        points.push((row[0], row[1]));
    }
    write_int(number_of_boomerangs(&points));
    std::process::exit(0);
}
