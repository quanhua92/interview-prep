/*
 * P39: Combination Sum (Medium)
 * https://leetcode.com/problems/combination-sum/
 * Topics: Array, Backtracking
 *
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target.
 * The same number may be chosen from candidates an unlimited number of times.
 *
 * Example 1:
 *     Input: candidates = [2,3,6,7], target = 7
 *     Output: [[2,2,3],[7]]
 *
 * Example 2:
 *     Input: candidates = [2,3,5], target = 8
 *     Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Hint: Use backtracking with early pruning when the remaining sum goes negative.
 */

#include "io.h"
#include <algorithm>
#include <functional>
#include <vector>


static std::vector<std::vector<int>> combinationSum(std::vector<int> candidates, int target) {
    abort();
}

int main() {
    auto candidates = read_ints();
    int target = read_int();
    auto result = combinationSum(candidates, target);
    for (const auto &combo : result) {
        write_ints(combo);
    }
    return 0;
}
