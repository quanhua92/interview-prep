from src.utils.judge_base import JudgeBase, TestCase, register

NULL_VAL = -2147483648


class P102LevelOrder(JudgeBase):
    name = "102. Binary Tree Level Order Traversal"
    test_cases = [
        TestCase(input=[3, 9, 20, None, None, 15, 7], expected=[[3], [9, 20], [15, 7]], label="example 1"),
        TestCase(input=[1], expected=[[1]], label="example 2"),
        TestCase(input=[], expected=[], label="empty"),
        TestCase(input=[1, None, 2], expected=[[1], [2]], label="right child only"),
        TestCase(input=[1, 2, None], expected=[[1], [2]], label="left child only"),
        TestCase(input=[5, 3, 8, 1, 4, 7, 9], expected=[[5], [3, 8], [1, 4, 7, 9]], label="full binary tree depth 2"),
        TestCase(input=[-1, -2, -3], expected=[[-1], [-2, -3]], label="negative values"),
        TestCase(input=[1, 1, 1, 1, 1, 1, 1], expected=[[1], [1, 1], [1, 1, 1, 1]], label="all same value"),
    ]

    def _serialize_tree_array(self, arr) -> str:
        if not arr:
            return "0\n"
        parts = []
        for v in arr:
            if v is None:
                parts.append("null")
            else:
                parts.append(str(v))
        return str(len(arr)) + "\n" + " ".join(parts) + "\n"

    def to_stdin(self, tc_input) -> str:
        return self._serialize_tree_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_matrix(stdout) == tc_expected


register(P102LevelOrder)
