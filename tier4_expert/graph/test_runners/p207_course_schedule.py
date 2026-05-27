from src.utils.judge_base import JudgeBase, TestCase, register


class P207CourseSchedule(JudgeBase):
    name = "207. Course Schedule"
    test_cases = [
        TestCase(input=(2, [[1, 0]]), expected=True, label="example 1"),
        TestCase(input=(2, [[1, 0], [0, 1]]), expected=False, label="example 2"),
        TestCase(input=(1, []), expected=True, label="no prerequisites"),
        TestCase(input=(3, [[0, 1], [1, 2], [2, 0]]), expected=False, label="3-node cycle"),
        TestCase(input=(5, [[0, 1], [1, 2], [2, 3]]), expected=True, label="linear chain disconnected node"),
        TestCase(input=(3, [[1, 0], [2, 0]]), expected=True, label="two deps on one course"),
        TestCase(input=(4, [[0, 1], [1, 2], [2, 3], [3, 1]]), expected=False, label="self-contained cycle"),
    ]

    def to_stdin(self, tc_input) -> str:
        num_courses, prereqs = tc_input
        parts = [self.serialize_int_array([num_courses, len(prereqs)])]
        for pair in prereqs:
            parts.append(self.serialize_int_array(pair))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P207CourseSchedule)
