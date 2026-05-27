from src.utils.judge_base import JudgeBase, TestCase, register


class P518CoinChangeII(JudgeBase):
    name = "518. Coin Change II"
    test_cases = [
        TestCase(input=(5, [1, 2, 5]), expected=4, label="example 1"),
        TestCase(input=(3, [2]), expected=0, label="example 2"),
        TestCase(input=(10, [10]), expected=1, label="example 3"),
        TestCase(input=(0, [1, 2, 5]), expected=1, label="zero amount"),
        TestCase(input=(1, [1]), expected=1, label="single coin exact amount"),
        TestCase(input=(500, [1, 2, 5]), expected=12701, label="large amount"),
    ]

    def to_stdin(self, tc_input) -> str:
        amount, coins = tc_input
        return self.serialize_multi(
            self.serialize_int(amount),
            self.serialize_int_array(coins),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P518CoinChangeII)
