from src.utils.judge_base import JudgeBase, TestCase, register


class P514FreedomTrail(JudgeBase):
    name = "514. Freedom Trail"
    test_cases = [
        TestCase(input=("godding", "gd"), expected=4, label="example 1"),
        TestCase(input=("godding", "godding"), expected=13, label="example 2"),
        TestCase(input=("a", "a"), expected=1, label="single char ring and key"),
        TestCase(input=("abc", "cba"), expected=6, label="reverse order key"),
        TestCase(input=("aaaaa", "aaa"), expected=3, label="repeated chars"),
    ]

    def to_stdin(self, tc_input) -> str:
        ring, key = tc_input
        return self.serialize_multi(
            self.serialize_string(ring),
            self.serialize_string(key),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P514FreedomTrail)
