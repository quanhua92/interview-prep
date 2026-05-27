from src.utils.judge_base import JudgeBase, TestCase, register


class P070ClimbingStairs(JudgeBase):
    name = "70. Climbing Stairs"
    test_cases = [
        TestCase(input=2, expected=2, label="example 1"),
        TestCase(input=3, expected=3, label="example 2"),
        TestCase(input=1, expected=1, label="base case"),
        TestCase(input=10, expected=89, label="larger"),
        TestCase(input=45, expected=1836311903, label="max constraint"),
        TestCase(input=4, expected=5, label="n=4"),
        TestCase(input=5, expected=8, label="n=5"),
        TestCase(input=6, expected=13, label="n=6"),
        TestCase(input=20, expected=10946, label="n=20"),
        TestCase(input=44, expected=1134903170, label="near max constraint"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P070ClimbingStairs)
