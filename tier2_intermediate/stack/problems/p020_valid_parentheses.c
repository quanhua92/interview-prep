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
 * Hint: Use a stack to match opening and closing brackets.
 */

#include "io.h"
#include <stdlib.h>

static int is_valid(const char *s) {
    abort();
}

int main(void)
{
    char *s = read_line();
    write_bool(is_valid(s));
    free(s);
    return 0;
}
