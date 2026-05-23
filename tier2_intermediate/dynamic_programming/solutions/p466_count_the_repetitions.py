"""
P466: Count The Repetitions [PREMIUM] (Hard)
https://leetcode.com/problems/count-the-repetitions/
Topics: String, Dynamic Programming

We define str = [s, n] as the string str which consists of the string s concatenated n times.
We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
Return the maximum integer m such that str = [str2, m] can be obtained from str1.
Example 1:
    Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
    Output: 2

Example 2:
    Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
    Output: 1

Constraints:
    - 1 <= s1.length, s2.length <= 100
    - s1 and s2 consist of lowercase English letters.
    - 1 <= n1, n2 <= 106

Template (python3):
    class Solution:
        def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "466. Count The Repetitions"
    test_cases = [
        TestCase(input=("acb", 4, "ab", 2), expected=2, label="example 1"),
        TestCase(input=("acb", 1, "acb", 1), expected=1, label="example 2"),
        TestCase(input=("a", 100, "a", 1), expected=100, label="single char repeated"),
        TestCase(input=("a", 1, "b", 1), expected=0, label="impossible char"),
        TestCase(input=("abc", 10, "ac", 1), expected=10, label="each s1 yields one s2 match"),
        TestCase(input=("aba", 3, "ab", 1), expected=3, label="overlap matching"),
    ]

    def solve(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if n1 == 0:
            return 0
        s2_len, s1_len = len(s2), len(s1)
        # Check if all chars in s2 are in s1
        if not set(s2).issubset(set(s1)):
            return 0
        index_map: dict[int, tuple[int, int]] = {}
        count = 0
        s2_index = 0
        for i in range(n1):
            for j in range(s1_len):
                if s1[j] == s2[s2_index]:
                    s2_index += 1
                    if s2_index == s2_len:
                        count += 1
                        s2_index = 0
            if s2_index in index_map:
                prev_i, prev_count = index_map[s2_index]
                cycle_len = i - prev_i
                cycle_count = count - prev_count
                remaining = n1 - 1 - i
                full_cycles = remaining // cycle_len
                count += full_cycles * cycle_count
                processed = i + full_cycles * cycle_len + 1
                for ii in range(processed, n1):
                    for jj in range(s1_len):
                        if s1[jj] == s2[s2_index]:
                            s2_index += 1
                            if s2_index == s2_len:
                                count += 1
                                s2_index = 0
                break
            else:
                index_map[s2_index] = (i, count)
        return count // n2


if __name__ == "__main__":
    Solution().run()
