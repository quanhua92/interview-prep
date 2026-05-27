from src.utils.judge_base import JudgeBase, TestCase, register


class P015ThreeSum(JudgeBase):
    name = "15. 3Sum"
    test_cases = [
        TestCase(
            input=[-1, 0, 1, 2, -1, -4],
            expected=sorted([sorted(t) for t in [[-1, -1, 2], [-1, 0, 1]]]),
            label="example 1",
        ),
        TestCase(input=[0, 1, 1], expected=[], label="no triplets"),
        TestCase(input=[0, 0, 0], expected=[[0, 0, 0]], label="all zeros"),
        TestCase(input=[], expected=[], label="empty"),
        TestCase(input=[-2, 0, 0, 2, 2], expected=[[-2, 0, 2]], label="adjacent duplicate pairs"),
        TestCase(input=[0, 0, 0, 0, 0], expected=[[0, 0, 0]], label="all identical values"),
        TestCase(input=[-3, -3, 0, 1, 1, 2, 2], expected=[[-3, 1, 2]], label="skip-i with left/right dup"),
        TestCase(input=[-2, 0, 0, 0, 2, 2, 2], expected=[[-2, 0, 2], [0, 0, 0]], label="triple duplicate"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [l.strip() for l in stdout.strip().split("\n") if l.strip()]
        if not lines and not tc_expected:
            return True
        got = sorted(sorted(map(int, l.split())) for l in lines)
        exp = sorted(sorted(t) for t in tc_expected)
        return got == exp


register(P015ThreeSum)
