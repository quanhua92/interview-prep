from src.utils.judge_base import JudgeBase, TestCase, register


class P208ImplementTrie(JudgeBase):
    name = "208. Implement Trie (Prefix Tree)"
    test_cases = [
        TestCase(
            input=[
                ("insert", "apple"),
                ("search", "apple"),
                ("search", "app"),
                ("starts_with", "app"),
                ("insert", "app"),
                ("search", "app"),
            ],
            expected=[None, True, False, True, None, True],
            label="full sequence",
        ),
        TestCase(
            input=[
                ("insert", "a"),
                ("search", "a"),
                ("search", "b"),
                ("starts_with", "a"),
                ("starts_with", "b"),
            ],
            expected=[None, True, False, True, False],
            label="single character",
        ),
        TestCase(
            input=[
                ("insert", "hello"),
                ("search", "world"),
                ("starts_with", "world"),
                ("search", "hel"),
                ("starts_with", "hel"),
            ],
            expected=[None, False, False, False, True],
            label="search non-existent word/prefix",
        ),
        TestCase(
            input=[
                ("insert", "a"),
                ("insert", "ab"),
                ("insert", "abc"),
                ("search", "a"),
                ("search", "ab"),
                ("search", "abc"),
                ("search", "abcd"),
                ("starts_with", "ab"),
                ("starts_with", "abcd"),
            ],
            expected=[None, None, None, True, True, True, False, True, False],
            label="overlapping prefixes",
        ),
        TestCase(
            input=[
                ("insert", "test"),
                ("insert", "test"),
                ("search", "test"),
                ("starts_with", "te"),
            ],
            expected=[None, None, True, True],
            label="duplicate insert",
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


register(P208ImplementTrie)
