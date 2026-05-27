from src.utils.judge_base import JudgeBase, TestCase, register


class P695MaxAreaIsland(JudgeBase):
    name = "695. Max Area of Island"
    test_cases = [
        TestCase(
            input=[
                [0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0],
                [0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0],
                [0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0],
            ],
            expected=6,
            label="example 1",
        ),
        TestCase(input=[[0, 0, 0, 0, 0, 0, 0, 0]], expected=0, label="example 2"),
        TestCase(input=[[1]], expected=1, label="single cell land"),
        TestCase(input=[[0]], expected=0, label="single cell water"),
        TestCase(
            input=[[1, 1, 1], [1, 1, 1], [1, 1, 1]],
            expected=9,
            label="all land 3x3",
        ),
        TestCase(
            input=[[1, 0, 1, 0, 1]],
            expected=1,
            label="single row alternating",
        ),
        TestCase(
            input=[[1], [0], [1], [0], [1]],
            expected=1,
            label="single column alternating",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        if not tc_input or not tc_input[0]:
            return "0 0\n"
        rows = len(tc_input)
        cols = len(tc_input[0])
        parts = [f"{rows} {cols}\n"]
        for row in tc_input:
            parts.append(" ".join(str(x) for x in row) + "\n")
        return "".join(parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P695MaxAreaIsland)
