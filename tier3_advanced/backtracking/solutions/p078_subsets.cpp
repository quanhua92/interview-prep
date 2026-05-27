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
 * Hint: Use backtracking to generate all possible subsets by including/excluding each element.
 */

#include "io.h"
#include <vector>

static std::vector<std::vector<int>> subsets(std::vector<int> nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    int n = (int)nums.size();

    std::function<void(int)> bt = [&](int start) {
        result.push_back(path);
        for (int i = start; i < n; i++) {
            path.push_back(nums[i]);
            bt(i + 1);
            path.pop_back();
        }
    };
    bt(0);
    return result;
}

int main() {
    auto nums = read_ints();
    auto result = subsets(nums);
    for (const auto &s : result) {
        if (s.empty()) {
            write_string("");
        } else {
            write_ints(s);
        }
    }
    return 0;
}
