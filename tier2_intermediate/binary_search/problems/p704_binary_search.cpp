/*
 * P704: Binary Search (Easy)
 * https://leetcode.com/problems/binary-search/
 * Topics: Array, Binary Search
 *
 * Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * Example 1:
 *     Input: nums = [-1,0,3,5,9,12], target = 9
 *     Output: 4
 *     Explanation: 9 exists in nums and its index is 4
 *
 * Example 2:
 *     Input: nums = [-1,0,3,5,9,12], target = 2
 *     Output: -1
 *     Explanation: 2 does not exist in nums so return -1
 *
 * Constraints:
 *     - 1 <= nums.length <= 10^4
 *     - -10^4 < nums[i], target < 10^4
 *     - All the integers in nums are unique.
 *     - nums is sorted in ascending order.
 *
 * Template (python3):
 *     class Solution:
 *         def search(self, nums: List[int], target: int) -> int:
 *
 * Hint: Use the classic binary search pattern with left and right pointers.
 */

#include "io.h"
#include <vector>

int search(const std::vector<int> &nums, int target)
{
    abort();
}

int main(void)
{
    std::vector<int> nums = read_ints();
    int target = read_ints()[0];
    write_int(search(nums, target));
    return 0;
}
