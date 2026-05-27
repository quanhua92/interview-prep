from src.utils.judge_base import JudgeBase, TestCase, register


class P055JumpGame(JudgeBase):
    name = "55. Jump Game"
    test_cases = [
        TestCase(input=[2, 3, 1, 1, 4], expected=True, label="example 1"),
        TestCase(input=[3, 2, 1, 0, 4], expected=False, label="example 2"),
        TestCase(input=[0], expected=True, label="single element"),
        TestCase(input=[1, 1, 1, 1, 1], expected=True, label="all ones"),
        TestCase(input=[5, 0, 0, 0, 0], expected=True, label="big jump from start"),
        TestCase(input=[0, 1], expected=False, label="stuck at start"),
        TestCase(input=[2, 0], expected=True, label="two elements reachable"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P055JumpGame)
