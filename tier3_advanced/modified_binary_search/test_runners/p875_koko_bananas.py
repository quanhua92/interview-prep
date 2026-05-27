from src.utils.judge_base import JudgeBase, TestCase, register


class P875KokoBananas(JudgeBase):
    name = "875. Koko Eating Bananas"
    test_cases = [
        TestCase(input=([3, 6, 7, 11], 8), expected=4, label="example 1"),
        TestCase(input=([30, 11, 23, 4, 20], 5), expected=30, label="example 2"),
        TestCase(input=([30, 11, 23, 4, 20], 6), expected=23, label="example 3"),
        TestCase(input=([1], 1), expected=1, label="single pile single hour"),
        TestCase(input=([312884470], 970709593), expected=1, label="single pile many hours"),
        TestCase(input=([1, 1, 1, 1], 4), expected=1, label="all ones h equals length"),
        TestCase(input=([1000000000, 1000000000], 3), expected=1000000000, label="large values tight deadline"),
        TestCase(input=([5, 5, 5, 5, 5], 10), expected=3, label="uniform piles extra hours"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P875KokoBananas)
