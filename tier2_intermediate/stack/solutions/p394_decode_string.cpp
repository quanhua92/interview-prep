/*
 * P394: Decode String (Medium)
 * https://leetcode.com/problems/decode-string/
 * Topics: String, Stack, Recursion
 *
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.
 *
 * Hint: Use a stack to handle nested k[encoded] patterns.
 */

#include "io.h"
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

int main(void)
{
    std::string s = read_line();
    write_string(decodeString(s));
    return 0;
}
