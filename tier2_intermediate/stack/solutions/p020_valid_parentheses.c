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

#include "ctest.h"

static int is_valid(const char *s) {
    char stack[10001];
    int top = 0;
    for (int i = 0; s[i]; i++) {
        char ch = s[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            stack[top++] = ch;
        } else {
            if (top == 0) return 0;
            char open = stack[--top];
            if ((ch == ')' && open != '(') ||
                (ch == ']' && open != '[') ||
                (ch == '}' && open != '{')) return 0;
        }
    }
    return top == 0;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    struct { const char *input; int expected; const char *label; } tests[] = {
        {"()", 1, "simple pair"},
        {"()[]{}", 1, "mixed brackets"},
        {"(]", 0, "mismatched"},
        {"([)]", 0, "interleaved"},
        {"{[]}", 1, "nested"},
        {"(", 0, "single opening"},
        {")", 0, "single closing"},
        {"((((", 0, "only openings"},
        {"))))", 0, "only closings"},
        {"((({{{[[[]]]}}})))", 1, "deeply nested"},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  20. Valid Parentheses\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        int got = is_valid(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
