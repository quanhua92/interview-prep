from src.utils.judge_base import JudgeBase, TestCase, register


class P482LicenseKeyFormatting(JudgeBase):
    name = "482. License Key Formatting"
    test_cases = [
        TestCase(input=("5F3Z-2e-9-w", 4), expected="5F3Z-2E9W", label="example 1"),
        TestCase(input=("2-5g-3-J", 2), expected="2-5G-3J", label="example 2"),
        TestCase(input=("a", 1), expected="A", label="single char no dash"),
        TestCase(input=("---", 3), expected="", label="only dashes"),
        TestCase(input=("2-4A0r7-4k", 4), expected="24A0-R74K", label="even groups no short first"),
        TestCase(input=("aa-aa-aa-aa-aa-aa", 1), expected="A-A-A-A-A-A-A-A-A-A-A-A", label="k=1"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_string(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_string(stdout) == tc_expected


register(P482LicenseKeyFormatting)
