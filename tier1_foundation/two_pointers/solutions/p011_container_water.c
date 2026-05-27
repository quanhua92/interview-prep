/*
 * P11: Container With Most Water (Medium)
 * https://leetcode.com/problems/container-with-most-water/
 * Topics: Array, Two Pointers, Greedy
 *
 * You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container, such that the container contains the most water.
 * Return the maximum amount of water a container can store.
 * Notice that you may not slant the container.
 *
 * Example 1:
 *     Input: height = [1,8,6,2,5,4,8,3,7]
 *     Output: 49
 *     Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
 *
 * Example 2:
 *     Input: height = [1,1]
 *     Output: 1
 *
 * Constraints:
 *     - n == height.length
 *     - 2 <= n <= 105
 *     - 0 <= height[i] <= 104
 *
 * Hints:
 *     - If you simulate the problem, it will be O(n^2) which is not efficient.
 *     - Try to use two-pointers. Set one pointer to the left and one to the right of the array. Always move the pointer that points to the lower line.
 *     - How can you calculate the amount of water at each step?
 *
 * Template (python3):
 *     class Solution:
 *         def maxArea(self, height: List[int]) -> int:
 *
 * Hint: Start with pointers at both ends and move the shorter one inward.
 */

#include "io.h"
#include <stdlib.h>

int maxArea(int *height, int n)
{
    int left = 0, right = n - 1;
    int max_area = 0;
    while (left < right) {
        int h = height[left] < height[right] ? height[left] : height[right];
        int area = h * (right - left);
        if (area > max_area) max_area = area;
        if (height[left] < height[right])
            left++;
        else
            right--;
    }
    return max_area;
}

int main(void)
{
    int n;
    int *height = read_ints(&n);
    write_int(maxArea(height, n));
    free(height);
    return 0;
}
