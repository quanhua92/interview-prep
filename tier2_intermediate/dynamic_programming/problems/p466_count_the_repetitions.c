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
#include <string.h>

int getMaxRepetitions(const char *s1, int n1, const char *s2, int n2) {
    abort();
}

int main(void) {
    char buf1[256], buf2[256];
    read_line(buf1, sizeof(buf1));
    int n1 = read_int();
    read_line(buf2, sizeof(buf2));
    int n2 = read_int();
    write_int(getMaxRepetitions(buf1, n1, buf2, n2));
    return 0;
}
