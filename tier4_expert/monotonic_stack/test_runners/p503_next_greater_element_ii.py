from src.utils.judge_base import JudgeBase, TestCase, register


class P503NextGreaterElementII(JudgeBase):
    name = "503. Next Greater Element II"
    test_cases = [
        TestCase(input=[1, 2, 1], expected=[2, -1, 2], label="example 1"),
        TestCase(input=[1, 2, 3, 4, 3], expected=[2, 3, 4, -1, 4], label="example 2"),
        TestCase(input=[5], expected=[-1], label="single element"),
        TestCase(input=[2, 2, 2], expected=[-1, -1, -1], label="all same"),
        TestCase(input=[5, 4, 3, 2], expected=[-1, 5, 5, 5], label="strictly decreasing wraps"),
        TestCase(input=[-3, -2, -1], expected=[-2, -1, -1], label="with negatives"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P503NextGreaterElementII)
