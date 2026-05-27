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
 * Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
 */

#include "io.h"
#include <algorithm>
#include <vector>

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
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res;
    std::vector<int> path;
    backtrack(0, nums, path, res);
    return res;
}

int main(void)
{
    std::vector<int> nums = read_ints();
    auto result = subsetsWithDup(nums);
    for (const auto& row : result)
        write_ints(row);
    return 0;
}
