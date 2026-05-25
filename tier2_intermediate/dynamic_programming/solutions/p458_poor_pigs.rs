/*
 * P458: Poor Pigs [PREMIUM] (Hard)
 * https://leetcode.com/problems/poor-pigs/
 * Topics: Math, Dynamic Programming, Combinatorics
 *
 * There are buckets buckets of liquid, where exactly one of the buckets is poisonous. To figure out which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die or not. Unfortunately, you only have minutesToTest minutes to determine which bucket is poisonous.
 * You can feed the pigs according to these steps:
 * Given buckets, minutesToDie, and minutesToTest, return the minimum number of pigs needed to figure out which bucket is poisonous within the allotted time.
 * Example 1:
 *     Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
 *     Output: 2
 *     Explanation: We can determine the poisonous bucket as follows:
 *     At time 0, feed the first pig buckets 1 and 2, and feed the second pig buckets 2 and 3.
 *     At time 15, there are 4 possible outcomes:
 *     - If only the first pig dies, then bucket 1 must be poisonous.
 *     - If only the second pig dies, then bucket 3 must be poisonous.
 *     - If both pigs die, then bucket 2 must be poisonous.
 *     - If neither pig dies, then bucket 4 must be poisonous.
 *
 * Example 2:
 *     Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
 *     Output: 2
 *     Explanation: We can determine the poisonous bucket as follows:
 *     At time 0, feed the first pig bucket 1, and feed the second pig bucket 2.
 *     At time 15, there are 2 possible outcomes:
 *     - If either pig dies, then the poisonous bucket is the one it was fed.
 *     - If neither pig dies, then feed the first pig bucket 3, and feed the second pig bucket 4.
 *     At time 30, one of the two pigs must die, and the poisonous bucket is the one it was fed.
 *
 * Constraints:
 *     - 1 <= buckets <= 1000
 *     - 1 <= minutesToDie <= minutesToTest <= 100
 *
 * Hint: What if you only have one shot? Eg. 4 buckets, 15 mins to die, and 15 mins to test.
 * Hint: How many states can we generate with x pigs and T tests?
 * Hint: Find minimum <code>x</code> such that <code>(T+1)^x >= N</code>
 *
 * Template (python3):
 *     class Solution:
 *         def poorPigs(self, buckets: int, minutesToDie: int, minutesToTest: int) -> int:
 */


use rstest;

fn poor_pigs(buckets: i32, minutes_to_die: i32, minutes_to_test: i32) -> i32 {
    let tests = minutes_to_test / minutes_to_die;
    let base = (tests + 1) as i64;
    let target = buckets as i64;
    let mut val: i64 = 1;
    let mut pigs = 0i32;
    while val < target {
        val *= base;
        pigs += 1;
    }
    pigs
}

fn main() {
    struct TC { label: &'static str, buckets: i32, mtd: i32, mtt: i32, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", buckets: 4, mtd: 15, mtt: 15, expected: 2 },
        TC { label: "example 2", buckets: 4, mtd: 15, mtt: 30, expected: 2 },
        TC { label: "single bucket", buckets: 1, mtd: 100, mtt: 100, expected: 0 },
        TC { label: "single test round", buckets: 125, mtd: 1, mtt: 1, expected: 7 },
        TC { label: "large buckets", buckets: 1000, mtd: 15, mtt: 60, expected: 5 },
        TC { label: "medium buckets", buckets: 8, mtd: 15, mtt: 30, expected: 2 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = poor_pigs(tc.buckets, tc.mtd, tc.mtt);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL (expected {}, got {})", i + 1, tc.label, tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
