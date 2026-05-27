from src.utils.judge_base import JudgeBase, TestCase, register


class P438FindAnagrams(JudgeBase):
    name = "438. Find All Anagrams in a String"
    test_cases = [
        TestCase(input=("cbaebabacd", "abc"), expected=[0, 6], label="example 1"),
        TestCase(input=("abab", "ab"), expected=[0, 1, 2], label="example 2"),
        TestCase(input=("af", "bf"), expected=[], label="no anagrams"),
        TestCase(input=("abc", "abc"), expected=[0], label="exact match single"),
        TestCase(input=("aaaaaaaaaa", "aa"), expected=[0, 1, 2, 3, 4, 5, 6, 7, 8], label="all same chars"),
        TestCase(input=("abacbabc", "abc"), expected=[1, 2, 3, 5], label="overlapping anagrams"),
        TestCase(input=("a", "aa"), expected=[], label="pattern longer than string"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_string(tc_input[0]),
            self.serialize_string(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P438FindAnagrams)
