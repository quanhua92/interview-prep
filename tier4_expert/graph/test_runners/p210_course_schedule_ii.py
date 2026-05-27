from src.utils.judge_base import JudgeBase, TestCase, register


class P210CourseScheduleII(JudgeBase):
    name = "210. Course Schedule II"
    test_cases = [
        TestCase(input=(2, [[1, 0]]), expected=[0, 1], label="example 1"),
        TestCase(
            input=(4, [[1, 0], [2, 0], [3, 1], [3, 2]]),
            expected=[0, 1, 2, 3],
            label="example 2",
        ),
        TestCase(input=(1, []), expected=[0], label="no prerequisites"),
        TestCase(input=(2, [[1, 0], [0, 1]]), expected=[], label="cycle returns empty"),
        TestCase(input=(3, [[0, 1], [1, 2], [2, 0]]), expected=[], label="3-node cycle"),
        TestCase(
            input=(4, [[0, 1], [0, 2], [0, 3]]),
            expected=[1, 2, 3, 0],
            label="all depend on course 0",
        ),
        TestCase(input=(3, [[2, 1], [1, 0]]), expected=[0, 1, 2], label="linear chain"),
    ]

    def to_stdin(self, tc_input) -> str:
        num_courses, prereqs = tc_input
        parts = [self.serialize_int_array([num_courses, len(prereqs)])]
        for pair in prereqs:
            parts.append(self.serialize_int_array(pair))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P210CourseScheduleII)
