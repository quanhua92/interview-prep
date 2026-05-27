from src.utils.judge_base import JudgeBase, TestCase, register


class P621bTaskSchedulerMulti(JudgeBase):
    name = "621b. Task Scheduler with Multiple Machines"
    test_cases = [
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 2, 1),
            expected=8,
            label="LC621 ex1 m=1",
        ),
        TestCase(
            input=(["A", "C", "A", "B", "D", "B"], 1, 1),
            expected=6,
            label="LC621 ex2 m=1",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 3, 1),
            expected=10,
            label="LC621 ex3 m=1",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B", "C", "C", "D"], 2, 1),
            expected=9,
            label="fill idle slots m=1",
        ),
        TestCase(
            input=(["A", "A"], 2, 1),
            expected=4,
            label="single task type m=1",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 2, 2),
            expected=4,
            label="basic parallelism m=2",
        ),
        TestCase(
            input=(["A", "C", "A", "B", "D", "B"], 1, 2),
            expected=3,
            label="unique tasks m=2",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 3, 2),
            expected=5,
            label="large cooldown m=2",
        ),
        TestCase(
            input=(["A", "A", "A", "B", "B", "B"], 2, 10),
            expected=1,
            label="very many machines m=10",
        ),
        TestCase(
            input=(["A"], 5, 1),
            expected=1,
            label="single task n=5 m=1",
        ),
        TestCase(
            input=(["A"], 5, 3),
            expected=1,
            label="single task n=5 m=3",
        ),
        TestCase(
            input=(["A", "B", "C"], 0, 5),
            expected=1,
            label="more machines than tasks n=0",
        ),
        TestCase(
            input=(["A", "A", "A", "A"], 0, 2),
            expected=2,
            label="n=0 same task m=2 (per-machine cooldown)",
        ),
        TestCase(
            input=(["A", "B", "C", "D"], 1, 3),
            expected=2,
            label="m=3 n=1 four unique tasks",
        ),
        TestCase(
            input=(["A", "A", "A", "A"], 1, 2),
            expected=3,
            label="all same task m=2",
        ),
        TestCase(
            input=(["A", "A", "A", "A", "A", "A"], 1, 3),
            expected=3,
            label="all same task m=3",
        ),
        TestCase(
            input=(["A", "B", "C", "D", "E"], 0, 2),
            expected=3,
            label="unique tasks no cooldown m=2",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        tasks_str = " ".join(tc_input[0])
        return self.serialize_multi(
            self.serialize_string(tasks_str),
            self.serialize_int(tc_input[1]),
            self.serialize_int(tc_input[2]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P621bTaskSchedulerMulti)
