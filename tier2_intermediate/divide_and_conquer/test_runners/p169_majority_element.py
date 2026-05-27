from src.utils.judge_base import JudgeBase, TestCase, register


class P169MajorityElement(JudgeBase):
    name = "169. Majority Element"
    test_cases = [
        TestCase(input=[3, 2, 3], expected=3, label="example 1"),
        TestCase(input=[2, 2, 1, 1, 1, 2, 2], expected=2, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
        TestCase(input=[1, 2, 3, 2, 2], expected=2, label="majority at end"),
        TestCase(input=[5, 5, 5, 5, 5], expected=5, label="all same"),
        TestCase(input=[-1, -1, 2], expected=-1, label="negative majority"),
        TestCase(input=[3, 3], expected=3, label="two elements"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P169MajorityElement)
