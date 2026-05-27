from src.utils.judge_base import JudgeBase, TestCase, register


class P513FindBottomLeftTreeValue(JudgeBase):
    name = "513. Find Bottom Left Tree Value"
    test_cases = [
        TestCase(input=[2, 1, 3], expected=1, label="example 1"),
        TestCase(input=[1, 2, 3, 4, None, 5, 6, None, None, 7], expected=7, label="example 2"),
        TestCase(input=[1], expected=1, label="single node"),
        TestCase(input=[1, 2], expected=2, label="left child only"),
        TestCase(input=[1, None, 2], expected=2, label="right child only"),
        TestCase(input=[1, 2, None, 3, None, 4], expected=4, label="left skewed deep"),
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
        return self.parse_int(stdout) == tc_expected


register(P513FindBottomLeftTreeValue)
