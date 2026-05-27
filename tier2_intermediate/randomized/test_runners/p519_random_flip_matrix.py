from src.utils.judge_base import JudgeBase, TestCase, register


class P519RandomFlipMatrix(JudgeBase):
    name = "519. Random Flip Matrix"
    test_cases = [
        TestCase(input=(1, 1, 1), expected=1, label="single cell one flip"),
        TestCase(input=(2, 2, 4), expected=4, label="flip all cells in 2x2"),
        TestCase(input=(3, 1, 3), expected=3, label="column matrix flip all"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int(tc_input[0]),
            self.serialize_int(tc_input[1]),
            self.serialize_int(tc_input[2]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P519RandomFlipMatrix)
