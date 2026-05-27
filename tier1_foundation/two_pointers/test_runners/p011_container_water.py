from src.utils.judge_base import JudgeBase, TestCase, register


class P011ContainerWater(JudgeBase):
    name = "11. Container With Most Water"
    test_cases = [
        TestCase(input=[1, 8, 6, 2, 5, 4, 8, 3, 7], expected=49, label="example 1"),
        TestCase(input=[1, 1], expected=1, label="example 2"),
        TestCase(input=[4, 3, 2, 1, 4], expected=16, label="symmetric"),
        TestCase(input=[0, 0, 0, 0], expected=0, label="all zeros"),
        TestCase(input=[1, 2, 3, 4, 5], expected=6, label="strictly increasing"),
        TestCase(input=[5, 4, 3, 2, 1], expected=6, label="strictly decreasing"),
        TestCase(input=[10000, 10000], expected=10000, label="max height two elements"),
        TestCase(input=[2, 2, 2, 2, 2], expected=8, label="all same height"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P011ContainerWater)
