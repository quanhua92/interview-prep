/*
 * P556: Next Greater Element III [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-iii/
 * Topics: Math, Two Pointers, String
 *
 * Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
 * Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
 * Example 1:
 *     Input: n = 12
 *     Output: 21
 *
 * Example 2:
 *     Input: n = 21
 *     Output: -1
 *
 * Constraints:
 *     - 1 <= n <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElement(self, n: int) -> int:
 */


#include "io.h"
#include <algorithm>

int nextGreaterElement(int n) {
    std::string digits = std::to_string(n);
    int i = (int)digits.size() - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) i--;
    if (i < 0) return -1;
    int j = (int)digits.size() - 1;
    while (digits[j] <= digits[i]) j--;
    std::swap(digits[i], digits[j]);
    std::reverse(digits.begin() + i + 1, digits.end());
    long long val = std::stoll(digits);
    if (val > 2147483647LL) return -1;
    return (int)val;
}

int main() {
    std::vector<int> vals = read_ints();
    write_int(nextGreaterElement(vals[0]));
    return 0;
}
