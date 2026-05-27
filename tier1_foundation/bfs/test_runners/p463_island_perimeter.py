from src.utils.judge_base import JudgeBase, TestCase, register


class P463IslandPerimeter(JudgeBase):
    name = "463. Island Perimeter"
    test_cases = [
        TestCase(input=[[0, 1, 0, 0], [1, 1, 1, 0], [0, 1, 0, 0], [1, 1, 0, 0]], expected=16, label="example 1"),
        TestCase(input=[[1]], expected=4, label="example 2"),
        TestCase(input=[[1, 0]], expected=4, label="example 3"),
        TestCase(input=[[1, 1, 1]], expected=8, label="horizontal line of 3"),
        TestCase(input=[[1], [1], [1]], expected=8, label="vertical line of 3"),
        TestCase(input=[[1, 1], [1, 1]], expected=8, label="2x2 block"),
        TestCase(input=[[1, 1, 1], [1, 1, 1]], expected=10, label="3x2 block"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P463IslandPerimeter)
