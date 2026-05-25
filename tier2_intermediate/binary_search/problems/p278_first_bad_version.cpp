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
#include <cstdio>
#include <vector>

static int g_bad;

int firstBadVersion(long long n, int bad)
{
    abort();
}

int main(void)
{
    struct Tc { const char *label; long long n; int bad; int expected; bool pass; };
    std::vector<Tc> tests = {
        {"example 1", 5, 4, 4, false},
        {"single version, bad", 1, 1, 1, false},
        {"last version is bad", 3, 3, 3, false},
        {"middle version is bad", 10, 7, 7, false},
        {"first version is bad", 2, 1, 1, false},
        {"large n, last is bad", 100, 100, 100, false},
        {"large n, first is bad", 100000, 1, 1, false},
        {"small n last bad", 2, 2, 2, false},
        {"large n near end", 1000000, 999999, 999999, false},
        {"max int overflow safe", 2147483647LL, 1, 1, false},
    };

    int passed = 0;
    for (auto &tc : tests) {
        int got = firstBadVersion(tc.n, tc.bad);
        tc.pass = (got == tc.expected);
        if (tc.pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  278. First Bad Version\n");
    printf("============================================================\n");
    for (int i = 0; i < (int)tests.size(); i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n");
    return passed == (int)tests.size() ? 0 : 1;
}
