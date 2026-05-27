from src.utils.judge_base import JudgeBase, TestCase, register


class P448FindDisappeared(JudgeBase):
    name = "448. Find All Numbers Disappeared in an Array"
    test_cases = [
        TestCase(input=[4, 3, 2, 7, 8, 2, 3, 1], expected=[5, 6], label="example 1"),
        TestCase(input=[1, 1], expected=[2], label="example 2"),
        TestCase(input=[2, 2], expected=[1], label="example 3"),
        TestCase(input=[1], expected=[], label="single element, none missing"),
        TestCase(input=[1, 1, 1, 1], expected=[2, 3, 4], label="all same value"),
        TestCase(
            input=[1, 2, 3, 4, 5], expected=[], label="identity permutation, none missing"
        ),
        TestCase(
            input=[5, 4, 6, 7, 9, 10, 9, 6, 5, 4],
            expected=[1, 2, 3, 8],
            label="large, many disappeared",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P448FindDisappeared)
