/*
 * P495: Teemo Attacking [PREMIUM] (Easy)
 * https://leetcode.com/problems/teemo-attacking/
 * Topics: Array, Simulation
 *
 * Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a exactly duration seconds.
 * You are given a non-decreasing integer array timeSeries, and an integer duration.
 * Return the total number of seconds that Ashe is poisoned.
 *
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
#include <vector>

int solve(const std::vector<int> &timeSeries, int duration)
{
    abort();
}

int main()
{
    std::vector<int> timeSeries = read_ints();
    int duration = read_int();
    write_int(solve(timeSeries, duration));
    return 0;
}
