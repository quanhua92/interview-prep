from src.utils.judge_base import JudgeBase, TestCase, register


class P887SuperEggDrop(JudgeBase):
    name = "887. Super Egg Drop"
    test_cases = [
        TestCase(input=(1, 1), expected=1, label="1 egg, 1 floor"),
        TestCase(input=(1, 2), expected=2, label="1 egg, 2 floors"),
        TestCase(input=(1, 10), expected=10, label="1 egg, 10 floors"),
        TestCase(input=(2, 1), expected=1, label="2 eggs, 1 floor"),
        TestCase(input=(2, 6), expected=3, label="2 eggs, 6 floors"),
        TestCase(input=(2, 10), expected=4, label="2 eggs, 10 floors"),
        TestCase(input=(2, 100), expected=14, label="classic 2-egg 100-floor"),
        TestCase(input=(3, 14), expected=4, label="3 eggs, 14 floors"),
        TestCase(input=(3, 25), expected=5, label="3 eggs, 25 floors"),
        TestCase(input=(100, 10000), expected=14, label="many eggs, many floors"),
    ]

    def to_stdin(self, tc_input) -> str:
        return f"{tc_input[0]} {tc_input[1]}\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P887SuperEggDrop)
