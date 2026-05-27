from src.utils.judge_base import JudgeBase, TestCase, register


class P295MedianFinder(JudgeBase):
    name = "295. Find Median from Data Stream"
    test_cases = [
        TestCase(
            input=[5, 15, 1, 3],
            expected=[5.0, 10.0, 5.0, 4.0],
            label="stream median",
        ),
        TestCase(input=[1, 2], expected=[1.0, 1.5], label="two elements"),
        TestCase(input=[42], expected=[42.0], label="single element"),
        TestCase(
            input=[3, 3, 3, 3], expected=[3.0, 3.0, 3.0, 3.0], label="all same"
        ),
        TestCase(
            input=[-5, -3, -1, 0],
            expected=[-5.0, -4.0, -3.0, -2.0],
            label="negative numbers",
        ),
        TestCase(
            input=[100, 0, 100, 0, 100, 0],
            expected=[100.0, 50.0, 100.0, 50.0, 100.0, 50.0],
            label="alternating high low",
        ),
        TestCase(
            input=[10, 9, 8, 7, 6, 5],
            expected=[10.0, 9.5, 9.0, 8.5, 8.0, 7.5],
            label="descending order",
        ),
        TestCase(
            input=[-100000, 100000],
            expected=[-100000.0, 0.0],
            label="extreme values",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if len(lines) != len(tc_expected):
            return False
        for got_s, exp in zip(lines, tc_expected):
            if abs(float(got_s) - exp) > 1e-6:
                return False
        return True


register(P295MedianFinder)
