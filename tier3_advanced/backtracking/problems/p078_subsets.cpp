/*
 * P78: Subsets (Medium)
 * https://leetcode.com/problems/subsets/
 * Topics: Array, Backtracking, Bit Manipulation
 * 
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 * 
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 *     - All the numbers of nums are unique.
 * 
 * Template (python3):
 *     class Solution:
 *         def subsets(self, nums: List[int]) -> List[List[int]]:
 * 
 * Hint: Use backtracking to generate all possible subsets by including/excluding each element.
 */
#include "cpptest.h"
#include <vector>
#include <algorithm>

static std::vector<std::vector<int>> subsets(std::vector<int> nums) {
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
    printf("  78. Subsets\n");
    printf("============================================================\n");

    int passed = 0;

    {
        auto got = subsets({1,2,3});
        std::vector<std::vector<int>> exp = {{},{1},{1,2},{1,2,3},{1,3},{2},{2,3},{3}};
        if (check(got, exp)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        auto got = subsets({0});
        std::vector<std::vector<int>> exp = {{},{0}};
        if (check(got, exp)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        auto got = subsets({1,2});
        std::vector<std::vector<int>> exp = {{},{1},{1,2},{2}};
        if (check(got, exp)) { passed++; printf("  Test 3 (two elements): PASS\n"); }
        else { printf("  Test 3 (two elements): FAIL\n"); }
    }
    {
        auto got = subsets({-1,0,1});
        std::vector<std::vector<int>> exp = {{},{-1},{-1,0},{-1,0,1},{-1,1},{0},{0,1},{1}};
        if (check(got, exp)) { passed++; printf("  Test 4 (negative numbers): PASS\n"); }
        else { printf("  Test 4 (negative numbers): FAIL\n"); }
    }
    {
        auto got = subsets({1,2,3,4});
        std::vector<std::vector<int>> exp = {
            {},{1},{1,2},{1,2,3},{1,2,3,4},{1,2,4},{1,3},{1,3,4},
            {1,4},{2},{2,3},{2,3,4},{2,4},{3},{3,4},{4}
        };
        if (check(got, exp)) { passed++; printf("  Test 5 (four elements): PASS\n"); }
        else { printf("  Test 5 (four elements): FAIL\n"); }
    }
    {
        auto got = subsets({3,1});
        std::vector<std::vector<int>> exp = {{},{3},{3,1},{1}};
        if (check(got, exp)) { passed++; printf("  Test 6 (unsorted input): PASS\n"); }
        else { printf("  Test 6 (unsorted input): FAIL\n"); }
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
