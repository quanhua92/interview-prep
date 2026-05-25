/*
 * P394: Decode String (Medium)
 * https://leetcode.com/problems/decode-string/
 * Topics: String, Stack, Recursion
 *
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 * You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
 * The test cases are generated so that the length of the output will never exceed 105.
 *
 * Example 1:
 *     Input: s = "3[a]2[bc]"
 *     Output: "aaabcbc"
 *
 * Example 2:
 *     Input: s = "3[a2[c]]"
 *     Output: "accaccacc"
 *
 * Example 3:
 *     Input: s = "2[abc]3[cd]ef"
 *     Output: "abcabccdcdcdef"
 *
 * Constraints:
 *     - 1 <= s.length <= 30
 *     - s consists of lowercase English letters, digits, and square brackets '[]'.
 *     - s is guaranteed to be a valid input.
 *     - All the integers in s are in the range [1, 300].
 *
 * Template (python3):
 *     class Solution:
 *         def decodeString(self, s: str) -> str:
 *
 * Hint: Use a stack to handle nested k[encoded] patterns.
 */

#include "cpptest.h"
#include <string>
#include <vector>
#include <utility>

static std::string decodeString(const std::string &s) {
    std::vector<std::pair<int, int>> stack;
    std::string result;
    int curr_num = 0;

    for (char ch : s) {
        if (ch >= '0' && ch <= '9') {
            curr_num = curr_num * 10 + (ch - '0');
        } else if (ch == '[') {
            stack.push_back({curr_num, (int)result.size()});
            curr_num = 0;
        } else if (ch == ']') {
            auto [repeat, start] = stack.back();
            stack.pop_back();
            std::string seg = result.substr(start);
            for (int j = 1; j < repeat; j++) result += seg;
        } else {
            result += ch;
        }
    }
    return result;
}

int main() {
    (void)print_arr;

    struct { const char *input; const char *expected; const char *label; } tests[] = {
        {"3[a]2[bc]", "aaabcbc", "example 1"},
        {"3[a2[c]]", "accaccacc", "nested"},
        {"2[abc]3[cd]ef", "abcabccdcdcdef", "multiple segments"},
        {"abc", "abc", "no encoding"},
        {"10[a]", "aaaaaaaaaa", "multi-digit multiplier"},
        {"2[2[2[a]]]", "aaaaaaaa", "deep nesting"},
        {"3[a]b", "aaab", "encoded then plain"},
        {"a2[b]c", "abbc", "plain-enc-plain"},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  394. Decode String\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        std::string got = decodeString(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %s\n    Got:      %s\n", tests[i].expected, got.c_str());
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
