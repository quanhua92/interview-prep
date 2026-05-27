from src.utils.judge_base import JudgeBase, TestCase, register


class P268MissingNumber(JudgeBase):
    name = "268. Missing Number"
    test_cases = [
        TestCase(input=[3, 0, 1], expected=2, label="example 1"),
        TestCase(input=[0, 1], expected=2, label="example 2"),
        TestCase(input=[9, 6, 4, 2, 3, 5, 7, 0, 1], expected=8, label="example 3"),
        TestCase(input=[1], expected=0, label="missing 0, n=1"),
        TestCase(input=[0], expected=1, label="missing n, n=1"),
        TestCase(input=[0, 1, 2, 3], expected=4, label="missing last, sorted"),
        TestCase(input=[1, 2, 3, 4, 5], expected=0, label="missing 0, n=5"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P268MissingNumber)
