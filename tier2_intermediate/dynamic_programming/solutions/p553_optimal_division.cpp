/*
 * P553: Optimal Division [PREMIUM] (Medium)
 * https://leetcode.com/problems/optimal-division/
 * Topics: Array, Math, Dynamic Programming
 *
 * You are given an integer array nums. The adjacent integers in nums will perform the float division.
 * However, you can add any number of parenthesis at any position to change the priority of operations. You want to add these parentheses such the value of the expression after the evaluation is maximum.
 * Return the corresponding expression that has the maximum value in string format.
 * Note: your expression should not contain redundant parenthesis.
 * Example 1:
 *     Input: nums = [1000,100,10,2]
 *     Output: "1000/(100/10/2)"
 *     Explanation: 1000/(100/10/2) = 1000/((100/10)/2) = 200
 *     However, the bold parenthesis in "1000/((100/10)/2)" are redundant since they do not influence the operation priority.
 *     So you should return "1000/(100/10/2)".
 *     Other cases:
 *     1000/(100/10)/2 = 50
 *     1000/(100/(10/2)) = 50
 *     1000/100/10/2 = 0.5
 *     1000/100/(10/2) = 2
 *
 * Example 2:
 *     Input: nums = [2,3,4]
 *     Output: "2/(3/4)"
 *     Explanation: (2/(3/4)) = 8/3 = 2.667
 *     It can be shown that after trying all possibilities, we cannot get an expression with evaluation greater than 2.667
 *
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - 2 <= nums[i] <= 1000
 *     - There is only one optimal division for the given input.
 *
 * Template (python3):
 *     class Solution:
 *         def optimalDivision(self, nums: List[int]) -> str:
 */

#include "io.h"
#include <vector>

std::string optimalDivision(std::vector<int> nums) {
    if (nums.size() == 1) return std::to_string(nums[0]);
    if (nums.size() == 2) return std::to_string(nums[0]) + "/" + std::to_string(nums[1]);
    std::string result = std::to_string(nums[0]) + "/(";
    for (size_t i = 1; i < nums.size(); i++) {
        if (i > 1) result += "/";
        result += std::to_string(nums[i]);
    }
    result += ")";
    return result;
}

int main(void) {
    std::vector<int> nums = read_ints();
    write_string(optimalDivision(nums));
    return 0;
}
