from src.utils.judge_base import JudgeBase, TestCase, register


class P020ValidParentheses(JudgeBase):
    name = "20. Valid Parentheses"
    test_cases = [
        TestCase(input="()", expected=True, label="simple pair"),
        TestCase(input="()[]{}", expected=True, label="mixed brackets"),
        TestCase(input="(]", expected=False, label="mismatched"),
        TestCase(input="([)]", expected=False, label="interleaved"),
        TestCase(input="{[]}", expected=True, label="nested"),
        TestCase(input="(", expected=False, label="single opening"),
        TestCase(input=")", expected=False, label="single closing"),
        TestCase(input="((((", expected=False, label="only openings"),
        TestCase(input="))))", expected=False, label="only closings"),
        TestCase(input="((({{{[[[]]]}}})))", expected=True, label="deeply nested"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P020ValidParentheses)
