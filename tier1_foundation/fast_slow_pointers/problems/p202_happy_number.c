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
#include "ctest.h"

static int get_next(int num)
{
    abort();
}

int isHappy(int n)
{
    abort();
}

void __attribute__((unused)) _use_harness_fns(void)
{
    abort();
}

int main(void)
{
    TestCase tests[] = {
        {.label = "example 1", .target = 19, .expected = {1}, .expected_n = 1},
        {.label = "example 2", .target = 2, .expected = {0}, .expected_n = 1},
        {.label = "already happy", .target = 1, .expected = {1}, .expected_n = 1},
        {.label = "small happy number", .target = 7, .expected = {1}, .expected_n = 1},
        {.label = "enters 4-16 cycle", .target = 4, .expected = {0}, .expected_n = 1},
        {.label = "power of 10", .target = 100, .expected = {1}, .expected_n = 1},
        {.label = "large unhappy number", .target = 999999999, .expected = {0}, .expected_n = 1},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = isHappy(tests[i].target);
        if (got == tests[i].expected[0]) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n",
                   tests[i].expected[0], got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
