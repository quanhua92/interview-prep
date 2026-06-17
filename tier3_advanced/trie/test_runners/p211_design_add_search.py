from src.utils.judge_base import JudgeBase, TestCase, register


class P211DesignAddSearch(JudgeBase):
    name = "211. Design Add and Search Words Data Structure"
    test_cases = [
        TestCase(
            input=[
                ("add_word", "bad"), ("add_word", "dad"), ("add_word", "mad"),
                ("search", "pad"), ("search", "bad"), ("search", ".ad"), ("search", "b.."),
            ],
            expected=[None, None, None, False, True, True, True],
            label="example 1",
        ),
        TestCase(
            input=[("add_word", "a"), ("add_word", "ab"), ("search", "a"), ("search", ".a"), ("search", "ab")],
            expected=[None, None, True, False, True],
            label="example 2",
        ),
        TestCase(
            input=[("add_word", "abc"), ("search", "..."), ("search", "..")],
            expected=[None, True, False],
            label="all dots pattern",
        ),
        TestCase(
            input=[("add_word", "a"), ("add_word", "b"), ("search", ".")],
            expected=[None, None, True],
            label="single char dot matches multiple",
        ),
        TestCase(
            input=[("add_word", "abc"), ("add_word", "xbc"), ("search", ".bc")],
            expected=[None, None, True],
            label="dot at beginning",
        ),
        TestCase(
            input=[("add_word", "abc"), ("search", "a.c"), ("search", "a..")],
            expected=[None, True, True],
            label="dot in middle and at end",
        ),
        TestCase(
            input=[
                ("add_word", "a"), ("search", "a"), ("search", "."),
                ("add_word", "ab"), ("search", "ab"), ("search", "a."), ("search", "."),
            ],
            expected=[None, True, True, None, True, True, True],
            label="interleaved add and search",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        parts = [self.serialize_int(len(tc_input))]
        for op, val in tc_input:
            parts.append(self.serialize_multi(self.serialize_string(op), self.serialize_string(val)))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = stdout.strip().split("\n")
        if len(lines) != len(tc_expected):
            return False
        for got, exp in zip(lines, tc_expected):
            if exp is None:
                if got.strip() != "null":
                    return False
            else:
                if got.strip().lower() != str(exp).lower():
                    return False
        return True


register(P211DesignAddSearch)
