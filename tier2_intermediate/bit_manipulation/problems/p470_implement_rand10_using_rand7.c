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
#include "ctest.h"
#include <stdlib.h>

static unsigned long rng_state = 12345;

static int rand7(void) {
    /* TODO: Implement */
    return 0;
}

static int rand10(void) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    struct { const char *label; int input; } tests[] = {
        {"generates 5 values in range [1, 10]", 5},
        {"single value", 1},
        {"100 values", 100},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  470. Implement Rand10() Using Rand7()\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        int ok = 1;
        for (int j = 0; j < tests[i].input; j++) {
            int v = rand10();
            if (v < 1 || v > 10) { ok = 0; break; }
        }
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: all values in [1, 10]\n");
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");

    return passed == n ? 0 : 1;
}
