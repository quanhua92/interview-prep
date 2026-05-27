from src.utils.judge_base import JudgeBase, TestCase, register


class P621TaskScheduler(JudgeBase):
    name = "621. Task Scheduler"
    test_cases = [
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 2), expected=8, label="example 1"
        ),
        TestCase(
            input=(["A", "C", "A", "B", "D", "B"], 1), expected=6, label="example 2"
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 3), expected=10, label="example 3"
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B", "C", "C", "D"], 2),
            expected=9,
            label="tasks fill all idle slots",
        ),
        TestCase(input=(["A", "A"], 2), expected=4, label="single task type with long cooldown"),
        TestCase(input=(["A", "A", "B", "B"], 0), expected=4, label="no cooldown"),
        TestCase(input=(["A"], 5), expected=1, label="single task"),
        TestCase(input=(["A", "A", "A", "A"], 2), expected=10, label="all same task"),
        TestCase(input=(["A", "B", "C"], 100), expected=3, label="unique tasks large n"),
    ]

    def to_stdin(self, tc_input) -> str:
        tasks_str = " ".join(tc_input[0])
        return self.serialize_multi(
            self.serialize_string(tasks_str),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P621TaskScheduler)
