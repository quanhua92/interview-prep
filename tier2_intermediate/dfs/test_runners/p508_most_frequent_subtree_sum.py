from src.utils.judge_base import JudgeBase, TestCase, register


class P508MostFrequentSubtreeSum(JudgeBase):
    name = "508. Most Frequent Subtree Sum"
    test_cases = [
        TestCase(input=[5, 2, -3], expected=sorted([-3, 2, 4]), label="example 1"),
        TestCase(input=[5, 2, -5], expected=[2], label="example 2"),
        TestCase(input=[1], expected=[1], label="single node"),
        TestCase(input=[1, 2, 3], expected=sorted([2, 3, 6]), label="balanced tree"),
        TestCase(
            input=[-1, -2, -3], expected=sorted([-6, -3, -2]), label="all negative values"
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return " ".join("null" if v is None else str(v) for v in tc_input) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        got = sorted(int(x) for x in stdout.strip().split())
        return got == tc_expected


register(P508MostFrequentSubtreeSum)
