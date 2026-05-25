/*
 * P90: Subsets II (Medium)
 * https://leetcode.com/problems/subsets-ii/
 * Topics: Array, Backtracking, Bit Manipulation
 * 
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Example 1:
 *     Input: nums = [1,2,2]
 *     Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 * 
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 * 
 * Template (python3):
 *     class Solution:
 *         def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
 * 
 * Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
 */
#include "cpptest.h"
#include <vector>
#include <algorithm>

static void backtrack(int start, const std::vector<int>& nums, std::vector<int>& path,
                       std::vector<std::vector<int>>& res) {
    res.push_back(path);
    for (int i = start; i < (int)nums.size(); i++) {
        if (i > start && nums[i] == nums[i - 1]) continue;
        path.push_back(nums[i]);
        backtrack(i + 1, nums, path, res);
        path.pop_back();
    }
}

static std::vector<std::vector<int>> subsetsWithDup(std::vector<int> nums) {
    abort();
}

static bool check(const std::vector<std::vector<int>>& got, const std::vector<std::vector<int>>& exp) {
    abort();
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  90. Subsets II\n");
    printf("============================================================\n");

    int passed = 0;

    {
        auto got = subsetsWithDup({1,2,2});
        std::vector<std::vector<int>> exp = {{},{1},{1,2},{1,2,2},{2},{2,2}};
        if (check(got, exp)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        auto got = subsetsWithDup({0});
        std::vector<std::vector<int>> exp = {{},{0}};
        if (check(got, exp)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        auto got = subsetsWithDup({2,2,2});
        std::vector<std::vector<int>> exp = {{},{2},{2,2},{2,2,2}};
        if (check(got, exp)) { passed++; printf("  Test 3 (all duplicates): PASS\n"); }
        else { printf("  Test 3 (all duplicates): FAIL\n"); }
    }
    {
        auto got = subsetsWithDup({1,1,2,2});
        std::vector<std::vector<int>> exp = {{},{1},{1,1},{1,1,2},{1,1,2,2},{1,2},{1,2,2},{2},{2,2}};
        if (check(got, exp)) { passed++; printf("  Test 4 (multiple duplicates): PASS\n"); }
        else { printf("  Test 4 (multiple duplicates): FAIL\n"); }
    }
    {
        auto got = subsetsWithDup({-1,-1,0});
        std::vector<std::vector<int>> exp = {{},{-1},{-1,-1},{-1,-1,0},{-1,0},{0}};
        if (check(got, exp)) { passed++; printf("  Test 5 (negative duplicates): PASS\n"); }
        else { printf("  Test 5 (negative duplicates): FAIL\n"); }
    }
    {
        auto got = subsetsWithDup({1,1,1,1});
        std::vector<std::vector<int>> exp = {{},{1},{1,1},{1,1,1},{1,1,1,1}};
        if (check(got, exp)) { passed++; printf("  Test 6 (all same element): PASS\n"); }
        else { printf("  Test 6 (all same element): FAIL\n"); }
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
