from src.utils.judge_base import JudgeBase, TestCase, register


class P407TrappingRainWaterII(JudgeBase):
    name = "407. Trapping Rain Water II"
    test_cases = [
        TestCase(
            input=[[1, 4, 3, 1, 3, 2], [3, 2, 1, 3, 2, 4], [2, 3, 3, 2, 3, 1]],
            expected=4,
            label="example 1",
        ),
        TestCase(
            input=[
                [3, 3, 3, 3, 3],
                [3, 2, 2, 2, 3],
                [3, 2, 1, 2, 3],
                [3, 2, 2, 2, 3],
                [3, 3, 3, 3, 3],
            ],
            expected=10,
            label="example 2",
        ),
        TestCase(input=[[1]], expected=0, label="1x1 no trap"),
        TestCase(
            input=[[5, 5, 5], [5, 1, 5], [5, 5, 5]],
            expected=4,
            label="3x3 basin",
        ),
        TestCase(
            input=[[5, 5, 5, 5], [5, 5, 5, 5]],
            expected=0,
            label="2x4 no interior",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        mat = tc_input
        if not mat:
            return "0 0\n"
        rows = len(mat)
        cols = len(mat[0])
        parts = [f"{rows} {cols}"]
        for row in mat:
            parts.append(" ".join(str(x) for x in row))
        return "\n".join(parts) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P407TrappingRainWaterII)
