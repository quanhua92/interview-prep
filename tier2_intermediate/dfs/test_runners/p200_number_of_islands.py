from src.utils.judge_base import JudgeBase, TestCase, register


class P200NumberOfIslands(JudgeBase):
    name = "200. Number of Islands"
    test_cases = [
        TestCase(
            input=[
                ["1", "1", "1", "1", "0"],
                ["1", "1", "0", "1", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "0", "0", "0"],
            ],
            expected=1,
            label="example 1",
        ),
        TestCase(
            input=[
                ["1", "1", "0", "0", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "1", "0", "0"],
                ["0", "0", "0", "1", "1"],
            ],
            expected=3,
            label="example 2",
        ),
        TestCase(input=[[]], expected=0, label="empty grid"),
        TestCase(input=[["0"]], expected=0, label="single cell water"),
        TestCase(input=[["1"]], expected=1, label="single cell land"),
        TestCase(
            input=[["1", "0", "1", "0", "1"]],
            expected=3,
            label="single row",
        ),
        TestCase(
            input=[["1"], ["0"], ["1"], ["0"], ["1"]],
            expected=3,
            label="single column",
        ),
        TestCase(
            input=[["1", "1", "1"], ["1", "1", "1"], ["1", "1", "1"]],
            expected=1,
            label="all land 3x3",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        rows = len(tc_input)
        if rows == 0:
            return "0\n"
        cols = len(tc_input[0]) if tc_input[0] else 0
        parts = [f"{rows} {cols}\n"]
        for row in tc_input:
            parts.append("".join(row) + "\n")
        return "".join(parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P200NumberOfIslands)
