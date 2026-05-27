from src.utils.judge_base import JudgeBase, TestCase, register


class P141LinkedListCycle(JudgeBase):
    name = "141. Linked List Cycle"
    test_cases = [
        TestCase(input=([3, 2, 0, -4], 1), expected=True, label="example 1"),
        TestCase(input=([1, 2], 0), expected=True, label="example 2"),
        TestCase(input=([1], -1), expected=False, label="example 3"),
        TestCase(input=([], -1), expected=False, label="empty list"),
        TestCase(input=([1, 2], -1), expected=False, label="two nodes no cycle"),
        TestCase(input=([1, 2, 3], 2), expected=True, label="self-loop at tail"),
        TestCase(input=([1, 2, 3, 4, 5], -1), expected=False, label="long list no cycle"),
        TestCase(input=([1, 2, 3], 0), expected=True, label="cycle back to head"),
    ]

    def to_stdin(self, tc_input) -> str:
        vals, pos = tc_input
        return self.serialize_multi(
            self.serialize_int_array(vals),
            self.serialize_int(pos),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P141LinkedListCycle)
