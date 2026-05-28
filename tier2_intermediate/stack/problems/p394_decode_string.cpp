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
    abort();
}

int main(void)
{
    std::string s = read_line();
    write_string(decodeString(s));
    return 0;
}
