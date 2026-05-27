from src.utils.judge_base import JudgeBase, TestCase, register


class P488ZumaGame(JudgeBase):
    name = "488. Zuma Game"
    test_cases = [
        TestCase(input=("WRRBBW", "RB"), expected=-1, label="example 1"),
        TestCase(input=("WWRRBBWW", "WRBRW"), expected=2, label="example 2"),
        TestCase(input=("G", "GGGGG"), expected=2, label="example 3"),
        TestCase(input=("RBYYBBRR", "YRB"), expected=1, label="one insertion clears chain reaction"),
        TestCase(input=("RRWWRRBB", "WWB"), expected=2, label="insert triggers cascade"),
        TestCase(input=("R", "R"), expected=-1, label="insufficient balls single"),
        TestCase(input=("RR", "RR"), expected=1, label="pair plus one makes triple"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_string(tc_input[0]),
            self.serialize_string(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P488ZumaGame)
