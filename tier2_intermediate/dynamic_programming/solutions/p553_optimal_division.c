/*
 * P553: Optimal Division [PREMIUM] (Medium)
 * https://leetcode.com/problems/optimal-division/
 * Topics: Array, Math, Dynamic Programming
 *
 * You are given an integer array nums. The adjacent integers in nums will perform the float division.
 * However, you can add any number of parenthesis at any position to change the priority of operations. You want to add these parentheses such the value of the expression after the evaluation is maximum.
 * Return the corresponding expression that has the maximum value in string format.
 * Note: your expression should not contain redundant parenthesis.
 * Example 1:
 *     Input: nums = [1000,100,10,2]
 *     Output: "1000/(100/10/2)"
 *     Explanation: 1000/(100/10/2) = 1000/((100/10)/2) = 200
 *     However, the bold parenthesis in "1000/((100/10)/2)" are redundant since they do not influence the operation priority.
 *     So you should return "1000/(100/10/2)".
 *     Other cases:
 *     1000/(100/10)/2 = 50
 *     1000/(100/(10/2)) = 50
 *     1000/100/10/2 = 0.5
 *     1000/100/(10/2) = 2
 *
 * Example 2:
 *     Input: nums = [2,3,4]
 *     Output: "2/(3/4)"
 *     Explanation: (2/(3/4)) = 8/3 = 2.667
 *     It can be shown that after trying all possibilities, we cannot get an expression with evaluation greater than 2.667
 *
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - 2 <= nums[i] <= 1000
 *     - There is only one optimal division for the given input.
 *
 * Template (python3):
 *     class Solution:
 *         def optimalDivision(self, nums: List[int]) -> str:
 */


#include "ctest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *optimalDivision(int *nums, int numsSize) {
    if (numsSize == 1) {
        char *r = (char *)malloc(12);
        sprintf(r, "%d", nums[0]);
        return r;
    }
    if (numsSize == 2) {
        char *r = (char *)malloc(24);
        sprintf(r, "%d/%d", nums[0], nums[1]);
        return r;
    }
    int cap = 120;
    char *r = (char *)malloc(cap);
    int pos = sprintf(r, "%d/(", nums[0]);
    for (int i = 1; i < numsSize; i++) {
        if (i > 1) pos += sprintf(r + pos, "/");
        pos += sprintf(r + pos, "%d", nums[i]);
    }
    pos += sprintf(r + pos, ")");
    return r;
}

int main(void) {
    int passed = 0;
    int total = 5;
    struct TC { const char *label; int nums[10]; int sz; const char *expected; };
    struct TC tests[] = {
        {"example 1", {1000,100,10,2}, 4, "1000/(100/10/2)"},
        {"example 2", {2,3,4}, 3, "2/(3/4)"},
        {"two elements no parens", {2,3}, 2, "2/3"},
        {"single element", {2}, 1, "2"},
        {"three elements", {10,2,5}, 3, "10/(2/5)"},
    };
    for (int i = 0; i < total; i++) {
        char *got = optimalDivision(tests[i].nums, tests[i].sz);
        if (strcmp(got, tests[i].expected) == 0) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected \"%s\", got \"%s\")\n", i + 1, tests[i].label, tests[i].expected, got);
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, total);
    return passed == total ? 0 : 1;
}
