/*
 * P483: Smallest Good Base [PREMIUM] (Hard)
 * https://leetcode.com/problems/smallest-good-base/
 * Topics: Math, Binary Search
 * 
 * Given an integer n represented as a string, return the smallest good base of n.
 * We call k >= 2 a good base of n, if all digits of n base k are 1's.
 * Example 1:
 *     Input: n = "13"
 *     Output: "3"
 *     Explanation: 13 base 3 is 111.
 * 
 * Example 2:
 *     Input: n = "4681"
 *     Output: "8"
 *     Explanation: 4681 base 8 is 11111.
 * 
 * Example 3:
 *     Input: n = "1000000000000000000"
 *     Output: "999999999999999999"
 *     Explanation: 1000000000000000000 base 999999999999999999 is 11.
 * 
 * Constraints:
 *     - n is an integer in the range [3, 1018].
 *     - n does not contain any leading zeros.
 * 
 * Template (python3):
 *     class Solution:
 *         def smallestGoodBase(self, n: str) -> str:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static long long calc(long long k, int m, long long num)
{
    abort();
}

static int bit_length(long long n)
{
    abort();
}

char *smallestGoodBase(char *n)
{
    abort();
}

int main(void)
{
    struct { const char *label; char input[30]; const char *expected; int pass; } tests[] = {
        { "example 1", "13", "3", 0 },
        { "example 2", "4681", "8", 0 },
        { "example 3", "1000000000000000000", "999999999999999999", 0 },
        { "smallest n equals 11 base 2", "3", "2", 0 },
        { "111 base 2", "7", "2", 0 },
        { "11111 base 2", "31", "2", 0 },
    };
    int tn = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    for (int i = 0; i < tn; i++) {
        char buf[30];
        strcpy(buf, tests[i].input);
        char *got = smallestGoodBase(buf);
        tests[i].pass = (strcmp(got, tests[i].expected) == 0);
        if (tests[i].pass) passed++;
        free(got);
    }

    printf("\n============================================================\n");
    printf("  483. Smallest Good Base\n");
    printf("============================================================\n");
    for (int i = 0; i < tn; i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, tn);
    printf("============================================================\n");
    return passed == tn ? 0 : 1;
}
