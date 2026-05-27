/*
 * P473: Matchsticks to Square [PREMIUM] (Medium)
 * https://leetcode.com/problems/matchsticks-to-square/
 * Topics: Array, Dynamic Programming, Backtracking, Bit Manipulation, Bitmask
 *
 * You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square.
 * Return true if you can make this square and false otherwise.
 *
 * Example 1:
 *     Input: matchsticks = [1,1,2,2,2]
 *     Output: true
 *
 * Example 2:
 *     Input: matchsticks = [3,3,3,3,4]
 *     Output: false
 *
 * Hint: Treat the matchsticks as an array. Can we split the array into 4 equal parts?
 */

#include "io.h"
#include <algorithm>
#include <numeric>
#include <vector>

static bool makesquare(std::vector<int> matchsticks) {
    if (matchsticks.empty()) return false;
    long long total = std::accumulate(matchsticks.begin(), matchsticks.end(), 0LL);
    if (total % 4 != 0) return false;
    int side = (int)(total / 4);
    std::sort(matchsticks.begin(), matchsticks.end(), std::greater<int>());
    if (matchsticks[0] > side) return false;
    int n = (int)matchsticks.size();
    std::vector<int> sides(4, 0);

    std::function<bool(int)> bt = [&](int idx) -> bool {
        if (idx == n) return sides[0] == side && sides[1] == side &&
                             sides[2] == side && sides[3] == side;
        for (int i = 0; i < 4; i++) {
            if (sides[i] + matchsticks[idx] <= side) {
                sides[i] += matchsticks[idx];
                if (bt(idx + 1)) return true;
                sides[i] -= matchsticks[idx];
                if (sides[i] == 0) break;
            }
        }
        return false;
    };
    return bt(0);
}

int main() {
    auto matchsticks = read_ints();
    write_bool(makesquare(matchsticks));
    return 0;
}
