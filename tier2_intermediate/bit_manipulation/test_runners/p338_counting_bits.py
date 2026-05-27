from src.utils.judge_base import JudgeBase, TestCase, register


class P338CountingBits(JudgeBase):
    name = "338. Counting Bits"
    test_cases = [
        TestCase(input=2, expected=[0, 1, 1], label="example 1"),
        TestCase(input=5, expected=[0, 1, 1, 2, 1, 2], label="example 2"),
        TestCase(input=0, expected=[0], label="zero"),
        TestCase(input=1, expected=[0, 1], label="one"),
        TestCase(input=7, expected=[0, 1, 1, 2, 1, 2, 2, 3], label="power-of-2 minus 1"),
        TestCase(
            input=15,
            expected=[0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4],
            label="four bits all",
        ),
        TestCase(
            input=16,
            expected=[0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1],
            label="power of 2",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P338CountingBits)
