from src.utils.judge_base import JudgeBase, TestCase, register


class P553OptimalDivision(JudgeBase):
    name = "553. Optimal Division"
    test_cases = [
        TestCase(input=[1000, 100, 10, 2], expected="1000/(100/10/2)", label="example 1"),
        TestCase(input=[2, 3, 4], expected="2/(3/4)", label="example 2"),
        TestCase(input=[2, 3], expected="2/3", label="two elements no parens"),
        TestCase(input=[2], expected="2", label="single element"),
        TestCase(input=[10, 2, 5], expected="10/(2/5)", label="three elements"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_string(stdout) == tc_expected


register(P553OptimalDivision)
