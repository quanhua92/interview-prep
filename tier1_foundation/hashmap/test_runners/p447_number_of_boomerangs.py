from src.utils.judge_base import JudgeBase, TestCase, register


class P447NumberOfBoomerangs(JudgeBase):
    name = "447. Number of Boomerangs"
    test_cases = [
        TestCase(input=[[0, 0], [1, 0], [2, 0]], expected=2, label="example 1"),
        TestCase(input=[[1, 1], [2, 2], [3, 3]], expected=2, label="example 2"),
        TestCase(input=[[1, 1]], expected=0, label="example 3"),
        TestCase(input=[[0, 0], [1, 0]], expected=0, label="only 2 points"),
        TestCase(input=[[0, 0], [0, 1], [1, 0], [1, 1]], expected=8, label="square 4 points"),
        TestCase(input=[[0, 0], [1, 1], [1, -1]], expected=2, label="isoceles triangle"),
        TestCase(input=[[0, 0], [3, 4], [3, -4]], expected=2, label="isoceles different heights"),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for point in tc_input:
            lines.append(f"{point[0]} {point[1]}")
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P447NumberOfBoomerangs)
