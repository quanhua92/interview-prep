from src.utils.judge_base import JudgeBase, TestCase, register


class P449SerializeAndDeserializeBST(JudgeBase):
    name = "449. Serialize and Deserialize BST"
    test_cases = [
        TestCase(input=[2, 1, 3], expected=[2, 1, 3], label="example 1"),
        TestCase(input=[], expected=[], label="empty tree"),
        TestCase(input=[1], expected=[1], label="single node"),
        TestCase(input=[3, 1, 4, None, 2], expected=[3, 1, 4, None, 2], label="bst with left subtree"),
        TestCase(input=[5, 3, 8, 1, 4, 7, 9], expected=[5, 3, 8, 1, 4, 7, 9], label="balanced bst 3 levels"),
        TestCase(input=[4, 2, 5, 1, 3], expected=[4, 2, 5, 1, 3], label="complete bst"),
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

    def _parse_tree_array(self, stdout: str) -> list:
        text = stdout.strip()
        if not text:
            return []
        tokens = text.split()
        result = []
        for t in tokens:
            if t == "null":
                result.append(None)
            else:
                result.append(int(t))
        return result

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self._parse_tree_array(stdout) == tc_expected


register(P449SerializeAndDeserializeBST)
