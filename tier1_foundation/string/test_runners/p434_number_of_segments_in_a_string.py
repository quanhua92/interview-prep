from src.utils.judge_base import JudgeBase, TestCase, register


class P434NumberOfSegmentsInAString(JudgeBase):
    name = "434. Number of Segments in a String"
    test_cases = [
        TestCase(input="Hello, my name is John", expected=5, label="example 1"),
        TestCase(input="Hello", expected=1, label="example 2"),
        TestCase(input="", expected=0, label="empty string"),
        TestCase(input="   ", expected=0, label="only spaces"),
        TestCase(input="    foo    bar   ", expected=2, label="leading/trailing/multiple spaces"),
        TestCase(input="a b c d e", expected=5, label="single char segments"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P434NumberOfSegmentsInAString)
