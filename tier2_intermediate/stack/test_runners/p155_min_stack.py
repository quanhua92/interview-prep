from src.utils.judge_base import JudgeBase, TestCase, register


class P155MinStack(JudgeBase):
    name = "155. Min Stack"
    test_cases = [
        TestCase(
            input=(
                ["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"],
                [[], [5], [-2], [3], [], [], [], []],
            ),
            expected=[None, None, None, None, -2, None, -2, -2],
            label="example 1",
        ),
        TestCase(
            input=(
                [
                    "MinStack",
                    "push",
                    "push",
                    "getMin",
                    "getMin",
                    "push",
                    "getMin",
                    "top",
                    "getMin",
                    "pop",
                    "getMin",
                ],
                [[], [0], [1], [], [], [-3], [], [], [], [], []],
            ),
            expected=[None, None, None, 0, 0, None, -3, -3, -3, None, 0],
            label="negative values",
        ),
        TestCase(
            input=(
                ["MinStack", "push", "getMin", "top", "pop", "push", "getMin"],
                [[], [42], [], [], [], [7], []],
            ),
            expected=[None, None, 42, 42, None, None, 7],
            label="single push then replace",
        ),
        TestCase(
            input=(
                [
                    "MinStack",
                    "push",
                    "push",
                    "push",
                    "push",
                    "pop",
                    "getMin",
                    "pop",
                    "getMin",
                    "pop",
                    "getMin",
                ],
                [[], [2], [1], [3], [1], [], [], [], [], [], []],
            ),
            expected=[None, None, None, None, None, None, 1, None, 1, None, 2],
            label="duplicate min values",
        ),
        TestCase(
            input=(
                ["MinStack", "push", "push", "getMin", "pop", "getMin"],
                [[], [-2147483648], [2147483647], [], [], []],
            ),
            expected=[None, None, None, -2147483648, None, -2147483648],
            label="INT boundary values",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        ops, values = tc_input
        parts = [self.serialize_int(len(ops))]
        for op, val in zip(ops, values):
            parts.append(self.serialize_string(op))
            parts.append(self.serialize_int(len(val)))
            if val:
                parts.append(self.serialize_int_array(val))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if len(lines) != len(tc_expected):
            return False
        for line, exp in zip(lines, tc_expected):
            if exp is None:
                if line != "null":
                    return False
            else:
                try:
                    if int(line) != exp:
                        return False
                except ValueError:
                    return False
        return True


register(P155MinStack)
