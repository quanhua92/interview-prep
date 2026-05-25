/*
 * P473: Matchsticks to Square [PREMIUM] (Medium)
 * https://leetcode.com/problems/matchsticks-to-square/
 * Topics: Array, Dynamic Programming, Backtracking, Bit Manipulation, Bitmask
 * 
 * You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
 * Return true if you can make this square and false otherwise.
 * Example 1:
 *     Input: matchsticks = [1,1,2,2,2]
 *     Output: true
 *     Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
 * 
 * Example 2:
 *     Input: matchsticks = [3,3,3,3,4]
 *     Output: false
 *     Explanation: You cannot find a way to form a square with all the matchsticks.
 * 
 * Constraints:
 *     - 1 <= matchsticks.length <= 15
 *     - 1 <= matchsticks[i] <= 108
 * 
 * Hint: Treat the matchsticks as an array. Can we split the array into 4 equal parts?
 * Hint: Every matchstick can belong to either of the 4 sides. We don't know which one. Maybe try out all options!
 * Hint: For every matchstick, we have to try out each of the 4 options i.e. which side it can belong to. We can make use of recursion for this.
 * Hint: We don't really need to keep track of which matchsticks belong to a particular side during recursion. We just need to keep track of the <b>length</b> of each of the 4 sides.
 * Hint: When all matchsticks have been used we simply need to see the length of all 4 sides. If they're equal, we have a square on our hands!
 * 
 * Template (python3):
 *     class Solution:
 *         def makesquare(self, matchsticks: List[int]) -> bool:
 */
#include "cpptest.h"
#include <vector>
#include <algorithm>
#include <numeric>

static bool makesquare(std::vector<int> matchsticks) {
    /* TODO: Implement */
    return 0;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  473. Matchsticks to Square\n");
    printf("============================================================\n");

    int passed = 0;

    {
        if (makesquare({1,1,2,2,2})) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        if (!makesquare({3,3,3,3,4})) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        if (makesquare({5,5,5,5})) { passed++; printf("  Test 3 (four equal sticks): PASS\n"); }
        else { printf("  Test 3 (four equal sticks): FAIL\n"); }
    }
    {
        if (!makesquare({2,2,2,2,2,2})) { passed++; printf("  Test 4 (all twos cannot form square): PASS\n"); }
        else { printf("  Test 4 (all twos cannot form square): FAIL\n"); }
    }
    {
        if (makesquare({1,1,1,1})) { passed++; printf("  Test 5 (minimal square): PASS\n"); }
        else { printf("  Test 5 (minimal square): FAIL\n"); }
    }
    {
        if (makesquare({3,3,3,3})) { passed++; printf("  Test 6 (each stick one side): PASS\n"); }
        else { printf("  Test 6 (each stick one side): FAIL\n"); }
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
