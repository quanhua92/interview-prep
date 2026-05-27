from src.utils.judge_base import JudgeBase, TestCase, register


class P907SumOfSubarrayMinimums(JudgeBase):
    name = "907. Sum of Subarray Minimums"
    test_cases = [
        TestCase(input=[3, 1, 2, 4], expected=17, label="example 1"),
        TestCase(input=[11, 81, 94, 43, 3], expected=444, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
        TestCase(input=[2, 1], expected=4, label="two elements"),
        TestCase(input=[3, 3, 3], expected=18, label="all same"),
        TestCase(input=[1, 2, 3], expected=10, label="strictly increasing"),
        TestCase(input=[3, 2, 1], expected=10, label="strictly decreasing"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P907SumOfSubarrayMinimums)
