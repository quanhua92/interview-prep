from src.utils.judge_base import JudgeBase, TestCase, register


class P495TeemoAttacking(JudgeBase):
    name = "495. Teemo Attacking"
    test_cases = [
        TestCase(input=([1, 4], 2), expected=4, label="example 1"),
        TestCase(input=([1, 2], 2), expected=3, label="example 2"),
        TestCase(input=([1], 2), expected=2, label="single attack"),
        TestCase(input=([1, 2, 3, 4, 5], 1), expected=5, label="consecutive attacks, duration 1"),
        TestCase(input=([1, 3, 5, 7, 9], 2), expected=10, label="non-overlapping attacks"),
        TestCase(input=([1, 1, 1, 1], 5), expected=5, label="duplicate timestamps"),
    ]

    def to_stdin(self, tc_input) -> str:
        time_series, duration = tc_input
        return self.serialize_multi(
            self.serialize_int_array(time_series),
            self.serialize_int(duration),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P495TeemoAttacking)
