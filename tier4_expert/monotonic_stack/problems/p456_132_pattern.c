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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int find132pattern(int *nums, int n)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  456. 132 Pattern\n");
    printf("============================================================\n");

    {
        int nums[] = {1, 2, 3, 4};
        int got = find132pattern(nums, 4);
        if (got == 0) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: 0, Got: %d\n", got); }
    }
    {
        int nums[] = {3, 1, 4, 2};
        int got = find132pattern(nums, 4);
        if (got == 1) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int nums[] = {-1, 3, 2, 0};
        int got = find132pattern(nums, 4);
        if (got == 1) { passed++; printf("  Test 3 (example 3): PASS\n"); }
        else { printf("  Test 3 (example 3): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int nums[] = {1, 2};
        int got = find132pattern(nums, 2);
        if (got == 0) { passed++; printf("  Test 4 (two elements): PASS\n"); }
        else { printf("  Test 4 (two elements): FAIL\n  Expected: 0, Got: %d\n", got); }
    }
    {
        int nums[] = {2, 2, 2};
        int got = find132pattern(nums, 3);
        if (got == 0) { passed++; printf("  Test 5 (all same): PASS\n"); }
        else { printf("  Test 5 (all same): FAIL\n  Expected: 0, Got: %d\n", got); }
    }
    {
        int nums[] = {5, 4, 3, 2, 1};
        int got = find132pattern(nums, 5);
        if (got == 0) { passed++; printf("  Test 6 (strictly decreasing): PASS\n"); }
        else { printf("  Test 6 (strictly decreasing): FAIL\n  Expected: 0, Got: %d\n", got); }
    }
    {
        int nums[] = {1, 3, 0, 2};
        int got = find132pattern(nums, 4);
        if (got == 1) { passed++; printf("  Test 7 (pattern near end): PASS\n"); }
        else { printf("  Test 7 (pattern near end): FAIL\n  Expected: 1, Got: %d\n", got); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
