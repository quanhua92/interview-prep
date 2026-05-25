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
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

static long long calc(long long k, int m, long long num)
{
    /* TODO: Implement */
    return 0;
}

std::string smallestGoodBase(std::string n)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct Tc { const char *label; std::string input; std::string expected; bool pass; };
    std::vector<Tc> tests = {
        {"example 1", "13", "3", false},
        {"example 2", "4681", "8", false},
        {"example 3", "1000000000000000000", "999999999999999999", false},
        {"smallest n equals 11 base 2", "3", "2", false},
        {"111 base 2", "7", "2", false},
        {"11111 base 2", "31", "2", false},
    };

    int passed = 0;
    for (auto &tc : tests) {
        std::string got = smallestGoodBase(tc.input);
        tc.pass = (got == tc.expected);
        if (tc.pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  483. Smallest Good Base\n");
    printf("============================================================\n");
    for (int i = 0; i < (int)tests.size(); i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n");
    return passed == (int)tests.size() ? 0 : 1;
}
