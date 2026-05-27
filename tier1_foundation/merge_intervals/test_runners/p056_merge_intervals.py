from src.utils.judge_base import JudgeBase, TestCase, register


class P056MergeIntervals(JudgeBase):
    name = "56. Merge Intervals"
    test_cases = [
        TestCase(
            input=[[1, 3], [2, 6], [8, 10], [15, 18]],
            expected=[[1, 6], [8, 10], [15, 18]],
            label="example 1",
        ),
        TestCase(input=[[1, 4], [4, 5]], expected=[[1, 5]], label="example 2"),
        TestCase(input=[[1, 4], [0, 4]], expected=[[0, 4]], label="overlapping start"),
        TestCase(input=[[1, 1]], expected=[[1, 1]], label="single interval"),
        TestCase(
            input=[[1, 4], [2, 3], [3, 5]],
            expected=[[1, 5]],
            label="all overlap into one",
        ),
        TestCase(
            input=[[1, 2], [3, 4], [5, 6]],
            expected=[[1, 2], [3, 4], [5, 6]],
            label="no overlaps",
        ),
        TestCase(
            input=[[1, 10], [2, 3], [4, 5]],
            expected=[[1, 10]],
            label="interval contains others",
        ),
        TestCase(
            input=[[1, 2], [2, 3], [3, 4]],
            expected=[[1, 4]],
            label="adjacent intervals touching",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for row in tc_input:
            lines.append(" ".join(str(x) for x in row))
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_matrix(stdout) == tc_expected


register(P056MergeIntervals)
