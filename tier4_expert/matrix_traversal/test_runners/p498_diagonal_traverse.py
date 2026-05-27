from src.utils.judge_base import JudgeBase, TestCase, register


class P498DiagonalTraverse(JudgeBase):
    name = "498. Diagonal Traverse"
    test_cases = [
        TestCase(
            input=[[1, 2, 3], [4, 5, 6], [7, 8, 9]],
            expected=[1, 2, 4, 7, 5, 3, 6, 8, 9],
            label="example 1",
        ),
        TestCase(
            input=[[1, 2], [3, 4], [5, 6]],
            expected=[1, 2, 3, 5, 4, 6],
            label="example 2",
        ),
        TestCase(input=[[1]], expected=[1], label="single element"),
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
            input=[[1, 2, 3, 4], [5, 6, 7, 8]],
            expected=[1, 2, 5, 6, 3, 4, 7, 8],
            label="2x4 rectangular",
        ),
        TestCase(
            input=[[-1, -2], [3, 4]],
            expected=[-1, -2, 3, 4],
            label="negative values 2x2",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P498DiagonalTraverse)
