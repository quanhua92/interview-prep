from src.utils.judge_base import JudgeBase, TestCase, register


class P532KDiffPairs(JudgeBase):
    name = "532. K-diff Pairs in an Array"
    test_cases = [
        TestCase(input=([3, 1, 4, 1, 5], 2), expected=2, label="example 1"),
        TestCase(input=([1, 2, 3, 4, 5], 1), expected=4, label="example 2"),
        TestCase(input=([1, 3, 1, 5, 4], 0), expected=1, label="example 3"),
        TestCase(input=([1], 1), expected=0, label="single element"),
        TestCase(input=([1, 1, 1, 1], 0), expected=1, label="all same k=0"),
        TestCase(input=([1, 2, 3, 4, 5], 100), expected=0, label="k larger than range"),
        TestCase(input=([-1, -2, -3, -4, -5], 1), expected=4, label="all negatives"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P532KDiffPairs)
