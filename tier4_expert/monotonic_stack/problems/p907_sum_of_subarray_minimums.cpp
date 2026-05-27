/*
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 *
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
 *
 * Example 1:
 *     Input: arr = [3,1,2,4]
 *     Output: 17
 *
 * Example 2:
 *     Input: arr = [11,81,94,43,3]
 *     Output: 444
 *
 * Constraints:
 *     - 1 <= arr.length <= 3 * 104
 *     - 1 <= arr[i] <= 3 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def sumSubarrayMins(self, arr: List[int]) -> int:
 *
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */

#include "io.h"
#include <vector>

int sumSubarrayMins(const std::vector<int> &arr)
{
    abort();
}

int main(void)
{
    std::vector<int> arr = read_ints();
    write_int(sumSubarrayMins(arr));
    return 0;
}
