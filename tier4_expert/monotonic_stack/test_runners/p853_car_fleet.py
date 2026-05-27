from src.utils.judge_base import JudgeBase, TestCase, register


class P853CarFleet(JudgeBase):
    name = "853. Car Fleet"
    test_cases = [
        TestCase(
            input=(12, [10, 8, 0, 5, 3], [2, 4, 1, 1, 3]), expected=3, label="example 1"
        ),
        TestCase(input=(10, [3], [3]), expected=1, label="example 2"),
        TestCase(input=(100, [0, 2, 4], [4, 2, 1]), expected=1, label="all merge"),
        TestCase(input=(10, [8, 0], [2, 1]), expected=2, label="two cars no merge"),
        TestCase(input=(10, [0, 3], [3, 2]), expected=1, label="two cars merge"),
        TestCase(input=(10, [1, 2, 3], [1, 1, 1]), expected=3, label="all same speed"),
    ]

    def to_stdin(self, tc_input) -> str:
        target, position, speed = tc_input
        return self.serialize_multi(
            self.serialize_int(target),
            self.serialize_int_array(position),
            self.serialize_int_array(speed),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P853CarFleet)
