from src.utils.judge_base import JudgeBase, TestCase, register


class P054SpiralMatrix(JudgeBase):
    name = "54. Spiral Matrix"
    test_cases = [
        TestCase(
            input=[[1, 2, 3], [4, 5, 6], [7, 8, 9]],
            expected=[1, 2, 3, 6, 9, 8, 7, 4, 5],
            label="example 1",
        ),
        TestCase(
            input=[[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]],
            expected=[1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7],
            label="example 2",
        ),
        TestCase(input=[[7]], expected=[7], label="single element"),
        TestCase(
            input=[[1, 2, 3, 4]],
            expected=[1, 2, 3, 4],
            label="single row",
        ),
        TestCase(
            input=[[1], [2], [3], [4]],
            expected=[1, 2, 3, 4],
            label="single column",
        ),
        TestCase(
            input=[[1, 2], [3, 4]],
            expected=[1, 2, 4, 3],
            label="2x2 matrix",
        ),
        TestCase(
            input=[[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]],
            expected=[1, 2, 3, 4, 5, 10, 9, 8, 7, 6],
            label="2 rows many columns",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P054SpiralMatrix)
