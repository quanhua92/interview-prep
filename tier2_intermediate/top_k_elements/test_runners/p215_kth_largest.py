from src.utils.judge_base import JudgeBase, TestCase, register


class P215KthLargest(JudgeBase):
    name = "215. Kth Largest Element in an Array"
    test_cases = [
        TestCase(input=([3, 2, 1, 5, 6, 4], 2), expected=5, label="example 1"),
        TestCase(input=([3, 2, 3, 1, 2, 4, 5, 5, 6], 4), expected=4, label="example 2"),
        TestCase(input=([1], 1), expected=1, label="single element"),
        TestCase(input=([-1, -2, -3], 1), expected=-1, label="negative numbers"),
        TestCase(input=([5, 5, 5, 5], 2), expected=5, label="all duplicates"),
        TestCase(input=([1, 2, 3], 3), expected=1, label="k equals length"),
        TestCase(input=([-100, 0, 100], 2), expected=0, label="mixed negatives and zero"),
        TestCase(input=(list(range(1, 101)), 50), expected=51, label="100 elements k=50"),
        TestCase(input=([-1, -1, -1, -1], 3), expected=-1, label="all negative duplicates"),
    ]

    def to_stdin(self, tc_input) -> str:
        nums, k = tc_input
        return self.serialize_multi(self.serialize_int_array(nums), self.serialize_int(k))

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P215KthLargest)
