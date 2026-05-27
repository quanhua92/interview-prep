from src.utils.judge_base import JudgeBase, TestCase, register


class P1091ShortestPathBinary(JudgeBase):
    name = "1091. Shortest Path in Binary Matrix"
    test_cases = [
        TestCase(input=[[0, 1], [1, 0]], expected=2, label="example 1"),
        TestCase(input=[[0, 0, 0], [1, 1, 0], [1, 1, 0]], expected=4, label="example 2"),
        TestCase(input=[[1, 0], [0, 1]], expected=-1, label="blocked"),
        TestCase(input=[[0]], expected=1, label="single cell"),
        TestCase(input=[[0, 0, 0], [0, 0, 0], [0, 0, 0]], expected=3, label="3x3 all open (diagonal)"),
        TestCase(input=[[0, 0], [0, 0]], expected=2, label="2x2 all open (diagonal)"),
        TestCase(input=[[0, 1, 1], [1, 1, 1], [1, 1, 0]], expected=-1, label="3x3 only corners open"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P1091ShortestPathBinary)
