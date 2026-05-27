from src.utils.judge_base import JudgeBase, TestCase, register


class P354RussianDollEnvelopes(JudgeBase):
    name = "354. Russian Doll Envelopes"
    test_cases = [
        TestCase(input=[[5, 4], [6, 4], [6, 7], [2, 3]], expected=3, label="example 1"),
        TestCase(input=[[1, 1], [1, 1], [1, 1]], expected=1, label="example 2"),
        TestCase(input=[[1, 1]], expected=1, label="single envelope"),
        TestCase(input=[[1, 2], [2, 3], [3, 4]], expected=3, label="strictly increasing"),
        TestCase(input=[[4, 5], [4, 6], [6, 7], [2, 3], [1, 1]], expected=4, label="width ties sorted by height desc"),
        TestCase(input=[[2, 100], [3, 200], [4, 300], [5, 250]], expected=3, label="height breaks chain"),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for row in tc_input:
            lines.append(" ".join(str(x) for x in row))
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P354RussianDollEnvelopes)
