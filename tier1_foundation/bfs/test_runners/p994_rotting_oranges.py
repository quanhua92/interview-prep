from src.utils.judge_base import JudgeBase, TestCase, register


class P994RottingOranges(JudgeBase):
    name = "994. Rotting Oranges"
    test_cases = [
        TestCase(input=[[2, 1, 1], [1, 1, 0], [0, 1, 1]], expected=4, label="example 1"),
        TestCase(input=[[2, 1, 1], [0, 1, 1], [1, 0, 1]], expected=-1, label="example 2"),
        TestCase(input=[[0, 2]], expected=0, label="no fresh"),
        TestCase(input=[[1]], expected=-1, label="single fresh no rotten"),
        TestCase(input=[[2]], expected=0, label="single rotten"),
        TestCase(input=[[1, 1, 1], [1, 1, 1], [1, 1, 1]], expected=-1, label="all fresh no rotten"),
        TestCase(input=[[2, 2], [1, 1], [0, 1]], expected=2, label="multiple rotten sources"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P994RottingOranges)
