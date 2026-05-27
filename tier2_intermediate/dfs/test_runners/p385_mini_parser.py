from src.utils.judge_base import JudgeBase, TestCase, register


class P385MiniParser(JudgeBase):
    name = "385. Mini Parser"
    test_cases = [
        TestCase(input="324", expected=324, label="example 1"),
        TestCase(
            input="[123,[456,[789]]]", expected=[123, [456, [789]]], label="example 2"
        ),
        TestCase(input="[-1]", expected=[-1], label="negative in list"),
        TestCase(input="[]", expected=[], label="empty list"),
        TestCase(input="[[]]", expected=[[]], label="nested empty list"),
        TestCase(input="[1,2,3]", expected=[1, 2, 3], label="flat list"),
        TestCase(input="-42", expected=-42, label="negative integer"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        if isinstance(tc_expected, int):
            return self.parse_int(stdout) == tc_expected
        import json

        return json.loads(stdout) == tc_expected


register(P385MiniParser)
