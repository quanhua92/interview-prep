/*
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 * 
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
 * 
 * Example 1:
 *     Input: arr = [3,1,2,4]
 *     Output: 17
 *     Explanation:
 *     Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
 *     Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
 *     Sum is 17.
 * 
 * Example 2:
 *     Input: arr = [11,81,94,43,3]
 *     Output: 444
 * 
 * Constraints:
 *     - 1 <= arr.length <= 3 * 104
 *     - 1 <= arr[i] <= 3 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def sumSubarrayMins(self, arr: List[int]) -> int:
 * 
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const long MOD = 1000000007L;

int sumSubarrayMins(int *arr, int n)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  907. Sum of Subarray Minimums\n");
    printf("============================================================\n");

    {
        int a[] = {3, 1, 2, 4};
        int got = sumSubarrayMins(a, 4);
        if (got == 17) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: 17, Got: %d\n", got); }
    }
    {
        int a[] = {11, 81, 94, 43, 3};
        int got = sumSubarrayMins(a, 5);
        if (got == 444) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: 444, Got: %d\n", got); }
    }
    {
        int a[] = {1};
        int got = sumSubarrayMins(a, 1);
        if (got == 1) { passed++; printf("  Test 3 (single element): PASS\n"); }
        else { printf("  Test 3 (single element): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int a[] = {2, 1};
        int got = sumSubarrayMins(a, 2);
        if (got == 4) { passed++; printf("  Test 4 (two elements): PASS\n"); }
        else { printf("  Test 4 (two elements): FAIL\n  Expected: 4, Got: %d\n", got); }
    }
    {
        int a[] = {3, 3, 3};
        int got = sumSubarrayMins(a, 3);
        if (got == 18) { passed++; printf("  Test 5 (all same): PASS\n"); }
        else { printf("  Test 5 (all same): FAIL\n  Expected: 18, Got: %d\n", got); }
    }
    {
        int a[] = {1, 2, 3};
        int got = sumSubarrayMins(a, 3);
        if (got == 10) { passed++; printf("  Test 6 (strictly increasing): PASS\n"); }
        else { printf("  Test 6 (strictly increasing): FAIL\n  Expected: 10, Got: %d\n", got); }
    }
    {
        int a[] = {3, 2, 1};
        int got = sumSubarrayMins(a, 3);
        if (got == 10) { passed++; printf("  Test 7 (strictly decreasing): PASS\n"); }
        else { printf("  Test 7 (strictly decreasing): FAIL\n  Expected: 10, Got: %d\n", got); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
