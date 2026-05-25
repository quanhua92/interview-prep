/*
 * P434: Number of Segments in a String [PREMIUM] (Easy)
 * https://leetcode.com/problems/number-of-segments-in-a-string/
 * Topics: String
 *
 * Given a string s, return the number of segments in the string.
 * A segment is defined to be a contiguous sequence of non-space characters.
 * Example 1:
 *     Input: s = "Hello, my name is John"
 *     Output: 5
 *     Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]
 *
 * Example 2:
 *     Input: s = "Hello"
 *     Output: 1
 *
 * Constraints:
 *     - 0 <= s.length <= 300
 *     - s consists of lowercase and uppercase English letters, digits, or one of the following characters "!@#$%^&*()_+-=',.:".
 *     - The only space character in s is ' '.
 *
 * Template (python3):
 *     class Solution:
 *         def countSegments(self, s: str) -> int:
 */


#include "cpptest.h"

int countSegments(const std::string &s)
{
    int count = 0;
    bool in_segment = false;
    for (char c : s) {
        if (c != ' ' && !in_segment) {
            count++;
            in_segment = true;
        } else if (c == ' ') {
            in_segment = false;
        }
    }
    return count;
}

void __attribute__((unused)) _use_harness_fns(void)
{
    (void)print_arr;
}

int main()
{
    struct { const char *s; int expected; const char *label; } tests[] = {
        {"Hello, my name is John", 5, "example 1"},
        {"Hello", 1, "example 2"},
        {"", 0, "empty string"},
        {"   ", 0, "only spaces"},
        {"    foo    bar   ", 2, "leading/trailing/multiple spaces"},
        {"a b c d e", 5, "single char segments"},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = countSegments(tests[i].s);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
