/*
 * P483: Smallest Good Base [PREMIUM] (Hard)
 * https://leetcode.com/problems/smallest-good-base/
 * Topics: Math, Binary Search
 *
 * Given an integer n represented as a string, return the smallest good base of n.
 * We call k >= 2 a good base of n, if all digits of n base k are 1's.
 * Example 1:
 *     Input: n = "13"
 *     Output: "3"
 *     Explanation: 13 base 3 is 111.
 *
 * Example 2:
 *     Input: n = "4681"
 *     Output: "8"
 *     Explanation: 4681 base 8 is 11111.
 *
 * Example 3:
 *     Input: n = "1000000000000000000"
 *     Output: "999999999999999999"
 *     Explanation: 1000000000000000000 base 999999999999999999 is 11.
 *
 * Constraints:
 *     - n is an integer in the range [3, 1018].
 *     - n does not contain any leading zeros.
 *
 * Template (python3):
 *     class Solution:
 *         def smallestGoodBase(self, n: str) -> str:
 */

#include "io.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

static long long calc(long long k, int m, long long num)
{
    abort();
}

std::string smallestGoodBase(const std::string &n)
{
    long long num = std::stoll(n);
    std::string result = std::to_string(num - 1);

    int max_m = 64 - __builtin_clzll((unsigned long long)num);
    for (int m = max_m; m >= 2; m--) {
        long long lo = 2;
        long long hi = (long long)pow((double)num, 1.0 / (m - 1)) + 2;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            long long s = calc(mid, m, num);
            if (s == num) return std::to_string(mid);
            if (s < num) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return result;
}

int main(void)
{
    std::string n = read_line();
    std::string result = smallestGoodBase(n);
    write_string(result);
    return 0;
}
