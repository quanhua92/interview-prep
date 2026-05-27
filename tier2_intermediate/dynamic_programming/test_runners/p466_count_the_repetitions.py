from src.utils.judge_base import JudgeBase, TestCase, register


class P466CountTheRepetitions(JudgeBase):
    name = "466. Count The Repetitions"
    test_cases = [
        TestCase(input=("acb", 4, "ab", 2), expected=2, label="example 1"),
        TestCase(input=("acb", 1, "acb", 1), expected=1, label="example 2"),
        TestCase(input=("a", 100, "a", 1), expected=100, label="single char repeated"),
        TestCase(input=("a", 1, "b", 1), expected=0, label="impossible char"),
        TestCase(input=("abc", 10, "ac", 1), expected=10, label="each s1 yields one s2 match"),
        TestCase(input=("aba", 3, "ab", 1), expected=3, label="overlap matching"),
    ]

    def to_stdin(self, tc_input) -> str:
        s1, n1, s2, n2 = tc_input
        return self.serialize_multi(
            self.serialize_string(s1),
            self.serialize_int(n1),
            self.serialize_string(s2),
            self.serialize_int(n2),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P466CountTheRepetitions)
