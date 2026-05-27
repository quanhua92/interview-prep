from src.utils.judge_base import JudgeBase, TestCase, register


class P048RotateImage(JudgeBase):
    name = "48. Rotate Image"
    test_cases = [
        TestCase(
            input=[[1, 2, 3], [4, 5, 6], [7, 8, 9]],
            expected=[[7, 4, 1], [8, 5, 2], [9, 6, 3]],
            label="example 1",
        ),
        TestCase(
            input=[[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]],
            expected=[[15, 13, 2, 5], [14, 3, 4, 1], [12, 6, 8, 9], [16, 7, 10, 11]],
            label="example 2",
        ),
        TestCase(input=[[1]], expected=[[1]], label="single element"),
        TestCase(
            input=[[1, 2], [3, 4]],
            expected=[[3, 1], [4, 2]],
            label="2x2 matrix",
        ),
        TestCase(
            input=[[-1, -2, -3], [-4, -5, -6], [-7, -8, -9]],
            expected=[[-7, -4, -1], [-8, -5, -2], [-9, -6, -3]],
            label="negative values",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_matrix(stdout) == tc_expected


register(P048RotateImage)
