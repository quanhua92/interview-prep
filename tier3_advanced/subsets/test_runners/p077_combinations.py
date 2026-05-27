from src.utils.judge_base import JudgeBase, TestCase, register


class P077Combinations(JudgeBase):
    name = "77. Combinations"
    test_cases = [
        TestCase(
            input=(4, 2),
            expected=[[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]],
            label="example 1",
        ),
        TestCase(input=(1, 1), expected=[[1]], label="example 2"),
        TestCase(input=(3, 1), expected=[[1], [2], [3]], label="example 3"),
        TestCase(input=(5, 5), expected=[[1, 2, 3, 4, 5]], label="k equals n"),
        TestCase(
            input=(5, 3),
            expected=[
                [1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 3, 4], [1, 3, 5], [1, 4, 5],
                [2, 3, 4], [2, 3, 5], [2, 4, 5], [3, 4, 5],
            ],
            label="mid range",
        ),
        TestCase(input=(2, 2), expected=[[1, 2]], label="smallest k equals n"),
        TestCase(input=(6, 1), expected=[[1], [2], [3], [4], [5], [6]], label="k equals 1 larger n"),
    ]

    def to_stdin(self, tc_input) -> str:
        n, k = tc_input
        return self.serialize_multi(self.serialize_int(n), self.serialize_int(k))

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if not lines and not tc_expected:
            return True
        got = [list(map(int, line.split())) for line in lines]
        return got == tc_expected


register(P077Combinations)
