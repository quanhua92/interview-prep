from src.utils.judge_base import JudgeBase, TestCase, register


class P704BinarySearch(JudgeBase):
    name = "704. Binary Search"
    test_cases = [
        TestCase(input=([-1, 0, 3, 5, 9, 12], 9), expected=4, label="example 1"),
        TestCase(input=([-1, 0, 3, 5, 9, 12], 2), expected=-1, label="example 2"),
        TestCase(input=([5], 5), expected=0, label="single element"),
        TestCase(input=([-1, 0, 3, 5, 9, 12], -2), expected=-1, label="below range"),
        TestCase(input=([-1, 0, 3, 5, 9, 12], 12), expected=5, label="last element"),
        TestCase(input=([1, 2], 1), expected=0, label="two elements first"),
        TestCase(input=([1, 2], 2), expected=1, label="two elements last"),
        TestCase(input=(list(range(-5000, 5001)), 0), expected=5000, label="large array middle target"),
        TestCase(input=([2, 4, 6, 8, 10], 5), expected=-1, label="target between elements"),
        TestCase(input=([-3, -2, -1], -1), expected=2, label="all negative found last"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P704BinarySearch)
