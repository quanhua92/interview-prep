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
 *     Explanation:
 *
 * Example 2:
 *     Input: target = 10, position = [3], speed = [3]
 *     Output: 1
 *     Explanation:
 *
 * Example 3:
 *     Input: target = 100, position = [0,2,4], speed = [4,2,1]
 *     Output: 1
 *     Explanation:
 *
 * Constraints:
 *     - n == position.length == speed.length
 *     - 1 <= n <= 105
 *     - 0 < target <= 106
 *     - 0 <= position[i] < target
 *     - All the values of position are unique.
 *     - 0 < speed[i] <= 106
 *
 * Template (python3):
 *     class Solution:
 *         def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
 *
 * Hint: Sort by position desc, calculate time to target. A car forms a new fleet only if it arrives before the current fleet.
 */


#include <stdio.h>
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
    if (n == 0) return 0;
    Car *cars = malloc(n * sizeof(Car));
    for (int i = 0; i < n; i++) {
        cars[i].pos = position[i];
        cars[i].spd = speed[i];
    }
    qsort(cars, n, sizeof(Car), cmp_car);

    int fleets = 0;
    double slowest = -1.0;
    for (int i = 0; i < n; i++) {
        double time = (double)(target - cars[i].pos) / cars[i].spd;
        if (time > slowest) {
            fleets++;
            slowest = time;
        }
    }
    free(cars);
    return fleets;
}

int main(void)
{
    int passed = 0, total = 6;
    printf("\n============================================================\n");
    printf("  853. Car Fleet\n");
    printf("============================================================\n");

    {
        int pos[] = {10, 8, 0, 5, 3}, spd[] = {2, 4, 1, 1, 3};
        int got = carFleet(12, pos, spd, 5);
        if (got == 3) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: 3, Got: %d\n", got); }
    }
    {
        int pos[] = {3}, spd[] = {3};
        int got = carFleet(10, pos, spd, 1);
        if (got == 1) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int pos[] = {0, 2, 4}, spd[] = {4, 2, 1};
        int got = carFleet(100, pos, spd, 3);
        if (got == 1) { passed++; printf("  Test 3 (all merge): PASS\n"); }
        else { printf("  Test 3 (all merge): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int pos[] = {8, 0}, spd[] = {2, 1};
        int got = carFleet(10, pos, spd, 2);
        if (got == 2) { passed++; printf("  Test 4 (two cars no merge): PASS\n"); }
        else { printf("  Test 4 (two cars no merge): FAIL\n  Expected: 2, Got: %d\n", got); }
    }
    {
        int pos[] = {0, 3}, spd[] = {3, 2};
        int got = carFleet(10, pos, spd, 2);
        if (got == 1) { passed++; printf("  Test 5 (two cars merge): PASS\n"); }
        else { printf("  Test 5 (two cars merge): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int pos[] = {1, 2, 3}, spd[] = {1, 1, 1};
        int got = carFleet(10, pos, spd, 3);
        if (got == 3) { passed++; printf("  Test 6 (all same speed): PASS\n"); }
        else { printf("  Test 6 (all same speed): FAIL\n  Expected: 3, Got: %d\n", got); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
