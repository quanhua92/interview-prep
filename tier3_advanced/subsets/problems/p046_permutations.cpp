/*
 * P46: Permutations (Medium)
 * https://leetcode.com/problems/permutations/
 * Topics: Array, Backtracking
 * 
 * Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
 * 
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 * 
 * Example 2:
 *     Input: nums = [0,1]
 *     Output: [[0,1],[1,0]]
 * 
 * Example 3:
 *     Input: nums = [1]
 *     Output: [[1]]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 6
 *     - -10 <= nums[i] <= 10
 *     - All the integers of nums are unique.
 * 
 * Template (python3):
 *     class Solution:
 *         def permute(self, nums: List[int]) -> List[List[int]]:
 * 
 * Hint: Use backtracking with swapping to generate all permutations in-place.
 */
#include "cpptest.h"
#include <vector>
#include <algorithm>
#include <numeric>

static void backtrack(std::vector<int>& nums, int first, std::vector<std::vector<int>>& res) {
    /* TODO: Implement */
    return 0;
}

static std::vector<std::vector<int>> permute(std::vector<int> nums) {
    /* TODO: Implement */
    return 0;
}

static bool check(const std::vector<std::vector<int>>& got, const std::vector<std::vector<int>>& exp) {
    /* TODO: Implement */
    return 0;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  46. Permutations\n");
    printf("============================================================\n");

    int passed = 0;

    {
        auto got = permute({1,2,3});
        std::vector<std::vector<int>> exp = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
        if (check(got, exp)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        auto got = permute({0,1});
        std::vector<std::vector<int>> exp = {{0,1},{1,0}};
        if (check(got, exp)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        auto got = permute({1});
        std::vector<std::vector<int>> exp = {{1}};
        if (check(got, exp)) { passed++; printf("  Test 3 (single element): PASS\n"); }
        else { printf("  Test 3 (single element): FAIL\n"); }
    }
    {
        auto got = permute({-1,0,1});
        std::vector<std::vector<int>> exp = {{-1,0,1},{-1,1,0},{0,-1,1},{0,1,-1},{1,-1,0},{1,0,-1}};
        if (check(got, exp)) { passed++; printf("  Test 4 (negative and zero mix): PASS\n"); }
        else { printf("  Test 4 (negative and zero mix): FAIL\n"); }
    }
    {
        auto got = permute({-3,-1});
        std::vector<std::vector<int>> exp = {{-3,-1},{-1,-3}};
        if (check(got, exp)) { passed++; printf("  Test 5 (two negative elements): PASS\n"); }
        else { printf("  Test 5 (two negative elements): FAIL\n"); }
    }
    {
        auto got = permute({1,2,3,4});
        std::vector<std::vector<int>> exp = {
            {1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},
            {2,1,3,4},{2,1,4,3},{2,3,1,4},{2,3,4,1},{2,4,1,3},{2,4,3,1},
            {3,1,2,4},{3,1,4,2},{3,2,1,4},{3,2,4,1},{3,4,1,2},{3,4,2,1},
            {4,1,2,3},{4,1,3,2},{4,2,1,3},{4,2,3,1},{4,3,1,2},{4,3,2,1},
        };
        if (check(got, exp)) { passed++; printf("  Test 6 (four elements): PASS\n"); }
        else { printf("  Test 6 (four elements): FAIL\n"); }
    }
    {
        auto got = permute({-5});
        std::vector<std::vector<int>> exp = {{-5}};
        if (check(got, exp)) { passed++; printf("  Test 7 (single negative element): PASS\n"); }
        else { printf("  Test 7 (single negative element): FAIL\n"); }
    }

    printf("\n  %d/7 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 7 ? 0 : 1;
}
