from src.utils.judge_base import JudgeBase, TestCase, register


class P575DistributeCandies(JudgeBase):
    name = "575. Distribute Candies"
    test_cases = [
        TestCase(input=[1, 1, 2, 2, 3, 3], expected=3, label="example 1"),
        TestCase(input=[1, 1, 2, 3], expected=2, label="example 2"),
        TestCase(input=[6, 6, 6, 6], expected=1, label="example 3"),
        TestCase(input=[1, 2, 3, 4], expected=2, label="all unique types"),
        TestCase(input=[-1, -1, 2, 2], expected=2, label="negative candy types"),
        TestCase(input=[100000, -100000, 0, 50000], expected=2, label="boundary values"),
        TestCase(input=[1, 2, 1, 2, 1, 2, 3, 4], expected=4, label="eight candies mixed"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P575DistributeCandies)
