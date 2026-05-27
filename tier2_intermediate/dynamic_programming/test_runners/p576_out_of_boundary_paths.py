from src.utils.judge_base import JudgeBase, TestCase, register


class P576OutOfBoundaryPaths(JudgeBase):
    name = "576. Out of Boundary Paths"
    test_cases = [
        TestCase(input=(2, 2, 2, 0, 0), expected=6, label="example 1"),
        TestCase(input=(1, 3, 3, 0, 1), expected=12, label="example 2"),
        TestCase(input=(1, 1, 1, 0, 0), expected=4, label="1x1 grid single move"),
        TestCase(input=(2, 2, 1, 0, 0), expected=2, label="corner 1 move"),
        TestCase(input=(3, 3, 0, 1, 1), expected=0, label="zero moves"),
    ]

    def to_stdin(self, tc_input) -> str:
        m, n, max_move, start_row, start_col = tc_input
        return self.serialize_multi(
            self.serialize_int(m),
            self.serialize_int(n),
            self.serialize_int(max_move),
            self.serialize_int(start_row),
            self.serialize_int(start_col),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P576OutOfBoundaryPaths)
