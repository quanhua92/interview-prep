from src.utils.judge_base import JudgeBase, TestCase, register


class P739DailyTemperatures(JudgeBase):
    name = "739. Daily Temperatures"
    test_cases = [
        TestCase(
            input=[73, 74, 75, 71, 69, 72, 76, 73],
            expected=[1, 1, 4, 2, 1, 1, 0, 0],
            label="example 1",
        ),
        TestCase(input=[30, 40, 50, 60], expected=[1, 1, 1, 0], label="example 2"),
        TestCase(input=[30, 60, 90], expected=[1, 1, 0], label="example 3"),
        TestCase(input=[50], expected=[0], label="single element"),
        TestCase(input=[50, 50, 50], expected=[0, 0, 0], label="all same temps"),
        TestCase(input=[90, 80, 70, 60], expected=[0, 0, 0, 0], label="strictly decreasing"),
        TestCase(input=[50, 50, 50, 60], expected=[3, 2, 1, 0], label="all same then warmer"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P739DailyTemperatures)
