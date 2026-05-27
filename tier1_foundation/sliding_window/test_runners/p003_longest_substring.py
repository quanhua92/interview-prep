from src.utils.judge_base import JudgeBase, TestCase, register


class P003LongestSubstring(JudgeBase):
    name = "3. Longest Substring Without Repeating Characters"
    test_cases = [
        TestCase(input="abcabcbb", expected=3, label="example 1"),
        TestCase(input="bbbbb", expected=1, label="example 2"),
        TestCase(input="pwwkew", expected=3, label="example 3"),
        TestCase(input="", expected=0, label="empty string"),
        TestCase(input="a", expected=1, label="single character"),
        TestCase(input=" ", expected=1, label="single space"),
        TestCase(input="au", expected=2, label="two unique chars"),
        TestCase(input="dvdf", expected=3, label="reset from duplicate after unique prefix"),
        TestCase(input="tmmzuxt", expected=5, label="char seen before current window"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P003LongestSubstring)
