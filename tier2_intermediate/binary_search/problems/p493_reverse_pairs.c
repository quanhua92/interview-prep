/*
 * P493: Reverse Pairs [PREMIUM] (Hard)
 * https://leetcode.com/problems/reverse-pairs/
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 * 
 * Given an integer array nums, return the number of reverse pairs in the array.
 * A reverse pair is a pair (i, j) where:
 * Example 1:
 *     Input: nums = [1,3,2,3,1]
 *     Output: 2
 *     Explanation: The reverse pairs are:
 *     (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
 *     (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
 * 
 * Example 2:
 *     Input: nums = [2,4,3,5,1]
 *     Output: 3
 *     Explanation: The reverse pairs are:
 *     (1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
 *     (2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
 *     (3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 5 * 104
 *     - -231 <= nums[i] <= 231 - 1
 * 
 * Hint: Use the merge-sort technique.
 * Hint: Divide the array into two parts and sort them.
 * Hint: For each integer in the first part, count the number of integers that satisfy the condition from the second part. Use the pointer to help you in the counting process.
 * 
 * Template (python3):
 *     class Solution:
 *         def reversePairs(self, nums: List[int]) -> int:
 */
#include <stdio.h>
#include <stdlib.h>

static int merge_sort(int *arr, int *tmp, int left, int right)
{
    abort();
}

int reversePairs(int *nums, int numsSize)
{
    abort();
}

int main(void)
{
    struct { const char *label; int nums[10]; int n; int expected; int pass; } tests[] = {
        { "example 1", {1,3,2,3,1}, 5, 2, 0 },
        { "example 2", {2,4,3,5,1}, 5, 3, 0 },
        { "single element", {1}, 1, 0, 0 },
        { "all descending", {5,4,3,2,1}, 5, 4, 0 },
        { "sorted ascending", {1,2,3,4,5}, 5, 0, 0 },
        { "negative numbers", {2,1,-1}, 3, 2, 0 },
        { "all equal", {1,1,1,1}, 4, 0, 0 },
    };
    int tn = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    for (int i = 0; i < tn; i++) {
        int buf[10];
        for (int j = 0; j < tests[i].n; j++) buf[j] = tests[i].nums[j];
        int got = reversePairs(buf, tests[i].n);
        tests[i].pass = (got == tests[i].expected);
        if (tests[i].pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  493. Reverse Pairs\n");
    printf("============================================================\n");
    for (int i = 0; i < tn; i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, tn);
    printf("============================================================\n");
    return passed == tn ? 0 : 1;
}
