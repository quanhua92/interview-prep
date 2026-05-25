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


#include "ctest.h"
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
    if (result_count >= result_cap) {
        result_cap = result_cap ? result_cap * 2 : 16;
        result = realloc(result, result_cap * sizeof(char *));
    }
    path[digits_len] = '\0';
    result[result_count] = malloc(digits_len + 1);
    strcpy(result[result_count], path);
    result_count++;
}

static void backtrack(const char *digits, int index) {
    if (index == digits_len) {
        add_result();
        return;
    }
    const char *letters = phone_map[digits[index] - '0'];
    for (int i = 0; letters[i]; i++) {
        path[index] = letters[i];
        backtrack(digits, index + 1);
    }
}

static int cmp_str(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

static char **letterCombinations(const char *digits, int *returnSize) {
    digits_len = (int)strlen(digits);
    result = NULL;
    result_count = 0;
    result_cap = 0;
    if (digits_len == 0) {
        *returnSize = 0;
        return NULL;
    }
    path = malloc(digits_len + 1);
    backtrack(digits, 0);
    free(path);
    qsort(result, result_count, sizeof(char *), cmp_str);
    *returnSize = result_count;
    return result;
}

static int check_strs(char **got, int got_n, char **exp, int exp_n) {
    if (got_n != exp_n) return 0;
    qsort(got, got_n, sizeof(char *), cmp_str);
    qsort(exp, exp_n, sizeof(char *), cmp_str);
    for (int i = 0; i < got_n; i++) {
        if (strcmp(got[i], exp[i]) != 0) return 0;
    }
    return 1;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  17. Letter Combinations of a Phone Number\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int ret_sz;
        char **got = letterCombinations("23", &ret_sz);
        char *exp[] = {"ad","ae","af","bd","be","bf","cd","ce","cf"};
        if (check_strs(got, ret_sz, exp, 9)) {
            passed++; printf("  Test 1 (example 1): PASS\n");
        } else {
            printf("  Test 1 (example 1): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got);
    }
    {
        int ret_sz;
        char **got = letterCombinations("", &ret_sz);
        if (ret_sz == 0) {
            passed++; printf("  Test 2 (empty input): PASS\n");
        } else {
            printf("  Test 2 (empty input): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got);
    }
    {
        int ret_sz;
        char **got = letterCombinations("2", &ret_sz);
        char *exp[] = {"a","b","c"};
        if (check_strs(got, ret_sz, exp, 3)) {
            passed++; printf("  Test 3 (single digit): PASS\n");
        } else {
            printf("  Test 3 (single digit): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got);
    }
    {
        int ret_sz;
        char **got = letterCombinations("7", &ret_sz);
        char *exp[] = {"p","q","r","s"};
        if (check_strs(got, ret_sz, exp, 4)) {
            passed++; printf("  Test 4 (digit with 4 letters): PASS\n");
        } else {
            printf("  Test 4 (digit with 4 letters): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got);
    }
    {
        int ret_sz;
        char **got = letterCombinations("9", &ret_sz);
        char *exp[] = {"w","x","y","z"};
        if (check_strs(got, ret_sz, exp, 4)) {
            passed++; printf("  Test 5 (digit 9): PASS\n");
        } else {
            printf("  Test 5 (digit 9): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got);
    }
    {
        int ret_sz;
        char **got = letterCombinations("79", &ret_sz);
        char *exp[] = {
            "pw","px","py","pz","qw","qx","qy","qz",
            "rw","rx","ry","rz","sw","sx","sy","sz",
        };
        if (check_strs(got, ret_sz, exp, 16)) {
            passed++; printf("  Test 6 (two 4-letter digits): PASS\n");
        } else {
            printf("  Test 6 (two 4-letter digits): FAIL\n");
        }
        for (int i = 0; i < ret_sz; i++) free(got[i]);
        free(got);
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
