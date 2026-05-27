from src.utils.judge_base import JudgeBase, TestCase, register


class P017LetterCombinations(JudgeBase):
    name = "17. Letter Combinations of a Phone Number"
    test_cases = [
        TestCase(
            input="23",
            expected=["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"],
            label="example 1",
        ),
        TestCase(input="", expected=[], label="empty input"),
        TestCase(input="2", expected=["a", "b", "c"], label="single digit"),
        TestCase(input="7", expected=["p", "q", "r", "s"], label="digit with 4 letters"),
        TestCase(input="9", expected=["w", "x", "y", "z"], label="digit 9"),
        TestCase(
            input="79",
            expected=[
                "pw", "px", "py", "pz", "qw", "qx", "qy", "qz",
                "rw", "rx", "ry", "rz", "sw", "sx", "sy", "sz",
            ],
            label="two 4-letter digits",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if not lines and not tc_expected:
            return True
        got = sorted(lines)
        exp = sorted(tc_expected)
        return got == exp


register(P017LetterCombinations)
