/*
 * P354: Russian Doll Envelopes [PREMIUM] (Hard)
 * https://leetcode.com/problems/russian-doll-envelopes/
 * Topics: Array, Binary Search, Dynamic Programming, Sorting
 *
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
 * One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 * Note: You cannot rotate an envelope.
 * Example 1:
 *     Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
 *     Output: 3
 *     Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 *
 * Example 2:
 *     Input: envelopes = [[1,1],[1,1],[1,1]]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= envelopes.length <= 105
 *     - envelopes[i].length == 2
 *     - 1 <= wi, hi <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
 */

#include "io.h"
#include <algorithm>
#include <cstdio>
#include <vector>

int maxEnvelopes(std::vector<std::vector<int>> envelopes)
{
    if (envelopes.size() <= 1) return (int)envelopes.size();
    std::sort(envelopes.begin(), envelopes.end(), [](const auto &a, const auto &b) {
        return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
    });
    std::vector<int> dp;
    for (auto &env : envelopes) {
        int h = env[1];
        auto it = std::lower_bound(dp.begin(), dp.end(), h);
        if (it == dp.end()) dp.push_back(h);
        else *it = h;
    }
    return (int)dp.size();
}

int main(void)
{
    int cols = read_int();
    std::vector<std::vector<int>> envelopes;
    for (int i = 0; i < cols; i++) {
        envelopes.push_back(read_ints());
    }
    write_int(maxEnvelopes(envelopes));
    return 0;
}
