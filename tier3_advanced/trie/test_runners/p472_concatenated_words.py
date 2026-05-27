from src.utils.judge_base import JudgeBase, TestCase, register


class P472ConcatenatedWords(JudgeBase):
    name = "472. Concatenated Words"
    test_cases = [
        TestCase(
            input=[
                "cat",
                "cats",
                "catsdogcats",
                "dog",
                "dogcatsdog",
                "hippopotamuses",
                "rat",
                "ratcatdogcat",
            ],
            expected=["catsdogcats", "dogcatsdog", "ratcatdogcat"],
            label="example 1",
        ),
        TestCase(
            input=["cat", "dog", "catdog"],
            expected=["catdog"],
            label="example 2",
        ),
        TestCase(
            input=["cat", "catcat"],
            expected=["catcat"],
            label="word from duplicate parts",
        ),
        TestCase(
            input=["a", "b", "c"],
            expected=[],
            label="no concatenated words",
        ),
        TestCase(
            input=["a", "aa", "aaaa"],
            expected=["aa", "aaaa"],
            label="deep concatenation chain",
        ),
        TestCase(
            input=["ab", "abab"],
            expected=["abab"],
            label="self-similar concatenation",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        words = tc_input
        parts = [self.serialize_int(len(words))]
        for w in words:
            parts.append(self.serialize_string(w))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if not lines:
            return len(tc_expected) == 0
        count = int(lines[0])
        got_words = lines[1:]
        return sorted(got_words) == sorted(tc_expected) and count == len(tc_expected)


register(P472ConcatenatedWords)
