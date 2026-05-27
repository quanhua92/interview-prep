from src.utils.judge_base import JudgeBase, TestCase, register


class P278FirstBadVersion(JudgeBase):
    name = "278. First Bad Version"
    test_cases = [
        TestCase(input=(5, 4), expected=4, label="example 1"),
        TestCase(input=(1, 1), expected=1, label="single version, bad"),
        TestCase(input=(3, 3), expected=3, label="last version is bad"),
        TestCase(input=(10, 7), expected=7, label="middle version is bad"),
        TestCase(input=(2, 1), expected=1, label="first version is bad"),
        TestCase(input=(100, 100), expected=100, label="large n, last is bad"),
        TestCase(input=(100000, 1), expected=1, label="large n, first is bad"),
        TestCase(input=(2, 2), expected=2, label="small n last bad"),
        TestCase(input=(1000000, 999999), expected=999999, label="large n near end"),
        TestCase(input=(2147483647, 1), expected=1, label="max int overflow safe"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P278FirstBadVersion)
