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


#include <cstdio>
#include <cstdlib>
#include <vector>

static int merge_sort(std::vector<int> &arr, std::vector<int> &tmp, int left, int right)
{
    if (right - left <= 1) return 0;
    int mid = left + (right - left) / 2;
    int count = merge_sort(arr, tmp, left, mid) + merge_sort(arr, tmp, mid, right);
    int j = mid;
    for (int i = left; i < mid; i++) {
        while (j < right && (long long)arr[i] > 2LL * arr[j])
            j++;
        count += j - mid;
    }
    int p = left, q = mid, k = left;
    while (p < mid && q < right)
        tmp[k++] = arr[p] <= arr[q] ? arr[p++] : arr[q++];
    while (p < mid) tmp[k++] = arr[p++];
    while (q < right) tmp[k++] = arr[q++];
    for (int i = left; i < right; i++) arr[i] = tmp[i];
    return count;
}

int reversePairs(std::vector<int> nums)
{
    if ((int)nums.size() <= 1) return 0;
    std::vector<int> tmp(nums.size());
    return merge_sort(nums, tmp, 0, (int)nums.size());
}

int main(void)
{
    struct Tc { const char *label; std::vector<int> nums; int expected; bool pass; };
    std::vector<Tc> tests = {
        {"example 1", {1,3,2,3,1}, 2, false},
        {"example 2", {2,4,3,5,1}, 3, false},
        {"single element", {1}, 0, false},
        {"all descending", {5,4,3,2,1}, 4, false},
        {"sorted ascending", {1,2,3,4,5}, 0, false},
        {"negative numbers", {2,1,-1}, 2, false},
        {"all equal", {1,1,1,1}, 0, false},
    };

    int passed = 0;
    for (auto &tc : tests) {
        int got = reversePairs(tc.nums);
        tc.pass = (got == tc.expected);
        if (tc.pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  493. Reverse Pairs\n");
    printf("============================================================\n");
    for (int i = 0; i < (int)tests.size(); i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n");
    return passed == (int)tests.size() ? 0 : 1;
}
