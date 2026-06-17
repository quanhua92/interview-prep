from src.utils.judge_base import JudgeBase, TestCase, register


class P519RandomFlipMatrix(JudgeBase):
    name = "519. Random Flip Matrix"
    test_cases = [
        TestCase(input=(1, 1, 1), expected=(1, 1, 1), label="single cell one flip"),
        TestCase(input=(2, 2, 4), expected=(2, 2, 4), label="flip all cells in 2x2"),
        TestCase(input=(3, 1, 3), expected=(3, 1, 3), label="column matrix flip all"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int(tc_input[0]),
            self.serialize_int(tc_input[1]),
            self.serialize_int(tc_input[2]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        m, n, num = tc_expected
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if len(lines) != num:
            return False
        seen = set()
        for line in lines:
            parts = line.split()
            if len(parts) != 2:
                return False
            r, c = int(parts[0]), int(parts[1])
            if not (0 <= r < m and 0 <= c < n):
                return False
            if (r, c) in seen:
                return False
            seen.add((r, c))
        return True


register(P519RandomFlipMatrix)
