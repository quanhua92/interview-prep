from src.utils.judge_base import JudgeBase, TestCase, register


class P476NumberComplement(JudgeBase):
    name = "476. Number Complement"
    test_cases = [
        TestCase(input=5, expected=2, label="example 1"),
        TestCase(input=1, expected=0, label="example 2"),
        TestCase(input=2, expected=1, label="power of two"),
        TestCase(input=8, expected=7, label="1000 flips to 0111"),
        TestCase(input=15, expected=0, label="all ones flips to zero"),
        TestCase(input=(1 << 30), expected=(1 << 30) - 1, label="large power of two"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P476NumberComplement)
