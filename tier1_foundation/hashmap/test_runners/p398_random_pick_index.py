from src.utils.judge_base import JudgeBase, TestCase, register


class P398RandomPickIndex(JudgeBase):
    name = "398. Random Pick Index"
    test_cases = [
        TestCase(
            input=([1, 2, 3, 3, 3], 3),
            expected=4,
            label="returns valid index for target 3",
        ),
        TestCase(
            input=([1, 2, 3, 3, 3], 1),
            expected=0,
            label="single occurrence",
        ),
        TestCase(
            input=([5], 5),
            expected=0,
            label="single element array",
        ),
        TestCase(
            input=([1, 2, 1, 2, 1], 1),
            expected=4,
            label="non-contiguous duplicates",
        ),
        TestCase(
            input=([-1, -2, -1, -3, -1], -1),
            expected=4,
            label="negative numbers with duplicates",
        ),
        TestCase(
            input=([1, 1, 1, 1, 1], 1),
            expected=0,
            label="all same elements",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P398RandomPickIndex)
