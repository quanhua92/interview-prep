from src.utils.judge_base import JudgeBase, TestCase, register


class P322CoinChange(JudgeBase):
    name = "322. Coin Change"
    test_cases = [
        TestCase(input=([1, 2, 5], 11), expected=3, label="example 1"),
        TestCase(input=([2], 3), expected=-1, label="example 2"),
        TestCase(input=([1], 0), expected=0, label="zero amount"),
        TestCase(input=([1], 1), expected=1, label="smallest amount"),
        TestCase(input=([1, 3, 4], 6), expected=2, label="suboptimal greedy"),
        TestCase(input=([2], 1), expected=-1, label="coin larger than amount"),
        TestCase(input=([7], 7), expected=1, label="single coin exact match"),
        TestCase(input=([1, 2, 5], 100), expected=20, label="large amount"),
        TestCase(input=([2, 5, 10, 1], 27), expected=4, label="multiple denominations"),
        TestCase(input=([1, 2147483647], 2), expected=2, label="large coin value"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P322CoinChange)
