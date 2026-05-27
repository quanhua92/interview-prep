from src.utils.judge_base import JudgeBase, TestCase, register


class P997TownJudge(JudgeBase):
    name = "997. Find the Town Judge"
    test_cases = [
        TestCase(input=(2, [[1, 2]]), expected=2, label="example 1"),
        TestCase(input=(3, [[1, 3], [2, 3]]), expected=3, label="example 2"),
        TestCase(input=(3, [[1, 3], [2, 3], [3, 1]]), expected=-1, label="no judge"),
        TestCase(input=(1, []), expected=1, label="single person"),
        TestCase(
            input=(4, [[1, 3], [2, 3], [4, 3], [3, 4]]),
            expected=-1,
            label="judge candidate trusts someone",
        ),
        TestCase(input=(3, []), expected=-1, label="no trust relationships n>1"),
        TestCase(input=(2, [[1, 2], [2, 1]]), expected=-1, label="mutual trust no judge"),
    ]

    def to_stdin(self, tc_input) -> str:
        n, trust = tc_input
        parts = [self.serialize_int_array([n, len(trust)])]
        for pair in trust:
            parts.append(self.serialize_int_array(pair))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P997TownJudge)
