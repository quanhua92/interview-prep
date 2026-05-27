from src.utils.judge_base import JudgeBase, TestCase, register


class P253MeetingRooms(JudgeBase):
    name = "253. Meeting Rooms II"
    test_cases = [
        TestCase(input=[[0, 30], [5, 10], [15, 20]], expected=2, label="example 1"),
        TestCase(input=[[7, 10], [2, 4]], expected=1, label="example 2"),
        TestCase(input=[], expected=0, label="no meetings"),
        TestCase(input=[[0, 1]], expected=1, label="single meeting"),
        TestCase(
            input=[[0, 10], [1, 9], [2, 8], [3, 7]],
            expected=4,
            label="all meetings overlap",
        ),
        TestCase(
            input=[[0, 5], [5, 10], [5, 10]],
            expected=2,
            label="meetings end and start at same time",
        ),
        TestCase(
            input=[[0, 30], [0, 30], [0, 30]],
            expected=3,
            label="all same start time",
        ),
        TestCase(
            input=[[0, 1], [1, 2], [2, 3]],
            expected=1,
            label="no overlap sequential",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for row in tc_input:
            lines.append(" ".join(str(x) for x in row))
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P253MeetingRooms)
