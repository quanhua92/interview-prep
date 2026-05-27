from src.utils.judge_base import JudgeBase, TestCase, register


class P473MatchsticksToSquare(JudgeBase):
    name = "473. Matchsticks to Square"
    test_cases = [
        TestCase(input=[1, 1, 2, 2, 2], expected=True, label="example 1"),
        TestCase(input=[3, 3, 3, 3, 4], expected=False, label="example 2"),
        TestCase(input=[5, 5, 5, 5], expected=True, label="four equal sticks"),
        TestCase(input=[2, 2, 2, 2, 2, 2], expected=False, label="all twos cannot form square"),
        TestCase(input=[1, 1, 1, 1], expected=True, label="minimal square"),
        TestCase(input=[3, 3, 3, 3], expected=True, label="each stick one side"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P473MatchsticksToSquare)
