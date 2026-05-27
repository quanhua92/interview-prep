from src.utils.judge_base import JudgeBase, TestCase, register


class P136SingleNumber(JudgeBase):
    name = "136. Single Number"
    test_cases = [
        TestCase(input=[2, 2, 1], expected=1, label="example 1"),
        TestCase(input=[4, 1, 2, 1, 2], expected=4, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
        TestCase(input=[-1, -1, -2], expected=-2, label="negative numbers"),
        TestCase(input=[0, 0, 1], expected=1, label="zero pairs"),
        TestCase(input=[-1], expected=-1, label="single negative"),
        TestCase(
            input=[7, 7, 7, 7, 99, 3, 3, 4, 4],
            expected=99,
            label="many pairs",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P136SingleNumber)
