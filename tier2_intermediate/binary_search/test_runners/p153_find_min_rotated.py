from src.utils.judge_base import JudgeBase, TestCase, register


class P153FindMinRotated(JudgeBase):
    name = "153. Find Minimum in Rotated Sorted Array"
    test_cases = [
        TestCase(input=[3, 4, 5, 1, 2], expected=1, label="example 1"),
        TestCase(input=[4, 5, 6, 7, 0, 1, 2], expected=0, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
        TestCase(input=[11, 13, 15, 17], expected=11, label="not rotated"),
        TestCase(input=[2, 1], expected=1, label="two elements rotated"),
        TestCase(input=[1, 2], expected=1, label="two elements not rotated"),
        TestCase(input=[-3, -2, -1, -5, -4], expected=-5, label="negative numbers"),
        TestCase(input=[2, 3, 4, 5, 1], expected=1, label="rotated by 1"),
        TestCase(input=[5, 1, 2, 3, 4], expected=1, label="rotated by n-1"),
        TestCase(input=[3, 1, 2], expected=1, label="three elements rotated"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P153FindMinRotated)
