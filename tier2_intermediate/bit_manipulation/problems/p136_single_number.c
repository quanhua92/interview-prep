/*
 * P136: Single Number (Easy)
 * https://leetcode.com/problems/single-number/
 * Topics: Array, Bit Manipulation
 * 
 * Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 * 
 * Example 1:
 *     Input: nums = [2,2,1]
 *     Output: 1
 * 
 * Example 2:
 *     Input: nums = [4,1,2,1,2]
 *     Output: 4
 * 
 * Example 3:
 *     Input: nums = [1]
 *     Output: 1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 3 * 104
 *     - -3 * 104 <= nums[i] <= 3 * 104
 *     - Each element in the array appears twice except for one element which appears only once.
 * 
 * Hints:
 *     - Think about the XOR (^) operator's property.
 * 
 * Template (python3):
 *     class Solution:
 *         def singleNumber(self, nums: List[int]) -> int:
 * 
 * Hint: XOR all numbers — pairs cancel out, leaving the single number.
 */
#include "ctest.h"

static int singleNumber(const int *nums, int numsSize) {
    abort();
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    struct { const char *label; int input[9]; int input_n; int expected; } tests[] = {
        {"example 1", {2, 2, 1}, 3, 1},
        {"example 2", {4, 1, 2, 1, 2}, 5, 4},
        {"single element", {1}, 1, 1},
        {"negative numbers", {-1, -1, -2}, 3, -2},
        {"zero pairs", {0, 0, 1}, 3, 1},
        {"single negative", {-1}, 1, -1},
        {"many pairs", {7, 7, 7, 7, 99, 3, 3, 4, 4}, 9, 99},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  136. Single Number\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        int got = singleNumber(tests[i].input, tests[i].input_n);
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
