/*
 * P912: Sort an Array (Medium)
 * https://leetcode.com/problems/sort-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Merge Sort, Bucket Sort, Radix Sort, Counting Sort
 * 
 * Given an array of integers nums, sort the array in ascending order and return it.
 * You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.
 * 
 * Example 1:
 *     Input: nums = [5,2,3,1]
 *     Output: [1,2,3,5]
 *     Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).
 * 
 * Example 2:
 *     Input: nums = [5,1,1,2,0,0]
 *     Output: [0,0,1,1,2,5]
 *     Explanation: Note that the values of nums are not necessarily unique.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 5 * 104
 *     - -5 * 104 <= nums[i] <= 5 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def sortArray(self, nums: List[int]) -> List[int]:
 * 
 * Hint: Implement merge sort — divide array in half, sort recursively, merge.
 */
#include <cstdio>
#include <cstring>
#include <vector>

static void merge_sort(std::vector<int> &arr, std::vector<int> &tmp, int l, int r)
{
    abort();
}

std::vector<int> sortArray(std::vector<int> nums)
{
    abort();
}

static void print_arr(const std::vector<int> &a)
{
    abort();
}

int main(void)
{
    printf("\n============================================================\n");
    printf("  912. Sort an Array\n");
    printf("============================================================\n");
    int passed = 0, total = 8;

    {
        std::vector<int> exp = {1, 2, 3, 5};
        auto got = sortArray({5, 2, 3, 1});
        if (got == exp) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: "); print_arr(exp); printf("\n  Got:      "); print_arr(got); printf("\n"); }
    }
    {
        std::vector<int> exp = {0, 0, 1, 1, 2, 5};
        auto got = sortArray({5, 1, 1, 2, 0, 0});
        if (got == exp) { passed++; printf("  Test 2 (duplicates): PASS\n"); }
        else { printf("  Test 2 (duplicates): FAIL\n"); }
    }
    {
        std::vector<int> exp = {1};
        auto got = sortArray({1});
        if (got == exp) { passed++; printf("  Test 3 (single element): PASS\n"); }
        else { printf("  Test 3 (single element): FAIL\n"); }
    }
    {
        std::vector<int> exp = {};
        auto got = sortArray({});
        if (got == exp) { passed++; printf("  Test 4 (empty array): PASS\n"); }
        else { printf("  Test 4 (empty array): FAIL\n"); }
    }
    {
        std::vector<int> exp = {1, 2, 3, 4, 5};
        auto got = sortArray({1, 2, 3, 4, 5});
        if (got == exp) { passed++; printf("  Test 5 (already sorted): PASS\n"); }
        else { printf("  Test 5 (already sorted): FAIL\n"); }
    }
    {
        std::vector<int> exp = {1, 2, 3, 4, 5};
        auto got = sortArray({5, 4, 3, 2, 1});
        if (got == exp) { passed++; printf("  Test 6 (reverse sorted): PASS\n"); }
        else { printf("  Test 6 (reverse sorted): FAIL\n"); }
    }
    {
        std::vector<int> exp = {7, 7, 7, 7};
        auto got = sortArray({7, 7, 7, 7});
        if (got == exp) { passed++; printf("  Test 7 (all same elements): PASS\n"); }
        else { printf("  Test 7 (all same elements): FAIL\n"); }
    }
    {
        std::vector<int> exp = {-8, -5, -3, -1};
        auto got = sortArray({-5, -3, -8, -1});
        if (got == exp) { passed++; printf("  Test 8 (negative numbers): PASS\n"); }
        else { printf("  Test 8 (negative numbers): FAIL\n"); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
