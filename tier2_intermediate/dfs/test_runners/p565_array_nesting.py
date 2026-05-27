from src.utils.judge_base import JudgeBase, TestCase, register


class P565ArrayNesting(JudgeBase):
    name = "565. Array Nesting"
    test_cases = [
        TestCase(input=[5, 4, 0, 3, 1, 6, 2], expected=4, label="example 1"),
        TestCase(input=[0, 1, 2], expected=1, label="example 2"),
        TestCase(input=[0], expected=1, label="single element"),
        TestCase(input=[1, 0], expected=2, label="two element cycle"),
        TestCase(input=[2, 0, 1], expected=3, label="full single cycle"),
        TestCase(input=[0, 2, 1], expected=2, label="two separate cycles"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P565ArrayNesting)
