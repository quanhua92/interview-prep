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
    long long total = 0;
    for (int i = 0; i < m; i++) {
        total = total * k + 1;
        if (total > num) return total;
    }
    return total;
}

static int bit_length(long long n)
{
    int b = 0;
    while (n > 0) { b++; n >>= 1; }
    return b;
}

char *smallestGoodBase(char *n)
{
    long long num = 0;
    for (int i = 0; n[i]; i++) num = num * 10 + (n[i] - '0');

    char *result = (char *)malloc(30);
    sprintf(result, "%lld", num - 1);

    int max_m = bit_length(num);
    for (int m = max_m; m >= 2; m--) {
        long long lo = 2;
        long long hi = (long long)powl((double)num, 1.0 / (m - 1)) + 2;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            long long s = calc(mid, m, num);
            if (s == num) {
                sprintf(result, "%lld", mid);
                return result;
            }
            if (s < num) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return result;
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
