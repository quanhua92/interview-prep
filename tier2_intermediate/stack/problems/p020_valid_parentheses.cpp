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
 * Constraints:
 *     - 1 <= s.length <= 104
 *     - s consists of parentheses only '()[]{}'.
 *
 * Hint: Use a stack to match opening and closing brackets.
 */

#include "io.h"
#include <string>
#include <stack>

static bool isValid(const std::string &s) {
    abort();
}

int main(void)
{
    std::string s = read_line();
    write_bool(isValid(s));
    return 0;
}
