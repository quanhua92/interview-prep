/*
 * P238: Product of Array Except Self (Medium)
 * https://leetcode.com/problems/product-of-array-except-self/
 * Topics: Array, Prefix Sum
 *
 * Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 *
 * Example 1:
 *     Input: nums = [1,2,3,4]
 *     Output: [24,12,8,6]
 *
 * Example 2:
 *     Input: nums = [-1,1,0,-3,3]
 *     Output: [0,0,9,0,0]
 *
 * Constraints:
 *     - 2 <= nums.length <= 105
 *     - -30 <= nums[i] <= 30
 *     - The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
 *
 * Follow up:
 *     - Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)
 *
 * Hints:
 *     - Think how you can efficiently utilize prefix and suffix products to calculate the product of all elements except self for each index. Can you pre-compute the prefix and suffix products in linear time to avoid redundant calculations?
 *     - Can you minimize additional space usage by reusing memory or modifying the input array to store intermediate results?
 *
 * Template (python3):
 *     class Solution:
 *         def productExceptSelf(self, nums: List[int]) -> List[int]:
 *
 * Hint: Build left and right product arrays, then combine.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <vector>

std::vector<int> product_except_self(const std::vector<int>& nums)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        std::vector<int> input;
        std::vector<int> expected;
    } tests[] = {
        {"example 1",             {1, 2, 3, 4},       {24, 12, 8, 6}},
        {"example 2",             {-1, 1, 0, -3, 3},  {0, 0, 9, 0, 0}},
        {"two elements",          {1, 2},              {2, 1}},
        {"all ones",              {1, 1, 1},           {1, 1, 1}},
        {"all negatives",         {-1, -1, -1},        {1, 1, 1}},
        {"two elements negative", {1, -1},             {-1, 1}},
        {"all zeros",             {0, 0, 0, 0},        {0, 0, 0, 0}},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  238. Product of Array Except Self\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        std::vector<int> got = product_except_self(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
