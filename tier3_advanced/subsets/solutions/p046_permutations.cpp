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
#include <vector>

static std::vector<std::vector<int>> permute(std::vector<int> nums) {
    std::vector<std::vector<int>> perms = {{}};
    for (int num : nums) {
        std::vector<std::vector<int>> new_perms;
        for (const auto &p : perms) {
            for (size_t i = 0; i <= p.size(); i++) {
                auto np = p;
                np.insert(np.begin() + i, num);
                new_perms.push_back(np);
            }
        }
        perms = std::move(new_perms);
    }
    std::sort(perms.begin(), perms.end());
    return perms;
}

int main(void)
{
    std::vector<int> nums = read_ints();
    auto result = permute(nums);
    for (const auto& row : result)
        write_ints(row);
    return 0;
}
