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

#include "io.h"
#include <stdlib.h>

void nextGreaterElements(int *nums, int n, int *result)
{
    int *stack = malloc(n * sizeof(int));
    int top = -1;
    for (int i = 0; i < n; i++) result[i] = -1;
    for (int i = 0; i < 2 * n; i++) {
        int idx = i % n;
        while (top >= 0 && nums[stack[top]] < nums[idx]) {
            result[stack[top--]] = nums[idx];
        }
        if (i < n) stack[++top] = idx;
    }
    free(stack);
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    int *result = malloc(n * sizeof(int));
    nextGreaterElements(nums, n, result);
    write_ints(result, n);
    free(result);
    free(nums);
    return 0;
}
