from src.utils.judge_base import JudgeBase, TestCase, register


class P556NextGreaterElementIII(JudgeBase):
    name = "556. Next Greater Element III"
    test_cases = [
        TestCase(input=12, expected=21, label="example 1"),
        TestCase(input=21, expected=-1, label="example 2"),
        TestCase(input=1, expected=-1, label="single digit"),
        TestCase(input=11, expected=-1, label="all same digits"),
        TestCase(input=230241, expected=230412, label="classic example"),
        TestCase(input=2147483647, expected=-1, label="max 32-bit int"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P556NextGreaterElementIII)
