/*
 * P398: Random Pick Index [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-pick-index/
 * Topics: Hash Table, Math, Reservoir Sampling, Randomized
 * 
 * Given an integer array nums with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "pick", "pick", "pick"]
 *     [[[1, 2, 3, 3, 3]], [3], [1], [3]]
 *     Output
 *     [null, 4, 0, 2]
 * 
 *     Explanation
 *     Solution solution = new Solution([1, 2, 3, 3, 3]);
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 *     solution.pick(1); // It should return 0. Since in the array only nums[0] is equal to 1.
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -231 <= nums[i] <= 231 - 1
 *     - target is an integer from nums.
 *     - At most 104 calls will be made to pick.
 * 
 * Template (python3):
 *     class Solution:
 * 
 *         def __init__(self, nums: List[int]):
 * 
 * 
 *         def pick(self, target: int) -> int:
 * 
 * 
 * 
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(nums)
 *     # param_1 = obj.pick(target)
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <vector>

std::vector<int> pickIndex(const std::vector<int> &nums, int target)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct {
        const char *label;
        std::vector<int> input;
        int target;
        std::vector<int> expected;
    } tests[] = {
        {"returns valid indices for target 3", {1, 2, 3, 3, 3}, 3, {2, 3, 4}},
        {"returns valid indices for target 1", {1, 2, 3, 3, 3}, 1, {0}},
        {"single element array",              {5},              5, {0}},
        {"non-contiguous duplicates",         {1, 2, 1, 2, 1}, 1, {0, 2, 4}},
        {"negative numbers with duplicates",  {-1, -2, -1, -3, -1}, -1, {0, 2, 4}},
        {"all same elements",                 {1, 1, 1, 1, 1}, 1, {0, 1, 2, 3, 4}},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  398. Random Pick Index\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        std::vector<int> got = pickIndex(tests[i].input, tests[i].target);
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
