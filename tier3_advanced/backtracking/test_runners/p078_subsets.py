from src.utils.judge_base import JudgeBase, TestCase, register


class P078Subsets(JudgeBase):
    name = "78. Subsets"
    test_cases = [
        TestCase(
            input=[1, 2, 3],
            expected=[[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]],
            label="example 1",
        ),
        TestCase(input=[0], expected=[[], [0]], label="example 2"),
        TestCase(input=[1, 2], expected=[[], [1], [1, 2], [2]], label="two elements"),
        TestCase(
            input=[-1, 0, 1],
            expected=[[], [-1], [-1, 0], [-1, 0, 1], [-1, 1], [0], [0, 1], [1]],
            label="negative numbers",
        ),
        TestCase(
            input=[1, 2, 3, 4],
            expected=[
                [], [1], [1, 2], [1, 2, 3], [1, 2, 3, 4], [1, 2, 4], [1, 3],
                [1, 3, 4], [1, 4], [2], [2, 3], [2, 3, 4], [2, 4], [3], [3, 4], [4],
            ],
            label="four elements",
        ),
        TestCase(input=[3, 1], expected=[[], [3], [3, 1], [1]], label="unsorted input"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        exp = [t for t in tc_expected if t]
        text = stdout.strip()
        if not text:
            return exp == []
        lines = text.split("\n")
        got = sorted(sorted(map(int, line.split())) if line.strip() else [] for line in lines)
        exp_sorted = sorted(sorted(t) for t in exp)
        return got == exp_sorted


register(P078Subsets)
