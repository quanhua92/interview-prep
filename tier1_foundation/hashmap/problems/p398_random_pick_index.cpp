/*
 * P398: Random Pick Index [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-pick-index/
 * Topics: Hash Table, Math, Reservoir Sampling, Randomized
 *
 * Given an integer array nums with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "pick", "pick", "pick"]
 *     [[[1, 2, 3, 3, 3]], [3], [1], [3]]
 *     Output
 *     [null, 4, 0, 2]
 *
 *     Explanation
 *     Solution solution = new Solution([1, 2, 3, 3, 3]);
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 *     solution.pick(1); // It should return 0. Since in the array only nums[0] is equal to 1.
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 *
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -231 <= nums[i] <= 231 - 1
 *     - target is an integer from nums.
 *     - At most 104 calls will be made to pick.
 */

#include "io.h"
#include <cstdlib>
#include <unordered_map>
#include <vector>

class Solution {
    std::unordered_map<int, std::vector<int>> idx;
public:
    Solution(std::vector<int>& nums) {
        for (int i = 0; i < (int)nums.size(); i++)
            idx[nums[i]].push_back(i);
    }
    int pick(int target) {
        abort();
    }
};

int main(void)
{
    std::vector<int> nums = read_ints();
    int target = read_int();

    srand(42);
    Solution sol(nums);
    write_int(sol.pick(target));
    return 0;
}
