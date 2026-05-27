from src.utils.judge_base import JudgeBase, TestCase, register


class P460LFUCache(JudgeBase):
    name = "460. LFU Cache"
    test_cases = [
        TestCase(
            input={
                "capacity": 2,
                "ops": [
                    ("put", [1, 1]),
                    ("put", [2, 2]),
                    ("get", [1]),
                    ("put", [3, 3]),
                    ("get", [2]),
                    ("get", [3]),
                    ("put", [4, 4]),
                    ("get", [1]),
                    ("get", [3]),
                    ("get", [4]),
                ],
            },
            expected=["null", "null", "1", "null", "-1", "3", "null", "-1", "3", "4"],
            label="example 1",
        ),
        TestCase(
            input={
                "capacity": 0,
                "ops": [
                    ("put", [1, 1]),
                    ("get", [1]),
                ],
            },
            expected=["null", "-1"],
            label="zero capacity",
        ),
        TestCase(
            input={
                "capacity": 1,
                "ops": [
                    ("put", [1, 10]),
                    ("put", [2, 20]),
                    ("get", [1]),
                    ("get", [2]),
                ],
            },
            expected=["null", "null", "-1", "20"],
            label="capacity 1",
        ),
        TestCase(
            input={
                "capacity": 3,
                "ops": [
                    ("put", [1, 1]),
                    ("put", [2, 2]),
                    ("put", [3, 3]),
                    ("get", [2]),
                    ("put", [4, 4]),
                    ("get", [1]),
                    ("get", [3]),
                    ("get", [4]),
                ],
            },
            expected=["null", "null", "null", "2", "null", "-1", "3", "4"],
            label="capacity 3, eviction",
        ),
        TestCase(
            input={
                "capacity": 2,
                "ops": [
                    ("put", [1, 10]),
                    ("get", [1]),
                    ("put", [2, 20]),
                    ("get", [1]),
                    ("get", [2]),
                ],
            },
            expected=["null", "10", "null", "10", "20"],
            label="get updates frequency",
        ),
        TestCase(
            input={
                "capacity": 2,
                "ops": [
                    ("put", [1, 1]),
                    ("put", [2, 2]),
                    ("get", [1]),
                    ("get", [1]),
                    ("put", [3, 3]),
                    ("get", [2]),
                    ("get", [1]),
                    ("get", [3]),
                ],
            },
            expected=["null", "null", "1", "1", "null", "-1", "1", "3"],
            label="evict least frequently used",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(tc_input["capacity"]), str(len(tc_input["ops"]))]
        for op, args in tc_input["ops"]:
            lines.append(op + " " + " ".join(str(a) for a in args))
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        got = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        return got == tc_expected


register(P460LFUCache)
