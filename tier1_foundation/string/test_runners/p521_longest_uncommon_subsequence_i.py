from src.utils.judge_base import JudgeBase, TestCase, register


class P521LongestUncommonSubsequenceI(JudgeBase):
    name = "521. Longest Uncommon Subsequence I"
    test_cases = [
        TestCase(input=("aba", "cdc"), expected=3, label="example 1"),
        TestCase(input=("aaa", "bbb"), expected=3, label="example 2"),
        TestCase(input=("aaa", "aaa"), expected=-1, label="example 3"),
        TestCase(input=("a", "b"), expected=1, label="single char different"),
        TestCase(input=("a", "aa"), expected=2, label="one is subsequence of other"),
        TestCase(input=("abc", "abcde"), expected=5, label="one longer than other"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_string(tc_input[0]),
            self.serialize_string(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P521LongestUncommonSubsequenceI)
