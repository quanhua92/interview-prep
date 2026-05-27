from src.utils.judge_base import JudgeBase, TestCase, register


class P525ContiguousArray(JudgeBase):
    name = "525. Contiguous Array"
    test_cases = [
        TestCase(input=[0, 1], expected=2, label="example 1"),
        TestCase(input=[0, 1, 0], expected=2, label="example 2"),
        TestCase(input=[0, 1, 1, 1, 1, 1, 0, 0, 0], expected=6, label="example 3"),
        TestCase(input=[1], expected=0, label="single element"),
        TestCase(input=[0, 0, 0, 0, 1, 1, 1, 1], expected=8, label="balanced halves"),
        TestCase(input=[0, 0, 1, 0, 0, 0, 1, 1], expected=6, label="middle balanced"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P525ContiguousArray)
