/*
 * P17: Letter Combinations of a Phone Number (Medium)
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * Topics: Hash Table, String, Backtracking
 *
 * Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
 * A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
 *
 * Example 1:
 *     Input: digits = "23"
 *     Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Example 2:
 *     Input: digits = ""
 *     Output: []
 *
 * Example 3:
 *     Input: digits = "2"
 *     Output: ["a","b","c"]
 *
 * Hint: Map each digit to its letters and use backtracking to build all combinations.
 */

#include "io.h"
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

static const std::string phone_map[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

static std::vector<std::string> letterCombinations(const std::string &digits) {
    if (digits.empty()) return {};
    std::vector<std::string> result;
    std::string path(digits.size(), '\0');
    const int n = (int)digits.size();

    std::function<void(int)> backtrack = [&](int index) {
        if (index == n) {
            result.push_back(path);
            return;
        }
        for (char c : phone_map[digits[index] - '0']) {
            path[index] = c;
            backtrack(index + 1);
        }
    };
    backtrack(0);
    std::sort(result.begin(), result.end());
    return result;
}

int main() {
    std::string digits = read_line();
    auto result = letterCombinations(digits);
    for (const auto &s : result) {
        write_string(s);
    }
    return 0;
}
