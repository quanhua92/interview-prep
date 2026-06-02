/*
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 *
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 10^9 + 7.
 *
 * Example 1:
 *     Input: arr = [3,1,2,4]
 *     Output: 17
 *     Explanation:
 *     Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
 *     Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
 *     Sum is 17.
 *
 * Example 2:
 *     Input: arr = [11,81,94,43,3]
 *     Output: 444
 *
 * Constraints:
 *     - 1 <= arr.length <= 3 * 10^4
 *     - 1 <= arr[i] <= 3 * 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def sumSubarrayMins(self, arr: List[int]) -> int:
 *
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */

#include "io.h"
#include <vector>

static const long long MOD = 1000000007LL;

int sumSubarrayMins(const std::vector<int> &arr)
{
    int n = (int)arr.size();
    std::vector<int> left(n, -1);
    std::vector<int> right(n, n);
    std::vector<int> stack;

    for (int i = 0; i < n; i++) {
        while (!stack.empty() && arr[stack.back()] >= arr[i]) stack.pop_back();
        left[i] = stack.empty() ? -1 : stack.back();
        stack.push_back(i);
    }

    stack.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!stack.empty() && arr[stack.back()] > arr[i]) stack.pop_back();
        right[i] = stack.empty() ? n : stack.back();
        stack.push_back(i);
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long cl = i - left[i];
        long long cr = right[i] - i;
        total = (total + (long long)arr[i] * cl * cr) % MOD;
    }
    return (int)total;
}

int main(void)
{
    std::vector<int> arr = read_ints();
    write_int(sumSubarrayMins(arr));
    return 0;
}
