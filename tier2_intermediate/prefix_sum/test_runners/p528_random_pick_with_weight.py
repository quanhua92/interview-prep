from src.utils.judge_base import JudgeBase, TestCase, register


class P528RandomPickWithWeight(JudgeBase):
    name = "528. Random Pick with Weight"
    test_cases = [
        TestCase(input=[1], expected=[0], label="single weight"),
        TestCase(input=[1, 3], expected=[0, 1], label="two weights"),
        TestCase(input=[3, 14, 1, 7], expected=[0, 1, 2, 3], label="four weights"),
        TestCase(input=[5], expected=[0], label="single large weight"),
        TestCase(input=[10, 10, 10], expected=[0, 1, 2], label="equal weights"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) in tc_expected


register(P528RandomPickWithWeight)
