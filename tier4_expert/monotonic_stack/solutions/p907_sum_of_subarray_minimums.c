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

#include "io.h"
#include <stdlib.h>

static const long MOD = 1000000007L;

int sumSubarrayMins(int *arr, int n)
{
    long *left = malloc(n * sizeof(long));
    long *right = malloc(n * sizeof(long));
    int *stack = malloc(n * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; i++) {
        while (top >= 0 && arr[stack[top]] >= arr[i]) top--;
        left[i] = (top >= 0) ? (i - stack[top]) : (i + 1);
        stack[++top] = i;
    }

    top = -1;
    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && arr[stack[top]] > arr[i]) top--;
        right[i] = (top >= 0) ? (stack[top] - i) : (n - i);
        stack[++top] = i;
    }

    long total = 0;
    for (int i = 0; i < n; i++) {
        total = (total + arr[i] * left[i] * right[i]) % MOD;
    }

    free(left);
    free(right);
    free(stack);
    return (int)total;
}

int main(void)
{
    int n;
    int *arr = read_ints(&n);
    write_int(sumSubarrayMins(arr, n));
    free(arr);
    return 0;
}
