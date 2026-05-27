from src.utils.judge_base import JudgeBase, TestCase, register


class P467UniqueSubstringsWraparound(JudgeBase):
    name = "467. Unique Substrings in Wraparound String"
    test_cases = [
        TestCase(input="a", expected=1, label="example 1"),
        TestCase(input="cac", expected=2, label="example 2"),
        TestCase(input="zab", expected=6, label="example 3"),
        TestCase(input="aaaaa", expected=1, label="all same chars only a in wraparound"),
        TestCase(input="zabcdefg", expected=36, label="wraparound chain length 8"),
        TestCase(input="abcdefghijklmnopqrstuvwxyz", expected=351, label="full alphabet"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P467UniqueSubstringsWraparound)
