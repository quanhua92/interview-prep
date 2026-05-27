/*
 * P560: Subarray Sum Equals K (Medium)
 * https://leetcode.com/problems/subarray-sum-equals-k/
 * Topics: Array, Hash Table, Prefix Sum
 *
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * Example 1:
 *     Input: nums = [1,1,1], k = 2
 *     Output: 2
 *
 * Example 2:
 *     Input: nums = [1,2,3], k = 3
 *     Output: 2
 *
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -1000 <= nums[i] <= 1000
 *     - -107 <= k <= 107
 *
 * Hints:
 *     - Will Brute force work here? Try to optimize it.
 *     - Can we optimize it by using some extra space?
 *     - What about storing sum frequencies in a hash table? Will it be useful?
 *     - sum(i,j)=sum(0,j)-sum(0,i), where sum(i,j) represents the sum of all the elements from index i to j-1.
 *
 * Can we use this property to optimize it.
 *
 * Template (python3):
 *     class Solution:
 *         def subarraySum(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a hash map with prefix sums to count subarrays summing to k.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <vector>

int subarray_sum(const std::vector<int>& nums, int k)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        std::vector<int> input;
        int target;
        int expected;
    } tests[] = {
        {"example 1",                {1, 1, 1},     2, 2},
        {"example 2",                {1, 2, 3},     3, 2},
        {"empty array",              {},            0, 0},
        {"single element equals k",  {1},           1, 1},
        {"single element not k",     {1},           2, 0},
        {"negatives with zero sum",  {1, -1, 0},    0, 3},
        {"all zeros",                {0, 0, 0},     0, 6},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  560. Subarray Sum Equals K\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = subarray_sum(tests[i].input, tests[i].target);
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
