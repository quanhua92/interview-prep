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
 * Hint: Use backtracking with swapping to generate all permutations in-place.
 */

#include "io.h"
#include <algorithm>
#include <numeric>
#include <vector>

static void backtrack(std::vector<int>& nums, int first, std::vector<std::vector<int>>& res) {
    if (first == (int)nums.size()) {
        res.push_back(nums);
        return;
    }
    for (int i = first; i < (int)nums.size(); i++) {
        std::swap(nums[first], nums[i]);
        backtrack(nums, first + 1, res);
        std::swap(nums[first], nums[i]);
    }
}

static std::vector<std::vector<int>> permute(std::vector<int> nums) {
    std::vector<std::vector<int>> res;
    backtrack(nums, 0, res);
    for (auto& t : res) std::sort(t.begin(), t.end());
    std::sort(res.begin(), res.end());
    return res;
}

int main(void)
{
    std::vector<int> nums = read_ints();
    auto result = permute(nums);
    for (const auto& row : result)
        write_ints(row);
    return 0;
}
