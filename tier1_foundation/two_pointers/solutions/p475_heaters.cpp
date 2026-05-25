/*
 * P475: Heaters [PREMIUM] (Medium)
 * https://leetcode.com/problems/heaters/
 * Topics: Array, Two Pointers, Binary Search, Sorting
 *
 * Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.
 * Every house can be warmed, as long as the house is within the heater's warm radius range.
 * Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.
 * Notice that all the heaters follow your radius standard, and the warm radius will the same.
 * Example 1:
 *     Input: houses = [1,2,3], heaters = [2]
 *     Output: 1
 *     Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
 *
 * Example 2:
 *     Input: houses = [1,2,3,4], heaters = [1,4]
 *     Output: 1
 *     Explanation: The two heaters were placed at positions 1 and 4. We need to use a radius 1 standard, then all the houses can be warmed.
 *
 * Example 3:
 *     Input: houses = [1,5], heaters = [2]
 *     Output: 3
 *
 * Constraints:
 *     - 1 <= houses.length, heaters.length <= 3 * 104
 *     - 1 <= houses[i], heaters[i] <= 109
 *
 * Template (python3):
 *     class Solution:
 *         def findRadius(self, houses: List[int], heaters: List[int]) -> int:
 */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <cstdlib>
#include <vector>

int findRadius(std::vector<int> houses, std::vector<int> heaters)
{
    std::sort(houses.begin(), houses.end());
    std::sort(heaters.begin(), heaters.end());
    int result = 0;
    int j = 0;
    for (int i = 0; i < (int)houses.size(); i++) {
        while (j + 1 < (int)heaters.size() && abs(houses[i] - heaters[j]) >= abs(houses[i] - heaters[j + 1]))
            j++;
        result = std::max(result, abs(houses[i] - heaters[j]));
    }
    return result;
}

int main(void)
{
    struct TC {
        const char *label;
        std::vector<int> houses;
        std::vector<int> heaters;
        int expected;
    };
    TC tests[] = {
        {"example 1",               {1, 2, 3},       {2},          1},
        {"example 2",               {1, 2, 3, 4},    {1, 4},       1},
        {"example 3",               {1, 5},          {2},          3},
        {"house at heater position", {1},            {1},          0},
        {"houses between heaters",  {1, 2, 3, 4, 5, 6}, {1, 6},    2},
        {"single heater center",    {10, 20, 30},    {15},         15},
        {"all houses before heaters", {1, 2, 3},    {4, 5, 6},    3},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  475. Heaters\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = findRadius(tests[i].houses, tests[i].heaters);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
