from src.utils.judge_base import JudgeBase, TestCase, register


class P572SubtreeOfAnotherTree(JudgeBase):
    name = "572. Subtree of Another Tree"
    test_cases = [
        TestCase(
            input=([3, 4, 5, 1, 2], [4, 1, 2]),
            expected=True,
            label="example 1",
        ),
        TestCase(
            input=([3, 4, 5, 1, 2, None, None, None, None, 0], [4, 1, 2]),
            expected=False,
            label="example 2",
        ),
        TestCase(
            input=([1, 2, 3], [1, 2, 3]),
            expected=True,
            label="identical trees",
        ),
        TestCase(input=([1], [1]), expected=True, label="single node match"),
        TestCase(
            input=([1, None, 2, None, 3], [2, None, 3]),
            expected=True,
            label="right-skewed subtree",
        ),
        TestCase(input=([1, 2], [3]), expected=False, label="no matching value"),
    ]

    def to_stdin(self, tc_input) -> str:
        root_vals, sub_vals = tc_input
        root_str = " ".join("null" if v is None else str(v) for v in root_vals)
        sub_str = " ".join("null" if v is None else str(v) for v in sub_vals)
        return self.serialize_multi(root_str + "\n", sub_str + "\n")

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P572SubtreeOfAnotherTree)
