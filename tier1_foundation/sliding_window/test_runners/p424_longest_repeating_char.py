from src.utils.judge_base import JudgeBase, TestCase, register


class P424LongestRepeatingChar(JudgeBase):
    name = "424. Longest Repeating Character Replacement"
    test_cases = [
        TestCase(input=("ABAB", 2), expected=4, label="example 1"),
        TestCase(input=("AABABBA", 1), expected=4, label="example 2"),
        TestCase(input=("AAAA", 0), expected=4, label="no changes needed"),
        TestCase(input=("ABCDE", 1), expected=2, label="all unique"),
        TestCase(input=("A", 0), expected=1, label="single char, k=0"),
        TestCase(input=("A", 5), expected=1, label="single char, k > len"),
        TestCase(input=("AAAB", 0), expected=3, label="no changes, partial run"),
        TestCase(input=("ABAA", 2), expected=4, label="change middle B to A"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_string(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P424LongestRepeatingChar)
