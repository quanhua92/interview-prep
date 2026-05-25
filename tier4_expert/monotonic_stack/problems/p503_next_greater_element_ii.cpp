/*
 * P503: Next Greater Element II [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-ii/
 * Topics: Array, Stack, Monotonic Stack
 * 
 * Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.
 * The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.
 * Example 1:
 *     Input: nums = [1,2,1]
 *     Output: [2,-1,2]
 *     Explanation: The first 1's next greater number is 2;
 *     The number 2 can't find next greater number.
 *     The second 1's next greater number needs to search circularly, which is also 2.
 * 
 * Example 2:
 *     Input: nums = [1,2,3,4,3]
 *     Output: [2,3,4,-1,4]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -109 <= nums[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElements(self, nums: List[int]) -> List[int]:
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

std::vector<int> nextGreaterElements(const std::vector<int> &nums)
{
    abort();
}

static void print_arr(const std::vector<int> &a)
{
    abort();
}

int main(void)
{
    struct TC { const char *label; std::vector<int> input; std::vector<int> expected; };
    TC tests[] = {
        {"example 1", {1, 2, 1}, {2, -1, 2}},
        {"example 2", {1, 2, 3, 4, 3}, {2, 3, 4, -1, 4}},
        {"single element", {5}, {-1}},
        {"all same", {2, 2, 2}, {-1, -1, -1}},
        {"strictly decreasing wraps", {5, 4, 3, 2}, {-1, 5, 5, 5}},
        {"with negatives", {-3, -2, -1}, {-2, -1, -1}},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  503. Next Greater Element II\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        auto got = nextGreaterElements(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: "); print_arr(tests[i].expected); printf("\n");
            printf("    Got:      "); print_arr(got); printf("\n");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
