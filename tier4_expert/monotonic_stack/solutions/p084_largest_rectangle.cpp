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

#include "io.h"
#include <algorithm>
#include <vector>

int largestRectangleArea(const std::vector<int> &heights)
{
    int n = (int)heights.size();
    std::vector<int> stack;
    int max_area = 0;
    for (int i = 0; i <= n; i++) {
        int h = (i < n) ? heights[i] : 0;
        while (!stack.empty() && h < heights[stack.back()]) {
            int height = heights[stack.back()];
            stack.pop_back();
            int width = stack.empty() ? i : i - stack.back() - 1;
            max_area = std::max(max_area, height * width);
        }
        stack.push_back(i);
    }
    return max_area;
}

int main(void)
{
    std::vector<int> heights = read_ints();
    write_int(largestRectangleArea(heights));
    return 0;
}
