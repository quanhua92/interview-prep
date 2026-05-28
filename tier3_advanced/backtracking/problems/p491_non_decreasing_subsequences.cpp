/*
 * P491: Non-decreasing Subsequences [PREMIUM] (Medium)
 * https://leetcode.com/problems/non-decreasing-subsequences/
 * Topics: Array, Hash Table, Backtracking, Bit Manipulation
 *
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements.
 * Example 1:
 *     Input: nums = [4,6,7,7]
 *     Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 *
 * Example 2:
 *     Input: nums = [4,4,3,2,1]
 *     Output: [[4,4]]
 *
 * Template (python3):
 *     class Solution:
 *         def findSubsequences(self, nums: List[int]) -> List[List[int]]:
 */

#include "io.h"
#include <algorithm>
#include <unordered_set>
#include <vector>

static std::vector<std::vector<int>> findSubsequences(const std::vector<int> &nums) {
    abort();
}

int main() {
    auto nums = read_ints();
    auto result = findSubsequences(nums);
    for (const auto &seq : result) {
        write_ints(seq);
    }
    return 0;
}
