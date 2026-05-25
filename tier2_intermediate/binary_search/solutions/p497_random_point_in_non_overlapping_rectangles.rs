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
 *     - -109 <= ai < xi <= 109
 *     - -109 <= bi < yi <= 109
 *     - xi - ai <= 2000
 *     - yi - bi <= 2000
 *     - All the rectangles do not overlap.
 *     - At most 104 calls will be made to pick.
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


fn solve_prefix_sums(rects: &Vec<Vec<i32>>) -> Vec<i32> {
    let mut prefix = Vec::new();
    let mut total = 0;
    for r in rects {
        let area = (r[2] - r[0] + 1) * (r[3] - r[1] + 1);
        total += area;
        prefix.push(total);
    }
    prefix
}

fn main() {
    let tests: Vec<(&str, Vec<Vec<i32>>, Vec<i32>)> = vec![
        ("area sum for two rectangles", vec![vec![-2,-2,1,1],vec![2,2,4,6]], vec![16,31]),
        ("area for single 3x3 rectangle", vec![vec![0,0,2,2]], vec![9]),
        ("single point rectangle", vec![vec![0,0,0,0]], vec![1]),
        ("negative and positive rects same size", vec![vec![-5,-5,-3,-3],vec![1,1,3,3]], vec![9,18]),
        ("different sized rects", vec![vec![1,1,2,2],vec![3,3,5,5]], vec![4,13]),
    ];

    let mut passed = 0;
    println!("\n============================================================");
    println!("  497. Random Point in Non-overlapping Rectangles");
    println!("============================================================");
    for (i, (label, rects, expected)) in tests.iter().enumerate() {
        let got = solve_prefix_sums(rects);
        let ok = got == *expected;
        if ok { passed += 1; }
        println!("  Test {} ({}): {}", i + 1, label, if ok { "PASS" } else { "FAIL" });
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
