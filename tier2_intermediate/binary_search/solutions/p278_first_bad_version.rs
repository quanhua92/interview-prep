/*
 * P278: First Bad Version (Easy)
 * https://leetcode.com/problems/first-bad-version/
 * Topics: Binary Search, Interactive
 *
 * You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
 * You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
 *
 * Example 1:
 *     Input: n = 5, bad = 4
 *     Output: 4
 *     Explanation:
 *     call isBadVersion(3) -> false
 *     call isBadVersion(5) -> true
 *     call isBadVersion(4) -> true
 *     Then 4 is the first bad version.
 *
 * Example 2:
 *     Input: n = 1, bad = 1
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= bad <= n <= 231 - 1
 *
 * Template (python3):
 *     # The isBadVersion API is already defined for you.
 *     # def isBadVersion(version: int) -> bool:
 *
 *     class Solution:
 *         def firstBadVersion(self, n: int) -> int:
 *
 * Hint: Binary search for the leftmost version where is_bad is True.
 */


fn first_bad_version(n: i64, bad: i64) -> i64 {
    let mut left: i64 = 1;
    let mut right: i64 = n;
    while left < right {
        let mid = left + (right - left) / 2;
        if mid >= bad {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    left
}

fn main() {
    let tests: Vec<(&str, i64, i64, i64)> = vec![
        ("example 1", 5, 4, 4),
        ("single version, bad", 1, 1, 1),
        ("last version is bad", 3, 3, 3),
        ("middle version is bad", 10, 7, 7),
        ("first version is bad", 2, 1, 1),
        ("large n, last is bad", 100, 100, 100),
        ("large n, first is bad", 100000, 1, 1),
        ("small n last bad", 2, 2, 2),
        ("large n near end", 1000000, 999999, 999999),
        ("max int overflow safe", 2147483647, 1, 1),
    ];

    let mut passed = 0;
    println!("\n============================================================");
    println!("  278. First Bad Version");
    println!("============================================================");
    for (i, (label, n, bad, expected)) in tests.iter().enumerate() {
        let got = first_bad_version(*n, *bad);
        let ok = got == *expected;
        if ok { passed += 1; }
        println!("  Test {} ({}): {}", i + 1, label, if ok { "PASS" } else { "FAIL" });
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
