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
 * Constraints:
 *     - 0 <= digits.length <= 4
 *     - digits[i] is a digit in the range ['2', '9'].
 * 
 * Template (python3):
 *     class Solution:
 *         def letterCombinations(self, digits: str) -> List[str]:
 * 
 * Hint: Map each digit to its letters and use backtracking to build all combinations.
 */
#include "cpptest.h"
#include <vector>
#include <string>
#include <algorithm>

static const std::string phone_map[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

static std::vector<std::string> letterCombinations(const std::string &digits) {
    /* TODO: Implement */
    return 0;
}

static bool check(const std::vector<std::string> &got, const std::vector<std::string> &exp) {
    /* TODO: Implement */
    return 0;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  17. Letter Combinations of a Phone Number\n");
    printf("============================================================\n");

    int passed = 0;

    {
        auto got = letterCombinations("23");
        std::vector<std::string> exp = {"ad","ae","af","bd","be","bf","cd","ce","cf"};
        if (check(got, exp)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        auto got = letterCombinations("");
        if (got.empty()) { passed++; printf("  Test 2 (empty input): PASS\n"); }
        else { printf("  Test 2 (empty input): FAIL\n"); }
    }
    {
        auto got = letterCombinations("2");
        std::vector<std::string> exp = {"a","b","c"};
        if (check(got, exp)) { passed++; printf("  Test 3 (single digit): PASS\n"); }
        else { printf("  Test 3 (single digit): FAIL\n"); }
    }
    {
        auto got = letterCombinations("7");
        std::vector<std::string> exp = {"p","q","r","s"};
        if (check(got, exp)) { passed++; printf("  Test 4 (digit with 4 letters): PASS\n"); }
        else { printf("  Test 4 (digit with 4 letters): FAIL\n"); }
    }
    {
        auto got = letterCombinations("9");
        std::vector<std::string> exp = {"w","x","y","z"};
        if (check(got, exp)) { passed++; printf("  Test 5 (digit 9): PASS\n"); }
        else { printf("  Test 5 (digit 9): FAIL\n"); }
    }
    {
        auto got = letterCombinations("79");
        std::vector<std::string> exp = {
            "pw","px","py","pz","qw","qx","qy","qz",
            "rw","rx","ry","rz","sw","sx","sy","sz",
        };
        if (check(got, exp)) { passed++; printf("  Test 6 (two 4-letter digits): PASS\n"); }
        else { printf("  Test 6 (two 4-letter digits): FAIL\n"); }
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
