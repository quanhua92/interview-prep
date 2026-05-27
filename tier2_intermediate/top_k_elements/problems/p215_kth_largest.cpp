/*
 * P215: Kth Largest Element in an Array (Medium)
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Quickselect
 *
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * Can you solve it without sorting?
 *
 * Example 1:
 *     Input: nums = [3,2,1,5,6,4], k = 2
 *     Output: 5
 *
 * Example 2:
 *     Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 *     Output: 4
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def findKthLargest(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a min-heap of size k to efficiently find the kth largest element.
 */

#include "io.h"
#include <algorithm>
#include <cstdlib>
#include <vector>

int findKthLargest(std::vector<int> nums, int k)
{
    abort();
}

int main(void)
{
    std::vector<int> nums = read_ints();
    std::vector<int> k_arr = read_ints();
    int k = k_arr[0];
    write_int(findKthLargest(nums, k));
    return 0;
}
