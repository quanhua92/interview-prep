from src.utils.judge_base import JudgeBase, TestCase, register


class P452MinArrowShots(JudgeBase):
    name = "452. Minimum Number of Arrows to Burst Balloons"
    test_cases = [
        TestCase(
            input=[[10, 16], [2, 8], [1, 6], [7, 12]], expected=2, label="example 1"
        ),
        TestCase(input=[[1, 2], [3, 4], [5, 6], [7, 8]], expected=4, label="example 2"),
        TestCase(input=[[1, 2], [2, 3], [3, 4], [4, 5]], expected=2, label="example 3"),
        TestCase(input=[[1, 2]], expected=1, label="single balloon"),
        TestCase(
            input=[[1, 10], [2, 9], [3, 8]], expected=1, label="all overlapping"
        ),
        TestCase(
            input=[[1, 5], [2, 3]], expected=1, label="nested intervals"
        ),
        TestCase(
            input=[[-2147483646, -2147483645], [2147483646, 2147483647]],
            expected=2,
            label="far apart balloons",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P452MinArrowShots)
