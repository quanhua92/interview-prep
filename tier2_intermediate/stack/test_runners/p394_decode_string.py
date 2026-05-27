from src.utils.judge_base import JudgeBase, TestCase, register


class P394DecodeString(JudgeBase):
    name = "394. Decode String"
    test_cases = [
        TestCase(input="3[a]2[bc]", expected="aaabcbc", label="example 1"),
        TestCase(input="3[a2[c]]", expected="accaccacc", label="nested"),
        TestCase(
            input="2[abc]3[cd]ef", expected="abcabccdcdcdef", label="multiple segments"
        ),
        TestCase(input="abc", expected="abc", label="no encoding"),
        TestCase(input="10[a]", expected="aaaaaaaaaa", label="multi-digit multiplier"),
        TestCase(input="2[2[2[a]]]", expected="aaaaaaaa", label="deep nesting"),
        TestCase(input="3[a]b", expected="aaab", label="encoded then plain"),
        TestCase(input="a2[b]c", expected="abbc", label="plain-enc-plain"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_string(stdout) == tc_expected


register(P394DecodeString)
