from src.utils.judge_base import JudgeBase, TestCase, register


class P0191NumberOf1Bits(JudgeBase):
    name = "191. Number of 1 Bits"
    test_cases = [
        TestCase(
            input=0b00000000000000000000000000001011,
            expected=3,
            label="example 1",
        ),
        TestCase(
            input=0b00000000000000000000000010000000,
            expected=1,
            label="power of two",
        ),
        TestCase(input=2147483645, expected=30, label="leetcode example 3"),
        TestCase(input=0, expected=0, label="zero"),
        TestCase(input=1, expected=1, label="single bit"),
        TestCase(input=0x55555555, expected=16, label="alternating bits"),
        TestCase(input=(1 << 31) - 1, expected=31, label="max value all bits set"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P0191NumberOf1Bits)
