/*
 * P478: Generate Random Point in a Circle [PREMIUM] (Medium)
 * https://leetcode.com/problems/generate-random-point-in-a-circle/
 * Topics: Math, Geometry, Rejection Sampling, Randomized
 *
 * Given the radius and the position of the center of a circle, implement the function randPoint which generates a uniform random point inside the circle.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "randPoint", "randPoint", "randPoint"]
 *     [[1.0, 0.0, 0.0], [], [], []]
 *     Output
 *     [null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]
 *
 *     Explanation
 *     Solution solution = new Solution(1.0, 0.0, 0.0);
 *     solution.randPoint(); // return [-0.02493, -0.38077]
 *     solution.randPoint(); // return [0.82314, 0.38945]
 *     solution.randPoint(); // return [0.36572, 0.17248]
 *
 * Constraints:
 *     - 0 < radius <= 108
 *     - -107 <= x_center, y_center <= 107
 *     - At most 3 * 104 calls will be made to randPoint.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, radius: float, x_center: float, y_center: float):
 *
 *
 *         def randPoint(self) -> List[float]:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(radius, x_center, y_center)
 *     # param_1 = obj.randPoint()
 */

use wasm_libs::*;
use std::io::{self, Write};

fn main() {
    let line = read_line();
    let parts: Vec<&str> = line.split_whitespace().collect();
    let radius: f64 = parts[0].parse().unwrap();
    let x_center: f64 = parts[1].parse().unwrap();
    let y_center: f64 = parts[2].parse().unwrap();
    let count = read_int();

    let state = std::time::SystemTime::now()
        .duration_since(std::time::UNIX_EPOCH)
        .map(|d| d.as_nanos() as u64)
        .unwrap_or(12345);
    let mut rng_state = state;

    let mut out = io::stdout().lock();
    for _ in 0..count {
        loop {
            rng_state = rng_state.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);
            let ux = (rng_state >> 11) as f64 / (1u64 << 53) as f64;
            rng_state = rng_state.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);
            let uy = (rng_state >> 11) as f64 / (1u64 << 53) as f64;
            let x = ux * 2.0 - 1.0;
            let y = uy * 2.0 - 1.0;
            if x * x + y * y <= 1.0 {
                writeln!(out, "{:.6} {:.6}", x_center + x * radius, y_center + y * radius).unwrap();
                break;
            }
        }
    }
    std::process::exit(0);
}
