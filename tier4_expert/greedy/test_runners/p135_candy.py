from src.utils.judge_base import JudgeBase, TestCase, register


class P135Candy(JudgeBase):
    name = "135. Candy"
    test_cases = [
        TestCase(input=[1, 0, 2], expected=5, label="example 1"),
        TestCase(input=[1, 2, 2], expected=4, label="example 2"),
        TestCase(input=[1, 3, 2, 2, 1], expected=7, label="decreasing then flat"),
        TestCase(input=[1], expected=1, label="single child"),
        TestCase(input=[2, 2, 2, 2], expected=4, label="all same ratings"),
        TestCase(input=[1, 2, 3, 4], expected=10, label="strictly increasing"),
        TestCase(input=[4, 3, 2, 1], expected=10, label="strictly decreasing"),
        TestCase(input=[1, 3, 4, 5, 2], expected=11, label="increase then drop"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P135Candy)
