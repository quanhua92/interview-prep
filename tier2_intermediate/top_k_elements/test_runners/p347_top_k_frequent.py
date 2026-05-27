from src.utils.judge_base import JudgeBase, TestCase, register


class P347TopKFrequent(JudgeBase):
    name = "347. Top K Frequent Elements"
    test_cases = [
        TestCase(input=([1, 1, 1, 2, 2, 3], 2), expected=[1, 2], label="example 1"),
        TestCase(input=([1], 1), expected=[1], label="example 2"),
        TestCase(input=([7, 7, 7, 7, 1, 2, 2, 2], 2), expected=[7, 2], label="distinct frequencies"),
        TestCase(input=([1, 2, 3, 4, 5, 6], 3), expected=[6, 5, 4], label="all freq 1"),
        TestCase(input=([1, 1, 1, 1], 1), expected=[1], label="all same element"),
        TestCase(
            input=([1, 1, 2, 2, 2, 3, 3, 3, 3], 2),
            expected=[3, 2],
            label="clear frequency ranking",
        ),
        TestCase(input=([-1, -1, -1, 2, 2], 1), expected=[-1], label="negative numbers"),
        TestCase(input=([0, 0, 0, 0, 1, 1, 2], 2), expected=[0, 1], label="zero values"),
    ]

    def to_stdin(self, tc_input) -> str:
        nums, k = tc_input
        return self.serialize_multi(self.serialize_int_array(nums), self.serialize_int(k))

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        got = sorted(self.parse_int_array(stdout))
        exp = sorted(tc_expected)
        return got == exp


register(P347TopKFrequent)
