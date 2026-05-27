from src.utils.judge_base import JudgeBase, TestCase, register


class P0238ProductExceptSelf(JudgeBase):
    name = "238. Product of Array Except Self"
    test_cases = [
        TestCase(input=[1, 2, 3, 4], expected=[24, 12, 8, 6], label="example 1"),
        TestCase(input=[-1, 1, 0, -3, 3], expected=[0, 0, 9, 0, 0], label="example 2"),
        TestCase(input=[1, 2], expected=[2, 1], label="two elements"),
        TestCase(input=[1, 1, 1], expected=[1, 1, 1], label="all ones"),
        TestCase(input=[-1, -1, -1], expected=[1, 1, 1], label="all negatives"),
        TestCase(input=[1, -1], expected=[-1, 1], label="two elements negative"),
        TestCase(input=[0, 0, 0, 0], expected=[0, 0, 0, 0], label="all zeros"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P0238ProductExceptSelf)
