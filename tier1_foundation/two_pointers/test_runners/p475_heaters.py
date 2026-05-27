from src.utils.judge_base import JudgeBase, TestCase, register


class P475Heaters(JudgeBase):
    name = "475. Heaters"
    test_cases = [
        TestCase(input=([1, 2, 3], [2]), expected=1, label="example 1"),
        TestCase(input=([1, 2, 3, 4], [1, 4]), expected=1, label="example 2"),
        TestCase(input=([1, 5], [2]), expected=3, label="example 3"),
        TestCase(input=([1], [1]), expected=0, label="house at heater position"),
        TestCase(input=([1, 2, 3, 4, 5, 6], [1, 6]), expected=2, label="houses between heaters"),
        TestCase(input=([10, 20, 30], [15]), expected=15, label="single heater center"),
        TestCase(input=([1, 2, 3], [4, 5, 6]), expected=3, label="all houses before heaters"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int_array(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P475Heaters)
