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

#include "io.h"
#include <stdlib.h>
#include <string.h>

int getMaxRepetitions(const char *s1, int n1, const char *s2, int n2) {
    abort();
}

int main(void) {
    char *s1 = read_line();
    int ic1; int *ia1 = read_ints(&ic1); int n1 = ia1[0]; free(ia1);
    char *s2 = read_line();
    int ic2; int *ia2 = read_ints(&ic2); int n2 = ia2[0]; free(ia2);
    int result = getMaxRepetitions(s1, n1, s2, n2);
    free(s1); free(s2);
    write_int(result);
    return 0;
}
