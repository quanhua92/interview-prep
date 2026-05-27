from src.utils.judge_base import JudgeBase, TestCase, register

NL = None


class P450DeleteNodeInBST(JudgeBase):
    name = "450. Delete Node in a BST"
    test_cases = [
        TestCase(
            input=([5, 3, 6, 2, 4, None, 7], 3),
            expected=[5, 4, 6, 2, None, None, 7],
            label="example 1",
        ),
        TestCase(
            input=([5, 3, 6, 2, 4, None, 7], 0),
            expected=[5, 3, 6, 2, 4, None, 7],
            label="example 2",
        ),
        TestCase(input=([None], 0), expected=[None], label="example 3"),
        TestCase(
            input=([5], 5), expected=[None], label="delete single node root"
        ),
        TestCase(
            input=([3, 1, 4], 3),
            expected=[4, 1],
            label="delete root with two children",
        ),
        TestCase(
            input=([2, 1, 3], 1),
            expected=[2, None, 3],
            label="delete left leaf",
        ),
        TestCase(
            input=([5, 3, None, 2, None, 1], 3),
            expected=[5, 2, None, 1],
            label="delete node with only left child",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        tree_vals, key = tc_input
        serialized = " ".join(
            "null" if v is None else str(v) for v in tree_vals
        )
        return self.serialize_multi(serialized + "\n", self.serialize_int(key))

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        got = [None if x == "null" else int(x) for x in stdout.strip().split()]
        while len(got) > 1 and got[-1] is None:
            got.pop()
        return got == tc_expected


register(P450DeleteNodeInBST)
