from src.utils.judge_base import JudgeBase, TestCase, register


class P395LongestSubstringKRepeating(JudgeBase):
    name = "395. Longest Substring with At Least K Repeating Characters"
    test_cases = [
        TestCase(input=("aaabb", 3), expected=3, label="example 1"),
        TestCase(input=("ababbc", 2), expected=5, label="example 2"),
        TestCase(input=("ababacb", 3), expected=0, label="no valid substring"),
        TestCase(input=("a", 1), expected=1, label="single char k=1"),
        TestCase(input=("a", 2), expected=0, label="single char k>1"),
        TestCase(input=("bbaaacbd", 3), expected=3, label="multiple runs"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_string(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P395LongestSubstringKRepeating)
