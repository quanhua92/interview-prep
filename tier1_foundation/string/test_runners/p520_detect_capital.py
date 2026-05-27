from src.utils.judge_base import JudgeBase, TestCase, register


class P520DetectCapital(JudgeBase):
    name = "520. Detect Capital"
    test_cases = [
        TestCase(input="USA", expected=True, label="example 1"),
        TestCase(input="FlaG", expected=False, label="example 2"),
        TestCase(input="a", expected=True, label="single lowercase"),
        TestCase(input="Z", expected=True, label="single uppercase"),
        TestCase(input="leetcode", expected=True, label="all lowercase"),
        TestCase(input="Google", expected=True, label="title case"),
        TestCase(input="mL", expected=False, label="lowercase then uppercase"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P520DetectCapital)
