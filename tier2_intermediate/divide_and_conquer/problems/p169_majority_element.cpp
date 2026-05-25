/*
 * P169: Majority Element (Easy)
 * https://leetcode.com/problems/majority-element/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Counting
 * 
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
 * 
 * Example 1:
 *     Input: nums = [3,2,3]
 *     Output: 3
 * 
 * Example 2:
 *     Input: nums = [2,2,1,1,1,2,2]
 *     Output: 2
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 5 * 104
 *     - -109 <= nums[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def majorityElement(self, nums: List[int]) -> int:
 * 
 * Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
 */
#include <cstdio>
#include <vector>

int majorityElement(const std::vector<int> &nums)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct {
        const char *label;
        std::vector<int> input;
        int expected;
    } tests[] = {
        {"example 1",       {3, 2, 3},              3},
        {"example 2",       {2, 2, 1, 1, 1, 2, 2},  2},
        {"single element",  {1},                     1},
        {"majority at end", {1, 2, 3, 2, 2},         2},
        {"all same",        {5, 5, 5, 5, 5},         5},
        {"negative majority", {-1, -1, 2},            -1},
        {"two elements",    {3, 3},                  3},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  169. Majority Element\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = majorityElement(tests[i].input);
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
