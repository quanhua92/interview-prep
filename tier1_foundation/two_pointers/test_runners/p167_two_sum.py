from src.utils.judge_base import JudgeBase, TestCase, register


class P167TwoSum(JudgeBase):
    name = "167. Two Sum II - Input Array Is Sorted"
    test_cases = [
        TestCase(input=([2, 7, 11, 15], 9), expected=[1, 2], label="example 1"),
        TestCase(input=([2, 3, 4], 6), expected=[1, 3], label="example 2"),
        TestCase(input=([-1, 0], -1), expected=[1, 2], label="example 3"),
        TestCase(input=([-10, -6, -4, -2], -10), expected=[2, 3], label="all negatives"),
        TestCase(input=([1, 2], 3), expected=[1, 2], label="exactly two elements"),
        TestCase(input=([-5, -3, 0, 2, 4, 6], 1), expected=[1, 6], label="negative positive cross"),
        TestCase(input=([1, 3, 4, 5, 7, 10, 11], 9), expected=[3, 4], label="middle elements"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P167TwoSum)
