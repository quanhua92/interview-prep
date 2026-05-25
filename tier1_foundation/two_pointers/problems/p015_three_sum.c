/*
 * P15: 3Sum (Medium)
 * https://leetcode.com/problems/3sum/
 * Topics: Array, Two Pointers, Sorting
 * 
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * Notice that the solution set must not contain duplicate triplets.
 * 
 * Example 1:
 *     Input: nums = [-1,0,1,2,-1,-4]
 *     Output: [[-1,-1,2],[-1,0,1]]
 *     Explanation:
 *     nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 *     nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 *     nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 *     The distinct triplets are [-1,0,1] and [-1,-1,2].
 *     Notice that the order of the output and the order of the triplets does not matter.
 * 
 * Example 2:
 *     Input: nums = [0,1,1]
 *     Output: []
 *     Explanation: The only possible triplet does not sum up to 0.
 * 
 * Example 3:
 *     Input: nums = [0,0,0]
 *     Output: [[0,0,0]]
 *     Explanation: The only possible triplet sums up to 0.
 * 
 * Constraints:
 *     - 3 <= nums.length <= 3000
 *     - -105 <= nums[i] <= 105
 * 
 * Hints:
 *     - So, we essentially need to find three numbers x, y, and z such that they add up to the given value. If we fix one of the numbers say x, we are left with the two-sum problem at hand!
 *     - For the two-sum problem, if we fix one of the numbers, say x, we have to scan the entire array to find the next number y, which is value - x where value is the input parameter. Can we change our array somehow so that this search becomes faster?
 *     - The second train of thought for two-sum is, without changing the array, can we use additional space somehow? Like maybe a hash map to speed up the search?
 * 
 * Template (python3):
 *     class Solution:
 *         def threeSum(self, nums: List[int]) -> List[List[int]]:
 * 
 * Hint: Sort, iterate i, nested two pointers for remaining pair, skip duplicates.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmp_int(const void *a, const void *b) {
    /* TODO: Implement */
    return 0;
}

int *threeSum(int *nums, int n, int *return_size)
{
    /* TODO: Implement */
    return 0;
}

static int triplet_cmp(const void *a, const void *b)
{
    /* TODO: Implement */
    return 0;
}

static int results_eq(int *got, int gn, int *exp, int en)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct {
        const char *label;
        int input[8];
        int n;
        int expected[30];
        int expected_triplets;
    } tests[] = {
        {"example 1",             {-1, 0, 1, 2, -1, -4}, 6, {-1, -1, 2, -1, 0, 1}, 2},
        {"no triplets",           {0, 1, 1},              3, {},                     0},
        {"all zeros",             {0, 0, 0},              3, {0, 0, 0},              1},
        {"empty",                 {},                     0, {},                     0},
        {"adjacent duplicate pairs", {-2, 0, 0, 2, 2},   5, {-2, 0, 2},             1},
        {"all identical values",  {0, 0, 0, 0, 0},        5, {0, 0, 0},              1},
        {"skip-i with left/right dup", {-3, -3, 0, 1, 1, 2, 2}, 7, {-3, 1, 2},     1},
        {"triple duplicate",      {-2, 0, 0, 0, 2, 2, 2}, 7, {-2, 0, 2, 0, 0, 0},  2},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  15. 3Sum\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int buf[64];
        memcpy(buf, tests[i].input, tests[i].n * sizeof(int));
        int got_count = 0;
        int *got = threeSum(buf, tests[i].n, &got_count);
        int exp[64];
        memcpy(exp, tests[i].expected, tests[i].expected_triplets * 3 * sizeof(int));
        if (results_eq(got, got_count, exp, tests[i].expected_triplets)) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected %d triplets, got %d\n", tests[i].expected_triplets, got_count);
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
