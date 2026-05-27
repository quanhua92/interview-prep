from src.utils.judge_base import JudgeBase, TestCase, register


class P470ImplementRand10UsingRand7(JudgeBase):
    name = "470. Implement Rand10() Using Rand7()"
    test_cases = [
        TestCase(input=5, expected=True, label="generates 5 values in range [1, 10]"),
        TestCase(input=1, expected=True, label="single value"),
        TestCase(input=100, expected=True, label="100 values"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P470ImplementRand10UsingRand7)
