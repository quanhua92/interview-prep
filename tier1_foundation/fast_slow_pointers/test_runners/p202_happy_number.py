from src.utils.judge_base import JudgeBase, TestCase, register


class P202HappyNumber(JudgeBase):
    name = "202. Happy Number"
    test_cases = [
        TestCase(input=19, expected=True, label="example 1"),
        TestCase(input=2, expected=False, label="example 2"),
        TestCase(input=1, expected=True, label="already happy"),
        TestCase(input=7, expected=True, label="small happy number"),
        TestCase(input=4, expected=False, label="enters 4-16 cycle"),
        TestCase(input=100, expected=True, label="power of 10"),
        TestCase(input=999999999, expected=False, label="large unhappy number"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P202HappyNumber)
