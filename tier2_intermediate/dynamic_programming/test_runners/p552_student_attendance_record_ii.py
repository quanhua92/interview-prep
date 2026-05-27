from src.utils.judge_base import JudgeBase, TestCase, register


class P552StudentAttendanceRecordII(JudgeBase):
    name = "552. Student Attendance Record II"
    test_cases = [
        TestCase(input=2, expected=8, label="example 1"),
        TestCase(input=1, expected=3, label="example 2"),
        TestCase(input=10101, expected=183236316, label="example 3"),
        TestCase(input=3, expected=19, label="n=3"),
        TestCase(input=4, expected=43, label="n=4"),
        TestCase(input=10, expected=3536, label="n=10"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P552StudentAttendanceRecordII)
