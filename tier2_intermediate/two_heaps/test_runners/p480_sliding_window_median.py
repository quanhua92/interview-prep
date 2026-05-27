from src.utils.judge_base import JudgeBase, TestCase, register


class P480SlidingWindowMedian(JudgeBase):
    name = "480. Sliding Window Median"
    test_cases = [
        TestCase(
            input=([1, 3, -1, -3, 5, 3, 6, 7], 3),
            expected=[1.0, -1.0, -1.0, 3.0, 5.0, 6.0],
            label="example 1",
        ),
        TestCase(input=([1, 2], 1), expected=[1.0, 2.0], label="window size 1"),
        TestCase(
            input=([1, 2, 3, 4, 2, 3, 1, 4, 2], 3),
            expected=[2.0, 3.0, 3.0, 3.0, 2.0, 3.0, 2.0],
            label="example 2",
        ),
        TestCase(
            input=([2147483647, -2147483648], 2),
            expected=[-0.5],
            label="large int boundary",
        ),
        TestCase(
            input=([1, 1, 1, 1], 2),
            expected=[1.0, 1.0, 1.0],
            label="all same values",
        ),
        TestCase(
            input=([5, 5, 5, 5, 5], 5),
            expected=[5.0],
            label="window equals array",
        ),
        TestCase(
            input=([-5, -4, -3, -2, -1], 3),
            expected=[-4.0, -3.0, -2.0],
            label="all negative ascending",
        ),
        TestCase(
            input=([10, 9, 8, 7, 6], 3),
            expected=[9.0, 8.0, 7.0],
            label="descending order",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        nums, k = tc_input
        return self.serialize_multi(
            self.serialize_int_array(nums),
            self.serialize_int(k),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if len(lines) != len(tc_expected):
            return False
        for got_s, exp in zip(lines, tc_expected):
            if abs(float(got_s) - exp) > 1e-5:
                return False
        return True


register(P480SlidingWindowMedian)
