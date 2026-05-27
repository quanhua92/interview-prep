from src.utils.judge_base import JudgeBase, TestCase, register


class P023MergeKSortedLists(JudgeBase):
    name = "23. Merge k Sorted Lists"
    test_cases = [
        TestCase(
            input=[[1, 4, 5], [1, 3, 4], [2, 6]],
            expected=[1, 1, 2, 3, 4, 4, 5, 6],
            label="example 1",
        ),
        TestCase(input=[], expected=[], label="empty input"),
        TestCase(input=[[]], expected=[], label="single empty list"),
        TestCase(input=[[1, 2, 3]], expected=[1, 2, 3], label="single list"),
        TestCase(
            input=[[1, 1], [1, 1], [1, 1]],
            expected=[1, 1, 1, 1, 1, 1],
            label="all same values",
        ),
        TestCase(
            input=[[-5, -3], [-4, -2], [-6, 0]],
            expected=[-6, -5, -4, -3, -2, 0],
            label="negative values",
        ),
        TestCase(input=[[1, 3], [2, 4]], expected=[1, 2, 3, 4], label="two lists"),
        TestCase(
            input=[[], [], [1], [], [2]],
            expected=[1, 2],
            label="mixed empty and non-empty",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        parts = [self.serialize_int(len(tc_input))]
        for lst in tc_input:
            parts.append(self.serialize_int_array(lst))
        return "".join(parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P023MergeKSortedLists)
