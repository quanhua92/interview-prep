from src.utils.judge_base import JudgeBase, TestCase, register


class P523ContinuousSubarraySum(JudgeBase):
    name = "523. Continuous Subarray Sum"
    test_cases = [
        TestCase(input=([23, 2, 4, 6, 7], 6), expected=True, label="example 1"),
        TestCase(input=([23, 2, 6, 4, 7], 6), expected=True, label="example 2"),
        TestCase(input=([23, 2, 6, 4, 7], 13), expected=False, label="example 3"),
        TestCase(input=([5, 0, 0], 3), expected=True, label="two zeros sum to 0"),
        TestCase(input=([1, 2], 4), expected=False, label="no valid subarray"),
        TestCase(input=([0, 0], 1), expected=True, label="two zeros always valid"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P523ContinuousSubarraySum)
