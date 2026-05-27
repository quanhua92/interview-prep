from src.utils.judge_base import JudgeBase, TestCase, register


class P912SortAnArray(JudgeBase):
    name = "912. Sort an Array"
    test_cases = [
        TestCase(input=[5, 2, 3, 1], expected=[1, 2, 3, 5], label="example 1"),
        TestCase(
            input=[5, 1, 1, 2, 0, 0], expected=[0, 0, 1, 1, 2, 5], label="duplicates"
        ),
        TestCase(input=[1], expected=[1], label="single element"),
        TestCase(input=[], expected=[], label="empty array"),
        TestCase(input=[1, 2, 3, 4, 5], expected=[1, 2, 3, 4, 5], label="already sorted"),
        TestCase(input=[5, 4, 3, 2, 1], expected=[1, 2, 3, 4, 5], label="reverse sorted"),
        TestCase(input=[7, 7, 7, 7], expected=[7, 7, 7, 7], label="all same elements"),
        TestCase(input=[-5, -3, -8, -1], expected=[-8, -5, -3, -1], label="negative numbers"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P912SortAnArray)
