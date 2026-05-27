from src.utils.judge_base import JudgeBase, TestCase, register


class P483SmallestGoodBase(JudgeBase):
    name = "483. Smallest Good Base"
    test_cases = [
        TestCase(input="13", expected="3", label="example 1"),
        TestCase(input="4681", expected="8", label="example 2"),
        TestCase(input="1000000000000000000", expected="999999999999999999", label="example 3"),
        TestCase(input="3", expected="2", label="smallest n equals 11 base 2"),
        TestCase(input="7", expected="2", label="111 base 2"),
        TestCase(input="31", expected="2", label="11111 base 2"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_string(stdout) == tc_expected


register(P483SmallestGoodBase)
