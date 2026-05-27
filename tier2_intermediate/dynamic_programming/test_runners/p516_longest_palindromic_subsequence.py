from src.utils.judge_base import JudgeBase, TestCase, register


class P516LongestPalindromicSubsequence(JudgeBase):
    name = "516. Longest Palindromic Subsequence"
    test_cases = [
        TestCase(input="bbbab", expected=4, label="example 1"),
        TestCase(input="cbbd", expected=2, label="example 2"),
        TestCase(input="a", expected=1, label="single char"),
        TestCase(input="aa", expected=2, label="two same chars"),
        TestCase(input="abcdef", expected=1, label="all distinct"),
        TestCase(input="aabbaa", expected=6, label="full palindrome"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P516LongestPalindromicSubsequence)
