from src.utils.judge_base import JudgeBase, TestCase, register


class P380InsertDeleteGetRandom(JudgeBase):
    name = "380. Insert Delete GetRandom O(1)"
    test_cases = [
        TestCase(
            input={
                "ops": ["insert", "remove", "insert", "remove", "insert", "getRandom"],
                "args": [[1], [2], [2], [1], [2], []],
            },
            expected=[True, False, True, True, False, 2],
            label="example 1",
        ),
        TestCase(
            input={
                "ops": ["insert", "insert", "insert", "getRandom", "remove", "getRandom"],
                "args": [[10], [20], [30], [], [20], []],
            },
            expected=[True, True, True, 30, True, 10],
            label="insert multiple then remove middle",
        ),
        TestCase(
            input={
                "ops": ["insert", "getRandom", "remove", "insert", "getRandom"],
                "args": [[5], [], [5], [5], []],
            },
            expected=[True, 5, True, True, 5],
            label="single element cycle",
        ),
        TestCase(
            input={
                "ops": ["insert", "insert", "remove", "remove", "insert", "getRandom"],
                "args": [[1], [2], [1], [2], [3], []],
            },
            expected=[True, True, True, True, True, 3],
            label="remove all then insert new",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        ops = tc_input["ops"]
        args = tc_input["args"]
        lines = [str(len(ops))]
        for op in ops:
            lines.append(op)
        for arg in args:
            lines.append(" ".join(str(x) for x in arg))
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        text = stdout.strip()
        if not text:
            return False
        parts = text.split()
        result = []
        for part in parts:
            if part == "true":
                result.append(True)
            elif part == "false":
                result.append(False)
            else:
                result.append(int(part))
        return result == tc_expected


register(P380InsertDeleteGetRandom)
