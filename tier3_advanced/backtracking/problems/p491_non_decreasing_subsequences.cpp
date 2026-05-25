/*
 * P491: Non-decreasing Subsequences [PREMIUM] (Medium)
 * https://leetcode.com/problems/non-decreasing-subsequences/
 * Topics: Array, Hash Table, Backtracking, Bit Manipulation
 * 
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
 * Example 1:
 *     Input: nums = [4,6,7,7]
 *     Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 * 
 * Example 2:
 *     Input: nums = [4,4,3,2,1]
 *     Output: [[4,4]]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 15
 *     - -100 <= nums[i] <= 100
 * 
 * Template (python3):
 *     class Solution:
 *         def findSubsequences(self, nums: List[int]) -> List[List[int]]:
 */
#include "cpptest.h"
#include <vector>
#include <algorithm>
#include <unordered_set>

static std::vector<std::vector<int>> findSubsequences(const std::vector<int> &nums) {
    /* TODO: Implement */
    return 0;
}

static bool check(const std::vector<std::vector<int>> &got, const std::vector<std::vector<int>> &exp) {
    /* TODO: Implement */
    return 0;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  491. Non-decreasing Subsequences\n");
    printf("============================================================\n");

    int passed = 0;

    {
        auto got = findSubsequences({4,6,7,7});
        std::vector<std::vector<int>> exp = {{4,6},{4,6,7},{4,6,7,7},{4,7},{4,7,7},{6,7},{6,7,7},{7,7}};
        if (check(got, exp)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        auto got = findSubsequences({4,4,3,2,1});
        std::vector<std::vector<int>> exp = {{4,4}};
        if (check(got, exp)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        auto got = findSubsequences({2,2,2});
        std::vector<std::vector<int>> exp = {{2,2},{2,2,2}};
        if (check(got, exp)) { passed++; printf("  Test 3 (all same elements): PASS\n"); }
        else { printf("  Test 3 (all same elements): FAIL\n"); }
    }
    {
        auto got = findSubsequences({5,4,3,2,1});
        if (got.empty()) { passed++; printf("  Test 4 (strictly decreasing): PASS\n"); }
        else { printf("  Test 4 (strictly decreasing): FAIL\n"); }
    }
    {
        auto got = findSubsequences({1,2,3});
        std::vector<std::vector<int>> exp = {{1,2},{1,2,3},{1,3},{2,3}};
        if (check(got, exp)) { passed++; printf("  Test 5 (strictly increasing): PASS\n"); }
        else { printf("  Test 5 (strictly increasing): FAIL\n"); }
    }
    {
        auto got = findSubsequences({1});
        if (got.empty()) { passed++; printf("  Test 6 (single element): PASS\n"); }
        else { printf("  Test 6 (single element): FAIL\n"); }
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
