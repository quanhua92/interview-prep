from src.utils.judge_base import JudgeBase, TestCase, register


class P522LongestUncommonSubsequenceII(JudgeBase):
    name = "522. Longest Uncommon Subsequence II"
    test_cases = [
        TestCase(input=["aba", "cdc", "eae"], expected=3, label="example 1"),
        TestCase(input=["aaa", "aaa", "aa"], expected=-1, label="example 2"),
        TestCase(input=["a", "b", "c", "d"], expected=1, label="all length 1 different"),
        TestCase(input=["abc", "abc", "abc"], expected=-1, label="all identical"),
        TestCase(input=["a", "a", "ab", "abc"], expected=3, label="one string longer than rest"),
        TestCase(input=["abc", "abd", "abe"], expected=3, label="same length different chars"),
    ]

    def to_stdin(self, tc_input) -> str:
        n = len(tc_input)
        parts = [self.serialize_int(n)]
        for s in tc_input:
            parts.append(self.serialize_string(s))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P522LongestUncommonSubsequenceII)
