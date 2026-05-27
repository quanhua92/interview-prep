from src.utils.judge_base import JudgeBase, TestCase, register


class P528RandomPickWithWeight(JudgeBase):
    name = "528. Random Pick with Weight"
    test_cases = [
        TestCase(input=[1], expected=[1], label="prefix sum for [1]"),
        TestCase(input=[1, 3], expected=[1, 4], label="prefix sum for [1, 3]"),
        TestCase(input=[3, 14, 1, 7], expected=[3, 17, 18, 25], label="prefix sum for [3, 14, 1, 7]"),
        TestCase(input=[5], expected=[5], label="single large weight"),
        TestCase(input=[10, 10, 10], expected=[10, 20, 30], label="equal weights"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P528RandomPickWithWeight)
