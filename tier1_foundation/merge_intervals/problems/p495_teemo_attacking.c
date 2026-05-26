/*
 * P495: Teemo Attacking [PREMIUM] (Easy)
 * https://leetcode.com/problems/teemo-attacking/
 * Topics: Array, Simulation
 * 
 * Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a exactly duration seconds. More formally, an attack at second t will mean Ashe is poisoned during the inclusive time interval [t, t + duration - 1]. If Teemo attacks again before the poison effect ends, the timer for it is reset, and the poison effect will end duration seconds after the new attack.
 * You are given a non-decreasing integer array timeSeries, where timeSeries[i] denotes that Teemo attacks Ashe at second timeSeries[i], and an integer duration.
 * Return the total number of seconds that Ashe is poisoned.
 * Example 1:
 *     Input: timeSeries = [1,4], duration = 2
 *     Output: 4
 *     Explanation: Teemo's attacks on Ashe go as follows:
 *     - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
 *     - At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
 *     Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.
 * 
 * Example 2:
 *     Input: timeSeries = [1,2], duration = 2
 *     Output: 3
 *     Explanation: Teemo's attacks on Ashe go as follows:
 *     - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
 *     - At second 2 however, Teemo attacks again and resets the poison timer. Ashe is poisoned for seconds 2 and 3.
 *     Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.
 * 
 * Constraints:
 *     - 1 <= timeSeries.length <= 104
 *     - 0 <= timeSeries[i], duration <= 107
 *     - timeSeries is sorted in non-decreasing order.
 * 
 * Template (python3):
 *     class Solution:
 *         def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:
 */
#include <stdio.h>
#include <stdlib.h>

static int findPoisonedDuration(int *ts, int tsSize, int duration)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        int input[10];
        int input_n;
        int duration;
        int expected;
    } tests[] = {
        {"example 1",                {1, 4},                  2, 2, 4},
        {"example 2",                {1, 2},                  2, 2, 3},
        {"single attack",            {1},                     1, 2, 2},
        {"consecutive attacks, duration 1", {1,2,3,4,5},      5, 1, 5},
        {"non-overlapping attacks",  {1, 3, 5, 7, 9},         5, 2, 10},
        {"duplicate timestamps",     {1, 1, 1, 1},            4, 5, 5},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = findPoisonedDuration(tests[i].input, tests[i].input_n, tests[i].duration);
        if (got == tests[i].expected) {
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
            passed++;
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
