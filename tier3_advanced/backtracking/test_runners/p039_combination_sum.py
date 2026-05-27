from src.utils.judge_base import JudgeBase, TestCase, register


class P039CombinationSum(JudgeBase):
    name = "39. Combination Sum"
    test_cases = [
        TestCase(input=([2, 3, 6, 7], 7), expected=[[2, 2, 3], [7]], label="example 1"),
        TestCase(
            input=([2, 3, 5], 8),
            expected=[[2, 2, 2, 2], [2, 3, 3], [3, 5]],
            label="example 2",
        ),
        TestCase(input=([2], 1), expected=[], label="no solution"),
        TestCase(input=([5], 5), expected=[[5]], label="single candidate equals target"),
        TestCase(input=([2], 4), expected=[[2, 2]], label="reuse single candidate"),
        TestCase(
            input=([8, 7, 4, 3], 11),
            expected=[[3, 4, 4], [3, 8], [4, 7]],
            label="unsorted candidates multiple combos",
        ),
        TestCase(input=([3, 5], 7), expected=[], label="no valid combination"),
        TestCase(input=([3], 9), expected=[[3, 3, 3]], label="triple reuse"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if not lines and not tc_expected:
            return True
        got = sorted(sorted(map(int, line.split())) for line in lines)
        exp = sorted(sorted(t) for t in tc_expected)
        return got == exp


register(P039CombinationSum)
