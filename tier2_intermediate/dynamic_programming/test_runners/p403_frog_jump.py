from src.utils.judge_base import JudgeBase, TestCase, register


class P403FrogJump(JudgeBase):
    name = "403. Frog Jump"
    test_cases = [
        TestCase(input=[0, 1, 3, 5, 6, 8, 12, 17], expected=True, label="example 1"),
        TestCase(input=[0, 1, 2, 3, 4, 8, 9, 11], expected=False, label="example 2"),
        TestCase(input=[0, 1], expected=True, label="minimum 2 stones"),
        TestCase(input=[0, 2], expected=False, label="gap too large for first jump"),
        TestCase(input=[0, 1, 3, 6, 10, 15, 21], expected=True, label="increasing jumps 1,2,3,4,5,6"),
        TestCase(input=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9], expected=True, label="consecutive stones"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P403FrogJump)
