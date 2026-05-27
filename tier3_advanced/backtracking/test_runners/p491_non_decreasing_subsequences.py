from src.utils.judge_base import JudgeBase, TestCase, register


class P491NonDecreasingSubsequences(JudgeBase):
    name = "491. Non-decreasing Subsequences"
    test_cases = [
        TestCase(
            input=[4, 6, 7, 7],
            expected=[
                [4, 6], [4, 6, 7], [4, 6, 7, 7], [4, 7],
                [4, 7, 7], [6, 7], [6, 7, 7], [7, 7],
            ],
            label="example 1",
        ),
        TestCase(input=[4, 4, 3, 2, 1], expected=[[4, 4]], label="example 2"),
        TestCase(input=[2, 2, 2], expected=[[2, 2], [2, 2, 2]], label="all same elements"),
        TestCase(input=[5, 4, 3, 2, 1], expected=[], label="strictly decreasing"),
        TestCase(
            input=[1, 2, 3],
            expected=[[1, 2], [1, 2, 3], [1, 3], [2, 3]],
            label="strictly increasing",
        ),
        TestCase(input=[1], expected=[], label="single element"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if not lines and not tc_expected:
            return True
        got = sorted(sorted(map(int, line.split())) for line in lines)
        exp = sorted(sorted(t) for t in tc_expected)
        return got == exp


register(P491NonDecreasingSubsequences)
