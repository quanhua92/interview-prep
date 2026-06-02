/*
 * P410: Split Array Largest Sum (Hard)
 * https://leetcode.com/problems/split-array-largest-sum/
 * Topics: Array, Binary Search, Dynamic Programming, Greedy, Prefix Sum
 *
 * Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
 * Return the minimized largest sum of the split.
 * A subarray is a contiguous part of the array.
 *
 * Example 1:
 *     Input: nums = [7,2,5,10,8], k = 2
 *     Output: 18
 *     Explanation: There are four ways to split nums into two subarrays.
 *     The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,5], k = 2
 *     Output: 9
 *     Explanation: There are four ways to split nums into two subarrays.
 *     The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.
 *
 * Constraints:
 *     - 1 <= nums.length <= 1000
 *     - 0 <= nums[i] <= 10^6
 *     - 1 <= k <= min(50, nums.length)
 *
 * Template (python3):
 *     class Solution:
 *         def splitArray(self, nums: List[int], k: int) -> int:
 *
 * Hint: Binary search the answer in [max(nums), sum(nums)] and check feasibility greedily.
 */


#include "io.h"
#include <numeric>
#include <algorithm>
#include <vector>

static bool feasible(const std::vector<int> &nums, long long max_sum, int k)
{
    int count = 1;
    long long current = 0;
    for (int v : nums) {
        current += v;
        if (current > max_sum) {
            count++;
            current = v;
            if (count > k) return false;
        }
    }
    return true;
}

long long splitArray(const std::vector<int> &nums, int k)
{
    long long left = *std::max_element(nums.begin(), nums.end());
    long long right = std::accumulate(nums.begin(), nums.end(), 0LL);
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (feasible(nums, mid, k))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

int main(void)
{
    std::vector<int> nums = read_ints();
    std::vector<int> k_line = read_ints();
    int k = k_line[0];
    write_int((int)splitArray(nums, k));
    return 0;
}
