from src.utils.judge_base import JudgeBase, TestCase, register


class P455AssignCookies(JudgeBase):
    name = "455. Assign Cookies"
    test_cases = [
        TestCase(input=([1, 2, 3], [1, 1]), expected=1, label="example 1"),
        TestCase(input=([1, 2], [1, 2, 3]), expected=2, label="example 2"),
        TestCase(input=([], [1, 2, 3]), expected=0, label="no children"),
        TestCase(input=([1, 2], []), expected=0, label="no cookies"),
        TestCase(input=([10, 11], [1, 2, 3]), expected=0, label="all cookies too small"),
        TestCase(input=([1, 2, 3], [3, 3, 3]), expected=3, label="all satisfied"),
        TestCase(input=([5], [5]), expected=1, label="exact match"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int_array(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P455AssignCookies)
