from src.utils.judge_base import JudgeBase, TestCase, register


class P134GasStation(JudgeBase):
    name = "134. Gas Station"
    test_cases = [
        TestCase(
            input=([1, 2, 3, 4, 5], [3, 4, 5, 1, 2]), expected=3, label="example 1"
        ),
        TestCase(input=([2, 3, 4], [3, 4, 3]), expected=-1, label="example 2"),
        TestCase(
            input=([5, 1, 2, 3, 4], [4, 4, 1, 5, 1]), expected=4, label="example 3"
        ),
        TestCase(input=([5], [4]), expected=0, label="single station possible"),
        TestCase(input=([3], [4]), expected=-1, label="single station impossible"),
        TestCase(input=([0, 0, 0], [0, 0, 0]), expected=0, label="all zeros"),
        TestCase(
            input=([10, 0, 0, 0, 0], [1, 1, 1, 1, 1]),
            expected=0,
            label="large surplus at start",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int_array(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P134GasStation)
