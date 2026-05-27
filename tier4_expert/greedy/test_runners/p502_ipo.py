from src.utils.judge_base import JudgeBase, TestCase, register


class P502IPO(JudgeBase):
    name = "502. IPO"
    test_cases = [
        TestCase(input=(2, 0, [1, 2, 3], [0, 1, 1]), expected=4, label="example 1"),
        TestCase(input=(3, 0, [1, 2, 3], [0, 1, 2]), expected=6, label="example 2"),
        TestCase(input=(1, 0, [1, 2, 3], [0, 0, 0]), expected=3, label="k less than projects"),
        TestCase(input=(10, 0, [1, 2], [0, 0]), expected=3, label="k more than projects"),
        TestCase(input=(1, 1, [5], [1]), expected=6, label="single project"),
        TestCase(input=(2, 5, [3, 4], [1, 2]), expected=12, label="all affordable"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int(tc_input[0]),
            self.serialize_int(tc_input[1]),
            self.serialize_int_array(tc_input[2]),
            self.serialize_int_array(tc_input[3]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P502IPO)
