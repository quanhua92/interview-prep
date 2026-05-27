from src.utils.judge_base import JudgeBase, TestCase, register


class P410SplitArraySum(JudgeBase):
    name = "410. Split Array Largest Sum"
    test_cases = [
        TestCase(input=([7, 2, 5, 10, 8], 2), expected=18, label="example 1"),
        TestCase(input=([1, 2, 3, 4, 5], 2), expected=9, label="example 2"),
        TestCase(input=([1, 4, 4], 3), expected=4, label="example 3"),
        TestCase(input=([1, 2, 3, 4, 5], 5), expected=5, label="k equals length"),
        TestCase(input=([5], 1), expected=5, label="single element"),
        TestCase(input=([0, 0, 0, 0], 2), expected=0, label="all zeros"),
        TestCase(input=([1, 1, 1, 1, 1, 1, 1, 1], 4), expected=2, label="uniform values"),
        TestCase(input=([1000000, 1000000, 1000000], 2), expected=2000000, label="large values"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P410SplitArraySum)
