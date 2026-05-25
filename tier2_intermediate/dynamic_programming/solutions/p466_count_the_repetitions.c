/*
 * P466: Count The Repetitions [PREMIUM] (Hard)
 * https://leetcode.com/problems/count-the-repetitions/
 * Topics: String, Dynamic Programming
 *
 * We define str = [s, n] as the string str which consists of the string s concatenated n times.
 * We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
 * You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
 * Return the maximum integer m such that str = [str2, m] can be obtained from str1.
 * Example 1:
 *     Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
 *     Output: 2
 *
 * Example 2:
 *     Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= s1.length, s2.length <= 100
 *     - s1 and s2 consist of lowercase English letters.
 *     - 1 <= n1, n2 <= 106
 *
 * Template (python3):
 *     class Solution:
 *         def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
 */


#include "ctest.h"
#include <string.h>

int getMaxRepetitions(const char *s1, int n1, const char *s2, int n2) {
    if (n1 == 0) return 0;
    int s1_len = (int)strlen(s1);
    int s2_len = (int)strlen(s2);
    int s1_count[26] = {0};
    for (int i = 0; i < s1_len; i++) s1_count[(unsigned char)s1[i] - 'a']++;
    for (int i = 0; i < s2_len; i++) {
        if (!s1_count[(unsigned char)s2[i] - 'a']) return 0;
    }
    int prev_iter[101];
    int prev_count[101];
    memset(prev_iter, -1, sizeof(prev_iter));
    memset(prev_count, 0, sizeof(prev_count));
    int count = 0;
    int s2_idx = 0;
    int found_cycle = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < s1_len; j++) {
            if (s1[j] == s2[s2_idx]) {
                s2_idx++;
                if (s2_idx == s2_len) {
                    count++;
                    s2_idx = 0;
                }
            }
        }
        if (!found_cycle && prev_iter[s2_idx] >= 0) {
            found_cycle = 1;
            int cycle_len = i - prev_iter[s2_idx];
            int cycle_count = count - prev_count[s2_idx];
            int remaining = n1 - 1 - i;
            int full_cycles = remaining / cycle_len;
            count += full_cycles * cycle_count;
            int processed = i + full_cycles * cycle_len + 1;
            for (int ii = processed; ii < n1; ii++) {
                for (int jj = 0; jj < s1_len; jj++) {
                    if (s1[jj] == s2[s2_idx]) {
                        s2_idx++;
                        if (s2_idx == s2_len) {
                            count++;
                            s2_idx = 0;
                        }
                    }
                }
            }
            break;
        }
        if (!found_cycle) {
            prev_iter[s2_idx] = i;
            prev_count[s2_idx] = count;
        }
    }
    return count / n2;
}

int main(void) {
    int passed = 0;
    int total = 6;
    struct TC { const char *label; const char *s1; int n1; const char *s2; int n2; int expected; };
    struct TC tests[] = {
        {"example 1", "acb", 4, "ab", 2, 2},
        {"example 2", "acb", 1, "acb", 1, 1},
        {"single char repeated", "a", 100, "a", 1, 100},
        {"impossible char", "a", 1, "b", 1, 0},
        {"each s1 yields one s2 match", "abc", 10, "ac", 1, 10},
        {"overlap matching", "aba", 3, "ab", 1, 3},
    };
    for (int i = 0; i < total; i++) {
        int got = getMaxRepetitions(tests[i].s1, tests[i].n1, tests[i].s2, tests[i].n2);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, total);
    return passed == total ? 0 : 1;
}
