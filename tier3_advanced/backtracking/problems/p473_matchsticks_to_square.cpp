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
    abort();
}

int main() {
    auto matchsticks = read_ints();
    write_bool(makesquare(matchsticks));
    return 0;
}
