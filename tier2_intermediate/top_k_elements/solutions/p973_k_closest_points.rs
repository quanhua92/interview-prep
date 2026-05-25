/*
 * P973: K Closest Points to Origin (Medium)
 * https://leetcode.com/problems/k-closest-points-to-origin/
 * Topics: Array, Math, Divide and Conquer, Geometry, Sorting, Heap (Priority Queue), Quickselect
 *
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
 * The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
 * You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).
 *
 * Example 1:
 *     Input: points = [[1,3],[-2,2]], k = 1
 *     Output: [[-2,2]]
 *     Explanation:
 *     The distance between (1, 3) and the origin is sqrt(10).
 *     The distance between (-2, 2) and the origin is sqrt(8).
 *     Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 *     We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
 *
 * Example 2:
 *     Input: points = [[3,3],[5,-1],[-2,4]], k = 2
 *     Output: [[3,3],[-2,4]]
 *     Explanation: The answer [[-2,4],[3,3]] would also be accepted.
 *
 * Constraints:
 *     - 1 <= k <= points.length <= 104
 *     - -104 <= xi, yi <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
 *
 * Hint: Use a max-heap of size k keyed by negative distance squared.
 */


fn k_closest(points: &mut Vec<Vec<i32>>, k: i32) -> Vec<Vec<i32>> {
    let k = k as usize;
    points.sort_by(|a, b| {
        let da = a[0] * a[0] + a[1] * a[1];
        let db = b[0] * b[0] + b[1] * b[1];
        da.cmp(&db).then(a[0].cmp(&b[0])).then(a[1].cmp(&b[1]))
    });
    let mut result: Vec<Vec<i32>> = points[..k].to_vec();
    result.sort();
    result
}

fn to_pts(flat: &[i32]) -> Vec<Vec<i32>> {
    flat.chunks(2).map(|p| vec![p[0], p[1]]).collect()
}

fn main() {
    struct Case { label: &'static str, flat: &'static [i32], k: i32, exp_flat: &'static [i32] }
    let tests: &[Case] = &[
        Case { label: "example 1", flat: &[1, 3, -2, 2], k: 1, exp_flat: &[-2, 2] },
        Case { label: "example 2 (sorted)", flat: &[3, 3, 5, -1, -2, 4], k: 2, exp_flat: &[-2, 4, 3, 3] },
        Case { label: "origin itself", flat: &[0, 0], k: 1, exp_flat: &[0, 0] },
        Case { label: "tie on distance", flat: &[1, 0, 0, 1, 2, 0], k: 2, exp_flat: &[0, 1, 1, 0] },
        Case { label: "negative coords", flat: &[-1, -1, 2, 2, 3, 3], k: 1, exp_flat: &[-1, -1] },
        Case { label: "two tied closest", flat: &[1, 0, 0, 1, 2, 0], k: 2, exp_flat: &[0, 1, 1, 0] },
        Case { label: "all same point", flat: &[1, 1, 1, 1, 1, 1], k: 2, exp_flat: &[1, 1, 1, 1] },
        Case { label: "origin is closest", flat: &[3, 4, 0, 0, 1, 1], k: 1, exp_flat: &[0, 0] },
    ];

    println!("\n============================================================");
    println!("  973. K Closest Points to Origin");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let mut pts = to_pts(tc.flat);
        let got = k_closest(&mut pts, tc.k);
        let expected = to_pts(tc.exp_flat);
        if got == expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", expected);
            println!("    Got:      {:?}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
