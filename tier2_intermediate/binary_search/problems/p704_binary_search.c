/*
 * P704: Binary Search (Easy)
 * https://leetcode.com/problems/binary-search/
 * Topics: Array, Binary Search
 * 
 * Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * Example 1:
 *     Input: nums = [-1,0,3,5,9,12], target = 9
 *     Output: 4
 *     Explanation: 9 exists in nums and its index is 4
 * 
 * Example 2:
 *     Input: nums = [-1,0,3,5,9,12], target = 2
 *     Output: -1
 *     Explanation: 2 does not exist in nums so return -1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -104 < nums[i], target < 104
 *     - All the integers in nums are unique.
 *     - nums is sorted in ascending order.
 * 
 * Template (python3):
 *     class Solution:
 *         def search(self, nums: List[int], target: int) -> int:
 * 
 * Hint: Use the classic binary search pattern with left and right pointers.
 */
#include <stdio.h>
#include <stdlib.h>

int search(int *nums, int numsSize, int target)
{
    abort();
}

int main(void)
{
    struct { const char *label; int nums[10001]; int n; int target; int expected; int pass; } tests[] = {
        { "example 1", {-1,0,3,5,9,12}, 6, 9, 4, 0 },
        { "example 2", {-1,0,3,5,9,12}, 6, 2, -1, 0 },
        { "single element", {5}, 1, 5, 0, 0 },
        { "below range", {-1,0,3,5,9,12}, 6, -2, -1, 0 },
        { "last element", {-1,0,3,5,9,12}, 6, 12, 5, 0 },
        { "two elements first", {1,2}, 2, 1, 0, 0 },
        { "two elements last", {1,2}, 2, 2, 1, 0 },
        { "large array middle target", {0}, 1, 0, 0, 0 },
        { "target between elements", {2,4,6,8,10}, 5, 5, -1, 0 },
        { "all negative found last", {-3,-2,-1}, 3, -1, 2, 0 },
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));

    int large[10001];
    for (int i = -5000; i <= 5000; i++) large[i + 5000] = i;
    tests[7].nums[0] = 0;
    tests[7].n = 10001;
    for (int i = 0; i < 10001; i++) tests[7].nums[i] = i - 5000;
    tests[7].expected = 5000;

    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = search(tests[i].nums, tests[i].n, tests[i].target);
        if (got == tests[i].expected) {
            tests[i].pass = 1;
            passed++;
        }
    }

    printf("\n============================================================\n");
    printf("  704. Binary Search\n");
    printf("============================================================\n");
    for (int i = 0; i < n; i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n");
    return passed == n ? 0 : 1;
}
