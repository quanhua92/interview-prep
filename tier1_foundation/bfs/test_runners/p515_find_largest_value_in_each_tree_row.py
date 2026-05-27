from src.utils.judge_base import JudgeBase, TestCase, register


class P515FindLargestValueInEachTreeRow(JudgeBase):
    name = "515. Find Largest Value in Each Tree Row"
    test_cases = [
        TestCase(input=[1, 3, 2, 5, 3, None, 9], expected=[1, 3, 9], label="example 1"),
        TestCase(input=[1, 2, 3], expected=[1, 3], label="example 2"),
        TestCase(input=[], expected=[], label="empty tree"),
        TestCase(input=[-1, -2, -3, -4], expected=[-1, -2, -4], label="negative values"),
        TestCase(input=[1, 2, None, 3], expected=[1, 2, 3], label="left chain"),
        TestCase(input=[5], expected=[5], label="single node"),
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
        return self.parse_int_array(stdout) == tc_expected


register(P515FindLargestValueInEachTreeRow)
