from src.utils.judge_base import JudgeBase, TestCase, register


class P090SubsetsII(JudgeBase):
    name = "90. Subsets II"
    test_cases = [
        TestCase(
            input=[1, 2, 2],
            expected=[[], [1], [1, 2], [1, 2, 2], [2], [2, 2]],
            label="example 1",
        ),
        TestCase(input=[0], expected=[[], [0]], label="example 2"),
        TestCase(
            input=[2, 2, 2],
            expected=[[], [2], [2, 2], [2, 2, 2]],
            label="all duplicates",
        ),
        TestCase(
            input=[1, 1, 2, 2],
            expected=[[], [1], [1, 1], [1, 1, 2], [1, 1, 2, 2], [1, 2], [1, 2, 2], [2], [2, 2]],
            label="multiple duplicates",
        ),
        TestCase(
            input=[-1, -1, 0],
            expected=[[], [-1], [-1, -1], [-1, -1, 0], [-1, 0], [0]],
            label="negative duplicates",
        ),
        TestCase(
            input=[1, 1, 1, 1],
            expected=[[], [1], [1, 1], [1, 1, 1], [1, 1, 1, 1]],
            label="all same element",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        exp = [t for t in tc_expected if t]
        text = stdout.strip()
        if not text:
            return exp == []
        lines = text.split("\n")
        got = [list(map(int, line.split())) if line.strip() else [] for line in lines]
        got_sorted = sorted(sorted(t) for t in got)
        exp_sorted = sorted(sorted(t) for t in exp)
        return got_sorted == exp_sorted


register(P090SubsetsII)
