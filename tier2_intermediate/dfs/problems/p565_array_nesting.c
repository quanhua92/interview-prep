/*
 * P565: Array Nesting [PREMIUM] (Medium)
 * https://leetcode.com/problems/array-nesting/
 * Topics: Array, Depth-First Search
 * 
 * You are given an integer array nums of length n where nums is a permutation of the numbers in the range [0, n - 1].
 * You should build a set s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... } subjected to the following rule:
 * Return the longest length of a set s[k].
 * Example 1:
 *     Input: nums = [5,4,0,3,1,6,2]
 *     Output: 4
 *     Explanation:
 *     nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
 *     One of the longest sets s[k]:
 *     s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
 * 
 * Example 2:
 *     Input: nums = [0,1,2]
 *     Output: 1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - 0 <= nums[i] < nums.length
 *     - All the values of nums are unique.
 * 
 * Template (python3):
 *     class Solution:
 *         def arrayNesting(self, nums: List[int]) -> int:
 */
#include "ctest.h"

static int arrayNesting(const int *nums, int n) {
    abort();
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    struct { const char *label; int input[7]; int input_n; int expected; } tests[] = {
        {"example 1", {5, 4, 0, 3, 1, 6, 2}, 7, 4},
        {"example 2", {0, 1, 2}, 3, 1},
        {"single element", {0}, 1, 1},
        {"two element cycle", {1, 0}, 2, 2},
        {"full single cycle", {2, 0, 1}, 3, 3},
        {"two separate cycles", {0, 2, 1}, 3, 2},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  565. Array Nesting\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        int got = arrayNesting(tests[i].input, tests[i].input_n);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");

    return passed == n ? 0 : 1;
}
