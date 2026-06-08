from src.utils.judge_base import JudgeBase, TestCase, register


class P382LinkedListRandomNode(JudgeBase):
    name = "382. Linked List Random Node"
    test_cases = [
        TestCase(input=[1, 2, 3], expected=3, label="reservoir sampling with seed 42"),
        TestCase(input=[1, 2, 3, 4], expected=3, label="even length with seed 42"),
        TestCase(input=[4], expected=4, label="single node"),
        TestCase(input=[1, 2], expected=2, label="two nodes with seed 42"),
        TestCase(input=[5, 6, 7], expected=7, label="three nodes with seed 42"),
        TestCase(input=[1, 2, 3, 4, 5], expected=3, label="five nodes with seed 42"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P382LinkedListRandomNode)
