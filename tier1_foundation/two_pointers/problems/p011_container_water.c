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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxArea(int *height, int n)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        int input[10];
        int n;
        int expected;
    } tests[] = {
        {"example 1",             {1, 8, 6, 2, 5, 4, 8, 3, 7}, 9, 49},
        {"example 2",             {1, 1},                         2, 1},
        {"symmetric",             {4, 3, 2, 1, 4},                5, 16},
        {"all zeros",             {0, 0, 0, 0},                   4, 0},
        {"strictly increasing",   {1, 2, 3, 4, 5},                5, 6},
        {"strictly decreasing",   {5, 4, 3, 2, 1},                5, 6},
        {"max height two elements", {10000, 10000},               2, 10000},
        {"all same height",       {2, 2, 2, 2, 2},                5, 8},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  11. Container With Most Water\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = maxArea(tests[i].input, tests[i].n);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
