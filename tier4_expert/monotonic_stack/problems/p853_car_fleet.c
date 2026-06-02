/*
 * P853: Car Fleet (Medium)
 * https://leetcode.com/problems/car-fleet/
 * Topics: Array, Stack, Sorting, Monotonic Stack
 *
 * There are n cars at given miles away from the starting mile 0, traveling to reach the mile target.
 * You are given two integer arrays position and speed, both of length n, where position[i] is the starting mile of the ith car and speed[i] is the speed of the ith car in miles per hour.
 * A car cannot pass another car, but it can catch up and then travel next to it at the speed of the slower car.
 * A car fleet is a car or cars driving next to each other. The speed of the car fleet is the minimum speed of any car in the fleet.
 * If a car catches up to a car fleet at the mile target, it will still be considered as part of the car fleet.
 * Return the number of car fleets that will arrive at the destination.
 *
 * Example 1:
 *     Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
 *     Output: 3
 *
 * Example 2:
 *     Input: target = 10, position = [3], speed = [3]
 *     Output: 1
 *
 * Example 3:
 *     Input: target = 100, position = [0,2,4], speed = [4,2,1]
 *     Output: 1
 *
 * Constraints:
 *     - n == position.length == speed.length
 *     - 1 <= n <= 10^5
 *     - 0 < target <= 10^6
 *     - 0 <= position[i] < target
 *     - All the values of position are unique.
 *     - 0 < speed[i] <= 10^6
 *
 * Template (python3):
 *     class Solution:
 *         def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
 *
 * Hint: Sort by position desc, calculate time to target. A car forms a new fleet only if it arrives before the current fleet.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

typedef struct { int pos; int spd; } Car;

static int cmp_car(const void *a, const void *b)
{
    const Car *ca = (const Car *)a, *cb = (const Car *)b;
    return cb->pos - ca->pos;
}

int carFleet(int target, int *position, int *speed, int n)
{
    abort();
}

int main(void)
{
    int target = read_int();
    int pos_n;
    int *position = read_ints(&pos_n);
    int spd_n;
    int *speed = read_ints(&spd_n);
    write_int(carFleet(target, position, speed, pos_n));
    free(position);
    free(speed);
    return 0;
}
