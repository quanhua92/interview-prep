from src.utils.judge_base import JudgeBase, TestCase, register


class P684RedundantConnection(JudgeBase):
    name = "684. Redundant Connection"
    test_cases = [
        TestCase(input=[[1, 2], [1, 3], [2, 3]], expected=[2, 3], label="example 1"),
        TestCase(
            input=[[1, 2], [2, 3], [3, 4], [1, 4], [1, 5]],
            expected=[1, 4],
            label="example 2",
        ),
        TestCase(input=[[1, 2], [2, 3], [3, 1]], expected=[3, 1], label="triangle of 3"),
        TestCase(
            input=[[1, 2], [1, 3], [1, 4], [1, 5], [2, 3]],
            expected=[2, 3],
            label="redundant at end star",
        ),
        TestCase(
            input=[[1, 2], [1, 3], [1, 4], [2, 3]],
            expected=[2, 3],
            label="last edge closes triangle",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for u, v in tc_input:
            lines.append(f"{u} {v}")
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P684RedundantConnection)
