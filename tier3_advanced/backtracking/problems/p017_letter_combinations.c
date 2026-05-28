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
 * Hint: Map each digit to its letters and use backtracking to build all combinations.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static const char *phone_map[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

static char **result;
static char *path;
static int result_count;
static int result_cap;
static int digits_len;

static void add_result(void) {
    abort();
}

static void backtrack(const char *digits, int index) {
    abort();
}

static int cmp_str(const void *a, const void *b) {
    abort();
}

int main(void) {
    char *digits = read_line();
    digits_len = (int)strlen(digits);
    result = NULL;
    result_count = 0;
    result_cap = 0;
    if (digits_len == 0) {
        free(digits);
        return 0;
    }
    path = malloc(digits_len + 1);
    backtrack(digits, 0);
    free(path);
    qsort(result, result_count, sizeof(char *), cmp_str);
    for (int i = 0; i < result_count; i++) {
        write_string(result[i]);
        free(result[i]);
    }
    free(result);
    free(digits);
    return 0;
}
