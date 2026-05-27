from src.utils.judge_base import JudgeBase, TestCase, register


class P084LargestRectangle(JudgeBase):
    name = "84. Largest Rectangle in Histogram"
    test_cases = [
        TestCase(input=[2, 1, 5, 6, 2, 3], expected=10, label="example 1"),
        TestCase(input=[2, 4], expected=4, label="example 2"),
        TestCase(input=[5], expected=5, label="single element"),
        TestCase(input=[3, 3, 3], expected=9, label="all same heights"),
        TestCase(input=[2, 0, 2], expected=2, label="contains zero height"),
        TestCase(input=[1, 2, 3, 4, 5], expected=9, label="strictly increasing"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P084LargestRectangle)
