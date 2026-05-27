from src.utils.judge_base import JudgeBase, TestCase, register


class P713SubarrayProductLessThanK(JudgeBase):
    name = "713. Subarray Product Less Than K"
    test_cases = [
        TestCase(input=([10, 5, 2, 6], 100), expected=8, label="example 1"),
        TestCase(input=([1, 2, 3], 0), expected=0, label="zero k"),
        TestCase(input=([1, 1, 1], 2), expected=6, label="all ones"),
        TestCase(input=([1, 2, 3], 0), expected=0, label="k equals 0"),
        TestCase(input=([1, 2, 3], 1), expected=0, label="k equals 1"),
        TestCase(input=([1000, 1000, 1000], 1000000), expected=3, label="all large numbers"),
        TestCase(input=([10, 5, 2, 6], 8), expected=3, label="small k many singles"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P713SubarrayProductLessThanK)
