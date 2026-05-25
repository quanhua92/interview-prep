/*
 * P448: Find All Numbers Disappeared in an Array (Easy)
 * https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 * Topics: Array, Hash Table
 * 
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
 * 
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [5,6]
 * 
 * Example 2:
 *     Input: nums = [1,1]
 *     Output: [2]
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 * 
 * Follow up:
 *     - Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
 * 
 * Hints:
 *     - This is a really easy problem if you decide to use additional memory. For those trying to write an initial solution using additional memory, think <b>counters!</b>
 *     - However, the trick really is to not use any additional space than what is already available to use. Sometimes, multiple passes over the input array help find the solution. However, there's an interesting piece of information in this problem that makes it easy to re-use the input array itself for the solution.
 *     - The problem specifies that the numbers in the array will be in the range [1, n] where n is the number of elements in the array. Can we use this information and modify the array in-place somehow to find what we need?
 * 
 * Template (python3):
 *     class Solution:
 *         def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
 * 
 * Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int *findDisappearedNumbers(int *nums, int n, int *return_size) {
    abort();
}

static int arr_eq(const int *a, int an, const int *b, int bn) {
    abort();
}

static void print_arr(const int *a, int n) {
    abort();
}

int main(void) {
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  448. Find All Numbers Disappeared in an Array\n");
    printf("============================================================\n");

    {
        int nums[] = {4, 3, 2, 7, 8, 2, 3, 1};
        int ret_size = 0;
        int *got = findDisappearedNumbers(nums, 8, &ret_size);
        int expected[] = {5, 6};
        if (arr_eq(got, ret_size, expected, 2)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: "); print_arr(expected, 2); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1, 1};
        int ret_size = 0;
        int *got = findDisappearedNumbers(nums, 2, &ret_size);
        int expected[] = {2};
        if (arr_eq(got, ret_size, expected, 1)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: "); print_arr(expected, 1); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {2, 2};
        int ret_size = 0;
        int *got = findDisappearedNumbers(nums, 2, &ret_size);
        int expected[] = {1};
        if (arr_eq(got, ret_size, expected, 1)) { passed++; printf("  Test 3 (example 3): PASS\n"); }
        else { printf("  Test 3 (example 3): FAIL\n  Expected: "); print_arr(expected, 1); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1};
        int ret_size = 0;
        int *got = findDisappearedNumbers(nums, 1, &ret_size);
        if (ret_size == 0) { passed++; printf("  Test 4 (single element, none missing): PASS\n"); }
        else { printf("  Test 4 (single element, none missing): FAIL\n  Expected: [], Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1, 1, 1, 1};
        int ret_size = 0;
        int *got = findDisappearedNumbers(nums, 4, &ret_size);
        int expected[] = {2, 3, 4};
        if (arr_eq(got, ret_size, expected, 3)) { passed++; printf("  Test 5 (all same value): PASS\n"); }
        else { printf("  Test 5 (all same value): FAIL\n  Expected: "); print_arr(expected, 3); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1, 2, 3, 4, 5};
        int ret_size = 0;
        int *got = findDisappearedNumbers(nums, 5, &ret_size);
        if (ret_size == 0) { passed++; printf("  Test 6 (identity permutation, none missing): PASS\n"); }
        else { printf("  Test 6 (identity permutation, none missing): FAIL\n  Expected: [], Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {5, 4, 6, 7, 9, 10, 9, 6, 5, 4};
        int ret_size = 0;
        int *got = findDisappearedNumbers(nums, 10, &ret_size);
        int expected[] = {1, 2, 3, 8};
        if (arr_eq(got, ret_size, expected, 4)) { passed++; printf("  Test 7 (large, many disappeared): PASS\n"); }
        else { printf("  Test 7 (large, many disappeared): FAIL\n  Expected: "); print_arr(expected, 4); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
