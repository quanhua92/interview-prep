from src.utils.judge_base import JudgeBase, TestCase, register


class P033SearchRotated(JudgeBase):
    name = "33. Search in Rotated Sorted Array"
    test_cases = [
        TestCase(input=([4, 5, 6, 7, 0, 1, 2], 0), expected=4, label="example 1"),
        TestCase(input=([4, 5, 6, 7, 0, 1, 2], 3), expected=-1, label="example 2"),
        TestCase(input=([1], 0), expected=-1, label="single element"),
        TestCase(input=([1], 1), expected=0, label="single element found"),
        TestCase(input=([1, 3], 3), expected=1, label="two elements rotated at pivot"),
        TestCase(input=([1, 3], 1), expected=0, label="two elements no rotation"),
        TestCase(input=([5, 1, 3], 5), expected=0, label="target at first index"),
        TestCase(input=([5, 1, 3], 3), expected=2, label="target at last index"),
        TestCase(input=([6, 7, 0, 1, 2, 3, 4, 5], 6), expected=0, label="large rotated target at start"),
        TestCase(input=([6, 7, 0, 1, 2, 3, 4, 5], 5), expected=7, label="large rotated target at end"),
        TestCase(input=([1, 2, 3, 4, 5], 3), expected=2, label="no rotation sorted"),
        TestCase(input=([-10, -5, 0, 1, 2, 3, -9], -10), expected=0, label="negative values target at start"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P033SearchRotated)
