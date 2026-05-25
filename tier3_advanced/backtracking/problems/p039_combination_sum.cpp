/*
 * P39: Combination Sum (Medium)
 * https://leetcode.com/problems/combination-sum/
 * Topics: Array, Backtracking
 * 
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
 * The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
 * 
 * Example 1:
 *     Input: candidates = [2,3,6,7], target = 7
 *     Output: [[2,2,3],[7]]
 *     Explanation:
 *     2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
 *     7 is a candidate, and 7 = 7.
 *     These are the only two combinations.
 * 
 * Example 2:
 *     Input: candidates = [2,3,5], target = 8
 *     Output: [[2,2,2,2],[2,3,3],[3,5]]
 * 
 * Example 3:
 *     Input: candidates = [2], target = 1
 *     Output: []
 * 
 * Constraints:
 *     - 1 <= candidates.length <= 30
 *     - 2 <= candidates[i] <= 40
 *     - All elements of candidates are distinct.
 *     - 1 <= target <= 40
 * 
 * Template (python3):
 *     class Solution:
 *         def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
 * 
 * Hint: Use backtracking with early pruning when the remaining sum goes negative.
 */
#include "cpptest.h"
#include <vector>
#include <algorithm>

static std::vector<std::vector<int>> combinationSum(std::vector<int> candidates, int target) {
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
    printf("  39. Combination Sum\n");
    printf("============================================================\n");

    int passed = 0;

    {
        auto got = combinationSum({2,3,6,7}, 7);
        std::vector<std::vector<int>> exp = {{2,2,3},{7}};
        if (check(got, exp)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        auto got = combinationSum({2,3,5}, 8);
        std::vector<std::vector<int>> exp = {{2,2,2,2},{2,3,3},{3,5}};
        if (check(got, exp)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        auto got = combinationSum({2}, 1);
        if (got.empty()) { passed++; printf("  Test 3 (no solution): PASS\n"); }
        else { printf("  Test 3 (no solution): FAIL\n"); }
    }
    {
        auto got = combinationSum({5}, 5);
        std::vector<std::vector<int>> exp = {{5}};
        if (check(got, exp)) { passed++; printf("  Test 4 (single candidate equals target): PASS\n"); }
        else { printf("  Test 4 (single candidate equals target): FAIL\n"); }
    }
    {
        auto got = combinationSum({2}, 4);
        std::vector<std::vector<int>> exp = {{2,2}};
        if (check(got, exp)) { passed++; printf("  Test 5 (reuse single candidate): PASS\n"); }
        else { printf("  Test 5 (reuse single candidate): FAIL\n"); }
    }
    {
        auto got = combinationSum({8,7,4,3}, 11);
        std::vector<std::vector<int>> exp = {{3,4,4},{3,8},{4,7}};
        if (check(got, exp)) { passed++; printf("  Test 6 (unsorted candidates multiple combos): PASS\n"); }
        else { printf("  Test 6 (unsorted candidates multiple combos): FAIL\n"); }
    }
    {
        auto got = combinationSum({3,5}, 7);
        if (got.empty()) { passed++; printf("  Test 7 (no valid combination): PASS\n"); }
        else { printf("  Test 7 (no valid combination): FAIL\n"); }
    }
    {
        auto got = combinationSum({3}, 9);
        std::vector<std::vector<int>> exp = {{3,3,3}};
        if (check(got, exp)) { passed++; printf("  Test 8 (triple reuse): PASS\n"); }
        else { printf("  Test 8 (triple reuse): FAIL\n"); }
    }

    printf("\n  %d/8 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 8 ? 0 : 1;
}
