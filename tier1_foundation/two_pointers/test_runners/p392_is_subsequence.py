from src.utils.judge_base import JudgeBase, TestCase, register


class P392IsSubsequence(JudgeBase):
    name = "392. Is Subsequence"
    test_cases = [
        TestCase(input=("abc", "ahbgdc"), expected=True, label="example 1"),
        TestCase(input=("axc", "ahbgdc"), expected=False, label="example 2"),
        TestCase(input=("", "ahbgdc"), expected=True, label="empty s is subsequence"),
        TestCase(input=("abc", "abc"), expected=True, label="s equals t"),
        TestCase(input=("abcd", "abc"), expected=False, label="s longer than t"),
        TestCase(input=("z", "aaaaa"), expected=False, label="single char not found"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_string(tc_input[0]),
            self.serialize_string(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P392IsSubsequence)
