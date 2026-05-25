/*
 * P20: Valid Parentheses (Easy)
 * https://leetcode.com/problems/valid-parentheses/
 * Topics: String, Stack
 * 
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * An input string is valid if:
 * 
 * Example 1:
 *     Input: s = "()"
 *     Output: true
 * 
 * Example 2:
 *     Input: s = "()[]{}"
 *     Output: true
 * 
 * Example 3:
 *     Input: s = "(]"
 *     Output: false
 * 
 * Example 4:
 *     Input: s = "([])"
 *     Output: true
 * 
 * Example 5:
 *     Input: s = "([)]"
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= s.length <= 104
 *     - s consists of parentheses only '()[]{}'.
 * 
 * Hints:
 *     - Use a stack of characters.
 *     - When you encounter an opening bracket, push it to the top of the stack.
 *     - When you encounter a closing bracket, check if the top of the stack was the opening for it. If yes, pop it from the stack. Otherwise, return false.
 * 
 * Template (python3):
 *     class Solution:
 *         def isValid(self, s: str) -> bool:
 * 
 * Hint: Use a stack to match opening and closing brackets.
 */
#include "cpptest.h"
#include <string>
#include <stack>

static bool isValid(const std::string &s) {
    /* TODO: Implement */
    return 0;
}

int main() {
    (void)print_arr;

    struct { const char *input; bool expected; const char *label; } tests[] = {
        {"()", true, "simple pair"},
        {"()[]{}", true, "mixed brackets"},
        {"(]", false, "mismatched"},
        {"([)]", false, "interleaved"},
        {"{[]}", true, "nested"},
        {"(", false, "single opening"},
        {")", false, "single closing"},
        {"((((", false, "only openings"},
        {"))))", false, "only closings"},
        {"((({{{[[[]]]}}})))", true, "deeply nested"},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  20. Valid Parentheses\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        bool got = isValid(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %s\n    Got:      %s\n",
                   tests[i].expected ? "true" : "false", got ? "true" : "false");
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
