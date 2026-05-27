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
 *
 * Example 2:
 *     Input: timeSeries = [1,2], duration = 2
 *     Output: 3
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

#include "io.h"

int solve(int *ts, int tsSize, int duration)
{
    abort();
}

int main(void)
{
    int n;
    int *ts = read_ints(&n);
    int duration = read_int();
    write_int(solve(ts, n, duration));
    free(ts);
    return 0;
}
