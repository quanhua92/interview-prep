/*
 * P278: First Bad Version (Easy)
 * https://leetcode.com/problems/first-bad-version/
 * Topics: Binary Search, Interactive
 * 
 * You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
 * You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
 * 
 * Example 1:
 *     Input: n = 5, bad = 4
 *     Output: 4
 *     Explanation:
 *     call isBadVersion(3) -> false
 *     call isBadVersion(5) -> true
 *     call isBadVersion(4) -> true
 *     Then 4 is the first bad version.
 * 
 * Example 2:
 *     Input: n = 1, bad = 1
 *     Output: 1
 * 
 * Constraints:
 *     - 1 <= bad <= n <= 231 - 1
 * 
 * Template (python3):
 *     # The isBadVersion API is already defined for you.
 *     # def isBadVersion(version: int) -> bool:
 * 
 *     class Solution:
 *         def firstBadVersion(self, n: int) -> int:
 * 
 * Hint: Binary search for the leftmost version where is_bad is True.
 */
#include <stdio.h>
#include <stdlib.h>

static int g_bad;

static int firstBadVersion(int n, int bad)
{
    abort();
}

int main(void)
{
    struct { const char *label; long long n; int bad; int expected; int pass; } tests[] = {
        { "example 1", 5, 4, 4, 0 },
        { "single version, bad", 1, 1, 1, 0 },
        { "last version is bad", 3, 3, 3, 0 },
        { "middle version is bad", 10, 7, 7, 0 },
        { "first version is bad", 2, 1, 1, 0 },
        { "large n, last is bad", 100, 100, 100, 0 },
        { "large n, first is bad", 100000, 1, 1, 0 },
        { "small n last bad", 2, 2, 2, 0 },
        { "large n near end", 1000000, 999999, 999999, 0 },
        { "max int overflow safe", 2147483647LL, 1, 1, 0 },
    };
    int tn = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    for (int i = 0; i < tn; i++) {
        int got = firstBadVersion((int)tests[i].n, tests[i].bad);
        tests[i].pass = (got == tests[i].expected);
        if (tests[i].pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  278. First Bad Version\n");
    printf("============================================================\n");
    for (int i = 0; i < tn; i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, tn);
    printf("============================================================\n");
    return passed == tn ? 0 : 1;
}
