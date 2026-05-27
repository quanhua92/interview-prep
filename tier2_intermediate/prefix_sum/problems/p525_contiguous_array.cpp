/*
 * P525: Contiguous Array [PREMIUM] (Medium)
 * https://leetcode.com/problems/contiguous-array/
 * Topics: Array, Hash Table, Prefix Sum
 *
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
 * Example 1:
 *     Input: nums = [0,1]
 *     Output: 2
 *     Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
 *
 * Example 2:
 *     Input: nums = [0,1,0]
 *     Output: 2
 *     Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
 *
 * Example 3:
 *     Input: nums = [0,1,1,1,1,1,0,0,0]
 *     Output: 6
 *     Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal number of 0 and 1.
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - nums[i] is either 0 or 1.
 *
 * Template (python3):
 *     class Solution:
 *         def findMaxLength(self, nums: List[int]) -> int:
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <vector>

int find_max_length(const std::vector<int>& nums)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        std::vector<int> input;
        int expected;
    } tests[] = {
        {"example 1",       {0, 1},                     2},
        {"example 2",       {0, 1, 0},                  2},
        {"example 3",       {0, 1, 1, 1, 1, 1, 0, 0, 0}, 6},
        {"single element",  {1},                         0},
        {"balanced halves", {0, 0, 0, 0, 1, 1, 1, 1},    8},
        {"middle balanced", {0, 0, 1, 0, 0, 0, 1, 1},    6},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  525. Contiguous Array\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = find_max_length(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
