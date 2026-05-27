from src.utils.judge_base import JudgeBase, TestCase, register


class P442FindDuplicates(JudgeBase):
    name = "442. Find All Duplicates in an Array"
    test_cases = [
        TestCase(input=[4, 3, 2, 7, 8, 2, 3, 1], expected=[2, 3], label="example 1"),
        TestCase(input=[1, 1, 2], expected=[1], label="example 2"),
        TestCase(input=[1], expected=[], label="single"),
        TestCase(input=[2, 2], expected=[2], label="all same, n=2"),
        TestCase(input=[1, 2, 2, 1], expected=[2, 1], label="all duplicates, n=4"),
        TestCase(input=[1, 2], expected=[], label="no duplicates"),
        TestCase(
            input=[10, 2, 5, 10, 9, 1, 1, 7, 9, 6],
            expected=[10, 1, 9],
            label="large, multiple duplicates",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P442FindDuplicates)
