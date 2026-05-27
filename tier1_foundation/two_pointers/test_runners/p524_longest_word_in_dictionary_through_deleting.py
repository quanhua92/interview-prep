from src.utils.judge_base import JudgeBase, TestCase, register


class P524LongestWordDictDeleting(JudgeBase):
    name = "524. Longest Word in Dictionary through Deleting"
    test_cases = [
        TestCase(
            input=("abpcplea", ["ale", "apple", "monkey", "plea"]),
            expected="apple",
            label="example 1",
        ),
        TestCase(input=("abpcplea", ["a", "b", "c"]), expected="a", label="example 2"),
        TestCase(input=("abpcplea", []), expected="", label="empty dictionary"),
        TestCase(input=("abc", ["xyz", "def"]), expected="", label="no match"),
        TestCase(
            input=("abpcplea", ["apple", "ale", "abpple"]),
            expected="abpple",
            label="same length lexicographical tie",
        ),
        TestCase(input=("a", ["a", "aa", "aaa"]), expected="a", label="longer dict words than s"),
    ]

    def to_stdin(self, tc_input) -> str:
        s, dictionary = tc_input
        parts = [self.serialize_string(s), self.serialize_int(len(dictionary))]
        for word in dictionary:
            parts.append(self.serialize_string(word))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_string(stdout) == tc_expected


register(P524LongestWordDictDeleting)
