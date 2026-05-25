/*
 * P391: Perfect Rectangle [PREMIUM] (Hard)
 * https://leetcode.com/problems/perfect-rectangle/
 * Topics: Array, Hash Table, Math, Geometry, Line Sweep
 *
 * Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
 * Return true if all the rectangles together form an exact cover of a rectangular region.
 * Example 1:
 *     Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
 *     Output: true
 *     Explanation: All 5 rectangles together form an exact cover of a rectangular region.
 *
 * Example 2:
 *     Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
 *     Output: false
 *     Explanation: Because there is a gap between the two rectangular regions.
 *
 * Example 3:
 *     Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
 *     Output: false
 *     Explanation: Because two of the rectangles overlap with each other.
 *
 * Constraints:
 *     - 1 <= rectangles.length <= 2 * 104
 *     - rectangles[i].length == 4
 *     - -105 <= xi < ai <= 105
 *     - -105 <= yi < bi <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
 */


use std::collections::HashSet;
use std::process::exit;

fn is_rectangle_cover(rectangles: &Vec<Vec<i32>>) -> bool
{
    let mut corners: HashSet<(i64, i64)> = HashSet::new();
    let mut total_area: i64 = 0;
    let mut min_x = 200000_i64;
    let mut min_y = 200000_i64;
    let mut max_x = -200000_i64;
    let mut max_y = -200000_i64;

    for r in rectangles {
        let x1 = r[0] as i64;
        let y1 = r[1] as i64;
        let x2 = r[2] as i64;
        let y2 = r[3] as i64;
        min_x = min_x.min(x1);
        min_y = min_y.min(y1);
        max_x = max_x.max(x2);
        max_y = max_y.max(y2);
        total_area += (x2 - x1) * (y2 - y1);

        let pts: [(i64, i64); 4] = [(x1,y1),(x1,y2),(x2,y1),(x2,y2)];
        for p in &pts {
            if !corners.remove(p) {
                corners.insert(*p);
            }
        }
    }

    if corners.len() != 4 {
        return false;
    }
    let expected: HashSet<(i64, i64)> = [
        (min_x, min_y), (min_x, max_y), (max_x, min_y), (max_x, max_y)
    ].iter().cloned().collect();
    if corners != expected {
        return false;
    }

    total_area == (max_x - min_x) * (max_y - min_y)
}

struct RectTC {
    label: &'static str,
    rects: Vec<Vec<i32>>,
    expected: bool,
}

fn main()
{
    let tests: Vec<RectTC> = vec![
        RectTC { label: "example 1", rects: vec![vec![1,1,3,3],vec![3,1,4,2],vec![3,2,4,4],vec![1,3,2,4],vec![2,3,3,4]], expected: true },
        RectTC { label: "example 2", rects: vec![vec![1,1,2,3],vec![1,3,2,4],vec![3,1,4,2],vec![3,2,4,4]], expected: false },
        RectTC { label: "example 3", rects: vec![vec![1,1,3,3],vec![3,1,4,2],vec![1,3,2,4],vec![2,2,4,4]], expected: false },
        RectTC { label: "single rectangle", rects: vec![vec![0,0,1,1]], expected: true },
        RectTC { label: "two rects side by side", rects: vec![vec![0,0,1,2],vec![1,0,2,2]], expected: true },
        RectTC { label: "overlapping rectangles", rects: vec![vec![0,0,2,2],vec![1,1,3,3]], expected: false },
    ];

    println!("\n============================================================");
    println!("  391. Perfect Rectangle");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = is_rectangle_cover(&tc.rects);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    if passed == tests.len() { exit(0); } else { exit(1); }
}
