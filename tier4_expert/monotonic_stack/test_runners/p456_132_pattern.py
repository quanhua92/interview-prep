from src.utils.judge_base import JudgeBase, TestCase, register


class P456132Pattern(JudgeBase):
    name = "456. 132 Pattern"
    test_cases = [
        TestCase(input=[1, 2, 3, 4], expected=False, label="example 1"),
        TestCase(input=[3, 1, 4, 2], expected=True, label="example 2"),
        TestCase(input=[-1, 3, 2, 0], expected=True, label="example 3"),
        TestCase(input=[1, 2], expected=False, label="two elements"),
        TestCase(input=[2, 2, 2], expected=False, label="all same"),
        TestCase(input=[5, 4, 3, 2, 1], expected=False, label="strictly decreasing"),
        TestCase(input=[1, 3, 0, 2], expected=True, label="pattern near end"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P456132Pattern)
