from src.utils.judge_base import JudgeBase, TestCase, register


class P211DesignAddSearch(JudgeBase):
    name = "211. Design Add and Search Words Data Structure"
    test_cases = [
        TestCase(
            input=(["bad", "dad", "mad"], ["pad", "bad", ".ad", "b.."]),
            expected=[False, True, True, True],
            label="example 1",
        ),
        TestCase(
            input=(["a", "ab"], ["a", ".a", "ab"]),
            expected=[True, False, True],
            label="example 2",
        ),
        TestCase(
            input=(["abc"], ["...", ".."]),
            expected=[True, False],
            label="all dots pattern",
        ),
        TestCase(
            input=(["a", "b"], ["."]),
            expected=[True],
            label="single char dot matches multiple",
        ),
        TestCase(
            input=(["abc", "xbc"], [".bc"]),
            expected=[True],
            label="dot at beginning",
        ),
        TestCase(
            input=(["abc"], ["a.c", "a.."]),
            expected=[True, True],
            label="dot in middle and at end",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        words, searches = tc_input
        parts = [
            self.serialize_int(len(words)),
        ]
        for w in words:
            parts.append(self.serialize_string(w))
        parts.append(self.serialize_int(len(searches)))
        for s in searches:
            parts.append(self.serialize_string(s))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = stdout.strip().split("\n")
        if len(lines) != len(tc_expected):
            return False
        for got, exp in zip(lines, tc_expected):
            if got.strip().lower() != str(exp).lower():
                return False
        return True


register(P211DesignAddSearch)
