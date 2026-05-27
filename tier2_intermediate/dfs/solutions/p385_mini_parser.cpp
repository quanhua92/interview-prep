/*
 * P385: Mini Parser [PREMIUM] (Medium)
 * https://leetcode.com/problems/mini-parser/
 * Topics: String, Stack, Depth-First Search
 */

#include "io.h"
#include <string>

int main() {
    std::string s = read_line();
    if (s[0] != '[') {
        write_int(std::stoi(s));
    } else {
        write_string(s);
    }
    return 0;
}
