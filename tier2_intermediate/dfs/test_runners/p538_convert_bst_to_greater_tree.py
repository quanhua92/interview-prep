from src.utils.judge_base import JudgeBase, TestCase, register


class P538ConvertBSTToGreaterTree(JudgeBase):
    name = "538. Convert BST to Greater Tree"
    test_cases = [
        TestCase(
            input=[4, 1, 6, 0, 2, 5, 7, None, None, None, 3, None, None, None, 8],
            expected=[30, 36, 21, 36, 35, 26, 15, None, None, None, 33, None, None, None, 8],
            label="example 1",
        ),
        TestCase(
            input=[0, None, 1],
            expected=[1, None, 1],
            label="example 2",
        ),
        TestCase(input=[2, 1, 3], expected=[5, 6, 3], label="small balanced BST"),
        TestCase(input=[1], expected=[1], label="single node"),
        TestCase(
            input=[1, None, 2, None, 3],
            expected=[6, None, 5, None, 3],
            label="right-skewed BST",
        ),
        TestCase(input=[], expected=[], label="empty tree"),
    ]

    def to_stdin(self, tc_input) -> str:
        if not tc_input:
            return "\n"
        return " ".join("null" if v is None else str(v) for v in tc_input) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        text = stdout.strip()
        if not text and not tc_expected:
            return True
        got = [None if x == "null" else int(x) for x in text.split()]
        while len(got) > 1 and got[-1] is None:
            got.pop()
        return got == tc_expected


register(P538ConvertBSTToGreaterTree)
