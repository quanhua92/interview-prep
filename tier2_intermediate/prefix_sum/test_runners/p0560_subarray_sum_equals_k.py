from src.utils.judge_base import JudgeBase, TestCase, register


class P560SubarraySumEqualsK(JudgeBase):
    name = "560. Subarray Sum Equals K"
    test_cases = [
        TestCase(input=([1, 1, 1], 2), expected=2, label="example 1"),
        TestCase(input=([1, 2, 3], 3), expected=2, label="example 2"),
        TestCase(input=([], 0), expected=0, label="empty array"),
        TestCase(input=([1], 1), expected=1, label="single element equals k"),
        TestCase(input=([1], 2), expected=0, label="single element not k"),
        TestCase(input=([1, -1, 0], 0), expected=3, label="negatives with zero sum"),
        TestCase(input=([0, 0, 0], 0), expected=6, label="all zeros"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P560SubarraySumEqualsK)
