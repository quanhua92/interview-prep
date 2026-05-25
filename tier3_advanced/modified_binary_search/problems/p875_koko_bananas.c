/*
 * P875: Koko Eating Bananas (Medium)
 * https://leetcode.com/problems/koko-eating-bananas/
 * Topics: Array, Binary Search
 * 
 * Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
 * Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
 * Return the minimum integer k such that she can eat all the bananas within h hours.
 * 
 * Example 1:
 *     Input: piles = [3,6,7,11], h = 8
 *     Output: 4
 * 
 * Example 2:
 *     Input: piles = [30,11,23,4,20], h = 5
 *     Output: 30
 * 
 * Example 3:
 *     Input: piles = [30,11,23,4,20], h = 6
 *     Output: 23
 * 
 * Constraints:
 *     - 1 <= piles.length <= 104
 *     - piles.length <= h <= 109
 *     - 1 <= piles[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def minEatingSpeed(self, piles: List[int], h: int) -> int:
 * 
 * Hint: Binary search on the eating speed, computing total hours for each candidate.
 */
#include <stdio.h>
#include <limits.h>

typedef struct {
    const char *label;
    int piles[10000];
    int piles_n;
    long long h;
    int expected;
} TestCase;

static long long hours_needed(int *piles, int piles_n, int k)
{
    /* TODO: Implement */
    return 0;
}

int minEatingSpeed(int *piles, int pilesSize, long long h)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    TestCase tests[] = {
        {"example 1", {3,6,7,11}, 4, 8, 4},
        {"example 2", {30,11,23,4,20}, 5, 5, 30},
        {"example 3", {30,11,23,4,20}, 5, 6, 23},
        {"single pile single hour", {1}, 1, 1, 1},
        {"single pile many hours", {312884470}, 1, 970709593, 1},
        {"all ones h equals length", {1,1,1,1}, 4, 4, 1},
        {"large values tight deadline", {1000000000,1000000000}, 2, 3, 1000000000},
        {"uniform piles extra hours", {5,5,5,5,5}, 5, 10, 3},
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  875. Koko Eating Bananas\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = minEatingSpeed(tests[i].piles, tests[i].piles_n, tests[i].h);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
