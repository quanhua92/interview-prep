from src.utils.judge_base import JudgeBase, TestCase, register


class P057InsertInterval(JudgeBase):
    name = "57. Insert Interval"
    test_cases = [
        TestCase(
            input=([[1, 3], [6, 9]], [2, 5]),
            expected=[[1, 5], [6, 9]],
            label="example 1",
        ),
        TestCase(
            input=([[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], [4, 8]),
            expected=[[1, 2], [3, 10], [12, 16]],
            label="example 2",
        ),
        TestCase(input=([], [5, 7]), expected=[[5, 7]], label="empty intervals"),
        TestCase(input=([[1, 5]], [2, 3]), expected=[[1, 5]], label="contained"),
        TestCase(
            input=([[3, 5], [6, 9]], [1, 2]),
            expected=[[1, 2], [3, 5], [6, 9]],
            label="insert before all",
        ),
        TestCase(
            input=([[1, 2], [3, 5]], [6, 9]),
            expected=[[1, 2], [3, 5], [6, 9]],
            label="insert after all",
        ),
        TestCase(
            input=([[1, 3], [6, 9]], [0, 2]),
            expected=[[0, 3], [6, 9]],
            label="merge with first interval",
        ),
        TestCase(
            input=([[1, 3], [6, 9]], [8, 10]),
            expected=[[1, 3], [6, 10]],
            label="merge with last interval",
        ),
        TestCase(
            input=([[1, 2], [4, 5]], [2, 4]),
            expected=[[1, 5]],
            label="bridge gap between intervals",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        intervals, new_interval = tc_input
        lines = [str(len(intervals))]
        for row in intervals:
            lines.append(" ".join(str(x) for x in row))
        lines.append(" ".join(str(x) for x in new_interval))
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_matrix(stdout) == tc_expected


register(P057InsertInterval)
