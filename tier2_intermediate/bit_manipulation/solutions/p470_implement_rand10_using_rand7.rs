/*
 * P470: Implement Rand10() Using Rand7() [PREMIUM] (Medium)
 * https://leetcode.com/problems/implement-rand10-using-rand7/
 * Topics: Math, Rejection Sampling, Randomized, Probability and Statistics
 *
 * Given the API rand7() that generates a uniform random integer in the range [1, 7], write a function rand10() that generates a uniform random integer in the range [1, 10]. You can only call the API rand7(), and you shouldn't call any other API. Please do not use a language's built-in random API.
 * Each test case will have one internal argument n, the number of times that your implemented function rand10() will be called while testing. Note that this is not an argument passed to rand10().
 * Follow up:
 * Example 1:
 *     Input: n = 1
 *     Output: [2]
 *
 * Example 2:
 *     Input: n = 2
 *     Output: [2,8]
 *
 * Example 3:
 *     Input: n = 3
 *     Output: [3,8,10]
 *
 * Constraints:
 *     - 1 <= n <= 105
 *
 * Template (python3):
 *     # The rand7() API is already defined for you.
 *     # def rand7():
 *     # @return a random integer in the range 1 to 7
 *
 *     class Solution:
 *         def rand10(self):
 *             '''
 *             :rtype: int
 *             '''
 */

#[allow(unused_imports)]
use rstest;

static mut RNG_STATE: u64 = 12345;

fn rand7() -> i32 {
    unsafe {
        RNG_STATE = RNG_STATE.wrapping_mul(1103515245).wrapping_add(12345);
        ((RNG_STATE >> 16) % 7 + 1) as i32
    }
}

fn rand10() -> i32 {
    loop {
        let row = rand7();
        let col = rand7();
        let idx = (row - 1) * 7 + col;
        if idx <= 40 {
            return (idx - 1) % 10 + 1;
        }
    }
}

fn main() {
    struct TestCase {
        label: &'static str,
        input: i32,
    }

    let tests: &[TestCase] = &[
        TestCase { label: "generates 5 values in range [1, 10]", input: 5 },
        TestCase { label: "single value", input: 1 },
        TestCase { label: "100 values", input: 100 },
    ];

    println!("\n============================================================");
    println!("  470. Implement Rand10() Using Rand7()");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let mut ok = true;
        for _ in 0..tc.input {
            let v = rand10();
            if v < 1 || v > 10 {
                ok = false;
                break;
            }
        }
        if ok {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: all values in [1, 10]");
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
