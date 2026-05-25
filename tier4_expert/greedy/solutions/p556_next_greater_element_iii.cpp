/*
 * P556: Next Greater Element III [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-iii/
 * Topics: Math, Two Pointers, String
 *
 * Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
 * Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
 * Example 1:
 *     Input: n = 12
 *     Output: 21
 *
 * Example 2:
 *     Input: n = 21
 *     Output: -1
 *
 * Constraints:
 *     - 1 <= n <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElement(self, n: int) -> int:
 */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
using namespace std;

int nextGreaterElement(int n) {
    string digits = to_string(n);
    int i = (int)digits.size() - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) i--;
    if (i < 0) return -1;
    int j = (int)digits.size() - 1;
    while (digits[j] <= digits[i]) j--;
    swap(digits[i], digits[j]);
    reverse(digits.begin() + i + 1, digits.end());
    long long val = stoll(digits);
    if (val > 2147483647LL) return -1;
    return (int)val;
}

int main() {
    printf("\n============================================================\n");
    printf("  556. Next Greater Element III\n");
    printf("============================================================\n");
    struct T { const char *label; int input; int expected; };
    std::vector<T> tests = {
        {"example 1", 12, 21},
        {"example 2", 21, -1},
        {"single digit", 1, -1},
        {"all same digits", 11, -1},
        {"classic example", 230241, 230412},
        {"max 32-bit int", 2147483647, -1},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        int got = nextGreaterElement(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d, Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n\n");
    return passed == (int)tests.size() ? 0 : 1;
}
