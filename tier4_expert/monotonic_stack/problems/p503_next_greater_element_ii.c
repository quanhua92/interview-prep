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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *nextGreaterElements(int *nums, int n, int *return_size)
{
    /* TODO: Implement */
    return 0;
}

static int arr_eq(const int *a, int an, const int *b, int bn)
{
    /* TODO: Implement */
    return 0;
}

static void print_arr(const int *a, int n)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    int passed = 0, total = 6;
    printf("\n============================================================\n");
    printf("  503. Next Greater Element II\n");
    printf("============================================================\n");

    {
        int nums[] = {1, 2, 1};
        int exp[] = {2, -1, 2};
        int ret = 0;
        int *got = nextGreaterElements(nums, 3, &ret);
        if (arr_eq(got, ret, exp, 3)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: "); print_arr(exp, 3); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1, 2, 3, 4, 3};
        int exp[] = {2, 3, 4, -1, 4};
        int ret = 0;
        int *got = nextGreaterElements(nums, 5, &ret);
        if (arr_eq(got, ret, exp, 5)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: "); print_arr(exp, 5); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {5};
        int exp[] = {-1};
        int ret = 0;
        int *got = nextGreaterElements(nums, 1, &ret);
        if (arr_eq(got, ret, exp, 1)) { passed++; printf("  Test 3 (single element): PASS\n"); }
        else { printf("  Test 3 (single element): FAIL\n  Expected: "); print_arr(exp, 1); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {2, 2, 2};
        int exp[] = {-1, -1, -1};
        int ret = 0;
        int *got = nextGreaterElements(nums, 3, &ret);
        if (arr_eq(got, ret, exp, 3)) { passed++; printf("  Test 4 (all same): PASS\n"); }
        else { printf("  Test 4 (all same): FAIL\n  Expected: "); print_arr(exp, 3); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {5, 4, 3, 2};
        int exp[] = {-1, 5, 5, 5};
        int ret = 0;
        int *got = nextGreaterElements(nums, 4, &ret);
        if (arr_eq(got, ret, exp, 4)) { passed++; printf("  Test 5 (strictly decreasing wraps): PASS\n"); }
        else { printf("  Test 5 (strictly decreasing wraps): FAIL\n  Expected: "); print_arr(exp, 4); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {-3, -2, -1};
        int exp[] = {-2, -1, -1};
        int ret = 0;
        int *got = nextGreaterElements(nums, 3, &ret);
        if (arr_eq(got, ret, exp, 3)) { passed++; printf("  Test 6 (with negatives): PASS\n"); }
        else { printf("  Test 6 (with negatives): FAIL\n  Expected: "); print_arr(exp, 3); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
