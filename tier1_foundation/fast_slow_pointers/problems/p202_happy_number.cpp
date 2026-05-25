/*
 * P202: Happy Number (Easy)
 * https://leetcode.com/problems/happy-number/
 * Topics: Hash Table, Math, Two Pointers
 * 
 * Write an algorithm to determine if a number n is happy.
 * A happy number is a number defined by the following process:
 * Return true if n is a happy number, and false if not.
 * 
 * Example 1:
 *     Input: n = 19
 *     Output: true
 *     Explanation:
 *     12 + 92 = 82
 *     82 + 22 = 68
 *     62 + 82 = 100
 *     12 + 02 + 02 = 1
 * 
 * Example 2:
 *     Input: n = 2
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= n <= 231 - 1
 * 
 * Template (python3):
 *     class Solution:
 *         def isHappy(self, n: int) -> bool:
 * 
 * Hint: Use fast and slow pointers on the sequence of sum-of-squared-digits.
 */
#include "cpptest.h"

static int get_next(int num)
{
    /* TODO: Implement */
    return 0;
}

bool isHappy(int n)
{
    /* TODO: Implement */
    return 0;
}

void __attribute__((unused)) _use_harness_fns(void)
{
    /* TODO: Implement */
    return 0;
}

int main()
{
    TestCase tests[] = {
        {"example 1", {}, 19, {1}},
        {"example 2", {}, 2, {0}},
        {"already happy", {}, 1, {1}},
        {"small happy number", {}, 7, {1}},
        {"enters 4-16 cycle", {}, 4, {0}},
        {"power of 10", {}, 100, {1}},
        {"large unhappy number", {}, 999999999, {0}},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = isHappy(tests[i].target);
        if (got == tests[i].expected[0]) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
            printf("    Expected: %d\n    Got:      %d\n",
                   tests[i].expected[0], got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
