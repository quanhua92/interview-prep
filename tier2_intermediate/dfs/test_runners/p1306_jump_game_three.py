from src.utils.judge_base import JudgeBase, TestCase, register


class P1306JumpGameIII(JudgeBase):
    name = "1306. Jump Game III"
    test_cases = [
        TestCase(input=([4, 2, 3, 0, 3, 1, 2], 5), expected=True, label="example 1"),
        TestCase(
            input=([4, 2, 3, 0, 3, 1, 2], 0), expected=True, label="start at index 0"
        ),
        TestCase(input=([3, 0, 2, 1, 2], 2), expected=False, label="cannot reach zero"),
        TestCase(input=([0], 0), expected=True, label="single element zero"),
        TestCase(input=([2], 0), expected=False, label="single element non-zero"),
        TestCase(input=([0, 1], 1), expected=True, label="start next to zero"),
        TestCase(
            input=([1, 1, 1, 1, 0], 0), expected=True, label="linear path to zero"
        ),
        TestCase(
            input=([7, 0, 0, 0, 0, 0, 0, 0], 0),
            expected=True,
            label="jump directly to zero",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P1306JumpGameIII)
