from src.utils.judge_base import JudgeBase, TestCase, register


class P564FindTheClosestPalindrome(JudgeBase):
    name = "564. Find the Closest Palindrome"
    test_cases = [
        TestCase(input="123", expected="121", label="example 1"),
        TestCase(input="1", expected="0", label="example 2"),
        TestCase(input="10", expected="9", label="edge at 10"),
        TestCase(input="99", expected="101", label="two same digits"),
        TestCase(input="100", expected="99", label="power of 10"),
        TestCase(input="1283", expected="1331", label="four digit"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_string(stdout) == tc_expected


register(P564FindTheClosestPalindrome)
