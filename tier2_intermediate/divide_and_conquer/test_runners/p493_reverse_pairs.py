from src.utils.judge_base import JudgeBase, TestCase, register


class P493ReversePairs(JudgeBase):
    name = "493. Reverse Pairs"
    test_cases = [
        TestCase(input=[1, 3, 2, 3, 1], expected=2, label="example 1"),
        TestCase(input=[2, 4, 3, 5, 1], expected=3, label="example 2"),
        TestCase(input=[1], expected=0, label="single element"),
        TestCase(input=[5, 4, 3, 2, 1], expected=4, label="all descending"),
        TestCase(input=[1, 2, 3, 4, 5], expected=0, label="sorted ascending"),
        TestCase(input=[2, 1, -1], expected=2, label="negative numbers"),
        TestCase(input=[1, 1, 1, 1], expected=0, label="all equal"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P493ReversePairs)
