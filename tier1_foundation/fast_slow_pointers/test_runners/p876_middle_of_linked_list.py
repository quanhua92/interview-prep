from src.utils.judge_base import JudgeBase, TestCase, register


class P876MiddleOfLinkedList(JudgeBase):
    name = "876. Middle of the Linked List"
    test_cases = [
        TestCase(input=[1, 2, 3, 4, 5], expected=[3, 4, 5], label="odd length"),
        TestCase(input=[1, 2, 3, 4, 5, 6], expected=[4, 5, 6], label="even length"),
        TestCase(input=[1], expected=[1], label="single node"),
        TestCase(input=[1, 2], expected=[2], label="two nodes"),
        TestCase(input=[1, 2, 3], expected=[2, 3], label="three nodes"),
        TestCase(input=[1, -2, 3, -4, 5], expected=[3, -4, 5], label="negative values"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P876MiddleOfLinkedList)
