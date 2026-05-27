/*
 * P278: First Bad Version (Easy)
 * https://leetcode.com/problems/first-bad-version/
 * Topics: Binary Search, Interactive
 *
 * You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
 * You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
 *
 * Example 1:
 *     Input: n = 5, bad = 4
 *     Output: 4
 *     Explanation:
 *     call isBadVersion(3) -> false
 *     call isBadVersion(5) -> true
 *     call isBadVersion(4) -> true
 *     Then 4 is the first bad version.
 *
 * Example 2:
 *     Input: n = 1, bad = 1
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= bad <= n <= 231 - 1
 *
 * Template (python3):
 *     # The isBadVersion API is already defined for you.
 *     # def isBadVersion(version: int) -> bool:
 *
 *     class Solution:
 *         def firstBadVersion(self, n: int) -> int:
 *
 * Hint: Binary search for the leftmost version where is_bad is True.
 */

#include "io.h"

static int g_bad;

static int firstBadVersion(long long n, int bad)
{
    g_bad = bad;
    long long left = 1, right = n;
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (mid >= g_bad)
            right = mid;
        else
            left = mid + 1;
    }
    return (int)left;
}

int main(void)
{
    long long n = read_long();
    int bad = read_int();
    write_int(firstBadVersion(n, bad));
    return 0;
}
