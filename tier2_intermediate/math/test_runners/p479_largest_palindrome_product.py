from src.utils.judge_base import JudgeBase, TestCase, register


class P479LargestPalindromeProduct(JudgeBase):
    name = "479. Largest Palindrome Product"
    test_cases = [
        TestCase(input=2, expected=987, label="example 1"),
        TestCase(input=1, expected=9, label="example 2"),
        TestCase(input=3, expected=123, label="3 digits"),
        TestCase(input=4, expected=597, label="4 digits"),
        TestCase(input=6, expected=1218, label="6 digits (max n)"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P479LargestPalindromeProduct)
