/*
 * P456: 132 Pattern [PREMIUM] (Medium)
 * https://leetcode.com/problems/132-pattern/
 * Topics: Array, Binary Search, Stack, Monotonic Stack, Ordered Set
 * 
 * Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 * Example 1:
 *     Input: nums = [1,2,3,4]
 *     Output: false
 *     Explanation: There is no 132 pattern in the sequence.
 * 
 * Example 2:
 *     Input: nums = [3,1,4,2]
 *     Output: true
 *     Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
 * 
 * Example 3:
 *     Input: nums = [-1,3,2,0]
 *     Output: true
 *     Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 2 * 105
 *     - -109 <= nums[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def find132pattern(self, nums: List[int]) -> bool:
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

bool find132pattern(const std::vector<int> &nums)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct TC { const char *label; std::vector<int> input; bool expected; };
    TC tests[] = {
        {"example 1", {1, 2, 3, 4}, false},
        {"example 2", {3, 1, 4, 2}, true},
        {"example 3", {-1, 3, 2, 0}, true},
        {"two elements", {1, 2}, false},
        {"all same", {2, 2, 2}, false},
        {"strictly decreasing", {5, 4, 3, 2, 1}, false},
        {"pattern near end", {1, 3, 0, 2}, true},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  456. 132 Pattern\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        bool got = find132pattern(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %s, Got: %s\n", tests[i].expected ? "true" : "false", got ? "true" : "false");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
