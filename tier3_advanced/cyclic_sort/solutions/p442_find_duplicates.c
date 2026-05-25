/*
 * P442: Find All Duplicates in an Array (Medium)
 * https://leetcode.com/problems/find-all-duplicates-in-an-array/
 * Topics: Array, Hash Table
 *
 * Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.
 * You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output
 *
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [2,3]
 *
 * Example 2:
 *     Input: nums = [1,1,2]
 *     Output: [1]
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: []
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 *     - Each element in nums appears once or twice.
 *
 * Template (python3):
 *     class Solution:
 *         def findDuplicates(self, nums: List[int]) -> List[int]:
 *
 * Hint: Negate the value at index abs(num)-1 to mark seen numbers in-place.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int *findDuplicates(int *nums, int n, int *return_size) {
    int *result = malloc(n * sizeof(int));
    *return_size = 0;
    for (int i = 0; i < n; i++) {
        int idx = abs(nums[i]) - 1;
        if (nums[idx] < 0) {
            result[(*return_size)++] = abs(nums[i]);
        } else {
            nums[idx] = -nums[idx];
        }
    }
    return result;
}

static int arr_eq(const int *a, int an, const int *b, int bn) {
    if (an != bn) return 0;
    for (int i = 0; i < an; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}

static void print_arr(const int *a, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        if (i) printf(",");
        printf("%d", a[i]);
    }
    printf("]");
}

int main(void) {
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  442. Find All Duplicates in an Array\n");
    printf("============================================================\n");

    {
        int nums[] = {4, 3, 2, 7, 8, 2, 3, 1};
        int ret_size = 0;
        int *got = findDuplicates(nums, 8, &ret_size);
        int expected[] = {2, 3};
        if (arr_eq(got, ret_size, expected, 2)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: "); print_arr(expected, 2); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1, 1, 2};
        int ret_size = 0;
        int *got = findDuplicates(nums, 3, &ret_size);
        int expected[] = {1};
        if (arr_eq(got, ret_size, expected, 1)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: "); print_arr(expected, 1); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1};
        int ret_size = 0;
        int *got = findDuplicates(nums, 1, &ret_size);
        if (ret_size == 0) { passed++; printf("  Test 3 (single): PASS\n"); }
        else { printf("  Test 3 (single): FAIL\n  Expected: [], Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {2, 2};
        int ret_size = 0;
        int *got = findDuplicates(nums, 2, &ret_size);
        int expected[] = {2};
        if (arr_eq(got, ret_size, expected, 1)) { passed++; printf("  Test 4 (all same, n=2): PASS\n"); }
        else { printf("  Test 4 (all same, n=2): FAIL\n  Expected: "); print_arr(expected, 1); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1, 2, 2, 1};
        int ret_size = 0;
        int *got = findDuplicates(nums, 4, &ret_size);
        int expected[] = {2, 1};
        if (arr_eq(got, ret_size, expected, 2)) { passed++; printf("  Test 5 (all duplicates, n=4): PASS\n"); }
        else { printf("  Test 5 (all duplicates, n=4): FAIL\n  Expected: "); print_arr(expected, 2); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {1, 2};
        int ret_size = 0;
        int *got = findDuplicates(nums, 2, &ret_size);
        if (ret_size == 0) { passed++; printf("  Test 6 (no duplicates): PASS\n"); }
        else { printf("  Test 6 (no duplicates): FAIL\n  Expected: [], Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }
    {
        int nums[] = {10, 2, 5, 10, 9, 1, 1, 7, 9, 6};
        int ret_size = 0;
        int *got = findDuplicates(nums, 10, &ret_size);
        int expected[] = {10, 1, 9};
        if (arr_eq(got, ret_size, expected, 3)) { passed++; printf("  Test 7 (large, multiple duplicates): PASS\n"); }
        else { printf("  Test 7 (large, multiple duplicates): FAIL\n  Expected: "); print_arr(expected, 3); printf(", Got: "); print_arr(got, ret_size); printf("\n"); }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
