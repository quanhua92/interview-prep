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
#include "ctest.h"
#include <stdlib.h>
#include <string.h>

static int g_sticks[15];
static int g_n;
static int g_side;
static int g_sides[4];

static int sort_desc(const void *a, const void *b) {
    abort();
}

static int bt(int idx) {
    abort();
}

static int makesquare(int *matchsticks, int matchsticksSize) {
    abort();
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  473. Matchsticks to Square\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int m[] = {1,1,2,2,2};
        int got = makesquare(m, 5);
        if (got) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        int m[] = {3,3,3,3,4};
        int got = makesquare(m, 5);
        if (!got) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        int m[] = {5,5,5,5};
        int got = makesquare(m, 4);
        if (got) { passed++; printf("  Test 3 (four equal sticks): PASS\n"); }
        else { printf("  Test 3 (four equal sticks): FAIL\n"); }
    }
    {
        int m[] = {2,2,2,2,2,2};
        int got = makesquare(m, 6);
        if (!got) { passed++; printf("  Test 4 (all twos cannot form square): PASS\n"); }
        else { printf("  Test 4 (all twos cannot form square): FAIL\n"); }
    }
    {
        int m[] = {1,1,1,1};
        int got = makesquare(m, 4);
        if (got) { passed++; printf("  Test 5 (minimal square): PASS\n"); }
        else { printf("  Test 5 (minimal square): FAIL\n"); }
    }
    {
        int m[] = {3,3,3,3};
        int got = makesquare(m, 4);
        if (got) { passed++; printf("  Test 6 (each stick one side): PASS\n"); }
        else { printf("  Test 6 (each stick one side): FAIL\n"); }
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
