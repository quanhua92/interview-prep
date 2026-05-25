/*
 * P70: Climbing Stairs (Easy)
 * https://leetcode.com/problems/climbing-stairs/
 * Topics: Math, Dynamic Programming, Memoization
 * 
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * 
 * Example 1:
 *     Input: n = 2
 *     Output: 2
 *     Explanation: There are two ways to climb to the top.
 *     1. 1 step + 1 step
 *     2. 2 steps
 * 
 * Example 2:
 *     Input: n = 3
 *     Output: 3
 *     Explanation: There are three ways to climb to the top.
 *     1. 1 step + 1 step + 1 step
 *     2. 1 step + 2 steps
 *     3. 2 steps + 1 step
 * 
 * Constraints:
 *     - 1 <= n <= 45
 * 
 * Hints:
 *     - To reach nth step, what could have been your previous steps? (Think about the step sizes)
 * 
 * Template (python3):
 *     class Solution:
 *         def climbStairs(self, n: int) -> int:
 * 
 * Hint: This is essentially Fibonacci -- each step depends on the two before it.
 */
#include "cpptest.h"

int climbStairs(int n) {
    /* TODO: Implement */
    return 0;
}

int main() {
    struct { const char *label; int n; int expected; } tests[] = {
        {"example 1", 2, 2},
        {"example 2", 3, 3},
        {"base case", 1, 1},
        {"larger", 10, 89},
        {"max constraint", 45, 1836311903},
        {"n=4", 4, 5},
        {"n=5", 5, 8},
        {"n=6", 6, 13},
        {"n=20", 20, 10946},
        {"near max constraint", 44, 1134903170},
    };
    int tn = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < tn; i++) {
        int got = climbStairs(tests[i].n);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, tn);
    return passed == tn ? 0 : 1;
}
