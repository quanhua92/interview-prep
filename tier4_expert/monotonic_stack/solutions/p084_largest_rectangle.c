/*
 * P84: Largest Rectangle in Histogram (Hard)
 * https://leetcode.com/problems/largest-rectangle-in-histogram/
 * Topics: Array, Stack, Monotonic Stack
 *
 * Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.
 *
 * Example 1:
 *     Input: heights = [2,1,5,6,2,3]
 *     Output: 10
 *     Explanation: The above is a histogram where width of each bar is 1.
 *     The largest rectangle is shown in the red area, which has an area = 10 units.
 *
 * Example 2:
 *     Input: heights = [2,4]
 *     Output: 4
 *
 * Constraints:
 *     - 1 <= heights.length <= 10^5
 *     - 0 <= heights[i] <= 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def largestRectangleArea(self, heights: List[int]) -> int:
 *
 * Hint: Use a monotonic increasing stack with a sentinel to compute max rectangle area.
 */

#include "io.h"
#include <stdlib.h>

int largestRectangleArea(int *heights, int n)
{
    int *stack = malloc((n + 1) * sizeof(int));
    int top = -1;
    int max_area = 0;
    for (int i = 0; i <= n; i++) {
        int h = (i < n) ? heights[i] : 0;
        while (top >= 0 && h < heights[stack[top]]) {
            int height = heights[stack[top--]];
            int width = (top < 0) ? i : i - stack[top] - 1;
            if (height * width > max_area) max_area = height * width;
        }
        stack[++top] = i;
    }
    free(stack);
    return max_area;
}

int main(void)
{
    int n;
    int *heights = read_ints(&n);
    write_int(largestRectangleArea(heights, n));
    free(heights);
    return 0;
}
