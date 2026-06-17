/*
 * P497: Random Point in Non-overlapping Rectangles [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/
 * Topics: Array, Math, Binary Search, Reservoir Sampling, Prefix Sum, Ordered Set, Randomized
 *
 * You are given an array of non-overlapping axis-aligned rectangles rects where rects[i] = [ai, bi, xi, yi] indicates that (ai, bi) is the bottom-left corner point of the ith rectangle and (xi, yi) is the top-right corner point of the ith rectangle. Design an algorithm to pick a random integer point inside the space covered by one of the given rectangles. A point on the perimeter of a rectangle is included in the space covered by the rectangle.
 * Any integer point inside the space covered by one of the given rectangles should be equally likely to be returned.
 * Note that an integer point is a point that has integer coordinates.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "pick", "pick", "pick", "pick", "pick"]
 *     [[[[-2, -2, 1, 1], [2, 2, 4, 6]]], [], [], [], [], []]
 *     Output
 *     [null, [1, -2], [1, -1], [-1, -2], [-2, -2], [0, 0]]
 *
 *     Explanation
 *     Solution solution = new Solution([[-2, -2, 1, 1], [2, 2, 4, 6]]);
 *     solution.pick(); // return [1, -2]
 *     solution.pick(); // return [1, -1]
 *     solution.pick(); // return [-1, -2]
 *     solution.pick(); // return [-2, -2]
 *     solution.pick(); // return [0, 0]
 *
 * Constraints:
 *     - 1 <= rects.length <= 100
 *     - rects[i].length == 4
 *     - -10^9 <= ai < xi <= 10^9
 *     - -10^9 <= bi < yi <= 10^9
 *     - xi - ai <= 2000
 *     - yi - bi <= 2000
 *     - All the rectangles do not overlap.
 *     - At most 10^4 calls will be made to pick.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, rects: List[List[int]]):
 *
 *
 *         def pick(self) -> List[int]:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(rects)
 *     # param_1 = obj.pick()
 */

use wasm_libs::*;

struct Solution {
    rects: Vec<Vec<i32>>,
    prefix: Vec<i32>,
    total: i32,
}

impl Solution {
    fn new(rects: Vec<Vec<i32>>) -> Self {
        let mut prefix = Vec::new();
        let mut total: i32 = 0;
        for r in &rects {
            total += (r[2] - r[0] + 1) * (r[3] - r[1] + 1);
            prefix.push(total);
        }
        Solution { rects, prefix, total }
    }

    fn pick(&self) -> Vec<i32> {
        let t = 42 % self.total.max(1);
        let mut lo = 0;
        let mut hi = self.prefix.len() - 1;
        while lo < hi {
            let mid = (lo + hi) / 2;
            if self.prefix[mid] > t {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        let r = &self.rects[lo];
        let x1 = r[0];
        let y1 = r[1];
        let x2 = r[2];
        let y2 = r[3];
        let w = x2 - x1 + 1;
        let h = y2 - y1 + 1;
        vec![x1 + 42 % w, y1 + 17 % h]
    }
}

fn solve(rects: Vec<Vec<i32>>) -> Vec<i32> {
    Solution::new(rects).pick()
}

fn main() {
    let n = read_int() as usize;
    let mut rects: Vec<Vec<i32>> = Vec::new();
    for _ in 0..n {
        rects.push(read_ints());
    }
    write_ints(&solve(rects));
    std::process::exit(0);
}
