from src.utils.judge_base import JudgeBase, TestCase, register


class P567PermutationInString(JudgeBase):
    name = "567. Permutation in String"
    test_cases = [
        TestCase(input=("ab", "eidbaooo"), expected=True, label="example 1"),
        TestCase(input=("ab", "eidboaoo"), expected=False, label="example 2"),
        TestCase(input=("a", "a"), expected=True, label="single char match"),
        TestCase(input=("adc", "dcda"), expected=True, label="permutation at end"),
        TestCase(input=("abc", "ccccbbbbaaaa"), expected=False, label="no match large string"),
        TestCase(input=("ab", "a"), expected=False, label="s1 longer than s2"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_string(tc_input[0]),
            self.serialize_string(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P567PermutationInString)
