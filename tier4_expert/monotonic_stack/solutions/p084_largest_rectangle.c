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
 *     - 1 <= heights.length <= 105
 *     - 0 <= heights[i] <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def largestRectangleArea(self, heights: List[int]) -> int:
 *
 * Hint: Use a monotonic increasing stack with a sentinel to compute max rectangle area.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int passed = 0, total = 6;
    printf("\n============================================================\n");
    printf("  84. Largest Rectangle in Histogram\n");
    printf("============================================================\n");

    {
        int h[] = {2, 1, 5, 6, 2, 3};
        int got = largestRectangleArea(h, 6);
        if (got == 10) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: 10, Got: %d\n", got); }
    }
    {
        int h[] = {2, 4};
        int got = largestRectangleArea(h, 2);
        if (got == 4) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: 4, Got: %d\n", got); }
    }
    {
        int h[] = {5};
        int got = largestRectangleArea(h, 1);
        if (got == 5) { passed++; printf("  Test 3 (single element): PASS\n"); }
        else { printf("  Test 3 (single element): FAIL\n  Expected: 5, Got: %d\n", got); }
    }
    {
        int h[] = {3, 3, 3};
        int got = largestRectangleArea(h, 3);
        if (got == 9) { passed++; printf("  Test 4 (all same heights): PASS\n"); }
        else { printf("  Test 4 (all same heights): FAIL\n  Expected: 9, Got: %d\n", got); }
    }
    {
        int h[] = {2, 0, 2};
        int got = largestRectangleArea(h, 3);
        if (got == 2) { passed++; printf("  Test 5 (contains zero height): PASS\n"); }
        else { printf("  Test 5 (contains zero height): FAIL\n  Expected: 2, Got: %d\n", got); }
    }
    {
        int h[] = {1, 2, 3, 4, 5};
        int got = largestRectangleArea(h, 5);
        if (got == 9) { passed++; printf("  Test 6 (strictly increasing): PASS\n"); }
        else { printf("  Test 6 (strictly increasing): FAIL\n  Expected: 9, Got: %d\n", got); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
