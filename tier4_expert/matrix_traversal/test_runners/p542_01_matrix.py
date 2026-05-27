from src.utils.judge_base import JudgeBase, TestCase, register


class P54201Matrix(JudgeBase):
    name = "542. 01 Matrix"
    test_cases = [
        TestCase(
            input=[[0, 0, 0], [0, 1, 0], [0, 0, 0]],
            expected=[[0, 0, 0], [0, 1, 0], [0, 0, 0]],
            label="example 1",
        ),
        TestCase(
            input=[[0, 0, 0], [0, 1, 0], [1, 1, 1]],
            expected=[[0, 0, 0], [0, 1, 0], [1, 2, 1]],
            label="example 2",
        ),
        TestCase(input=[[0]], expected=[[0]], label="single zero"),
        TestCase(
            input=[[1], [0], [1]],
            expected=[[1], [0], [1]],
            label="single column",
        ),
        TestCase(
            input=[[0, 1, 1, 1]],
            expected=[[0, 1, 2, 3]],
            label="single row",
        ),
        TestCase(
            input=[[1, 1, 1], [1, 0, 1], [1, 1, 1]],
            expected=[[2, 1, 2], [1, 0, 1], [2, 1, 2]],
            label="cross of ones around center zero",
        ),
        TestCase(
            input=[[1, 1, 0], [1, 1, 1], [0, 1, 1]],
            expected=[[2, 1, 0], [1, 2, 1], [0, 1, 2]],
            label="corner zeros",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_matrix(stdout) == tc_expected


register(P54201Matrix)
