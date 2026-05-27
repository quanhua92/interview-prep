from src.utils.judge_base import JudgeBase, TestCase, register


class P458PoorPigs(JudgeBase):
    name = "458. Poor Pigs"
    test_cases = [
        TestCase(input=(4, 15, 15), expected=2, label="example 1"),
        TestCase(input=(4, 15, 30), expected=2, label="example 2"),
        TestCase(input=(1, 100, 100), expected=0, label="single bucket"),
        TestCase(input=(125, 1, 1), expected=7, label="single test round"),
        TestCase(input=(1000, 15, 60), expected=5, label="large buckets"),
        TestCase(input=(8, 15, 30), expected=2, label="medium buckets"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(list(tc_input))

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P458PoorPigs)
