from src.utils.judge_base import JudgeBase, TestCase, register


class P212WordSearchII(JudgeBase):
    name = "212. Word Search II"
    test_cases = [
        TestCase(
            input=(
                [
                    ["o", "a", "a", "n"],
                    ["e", "t", "a", "e"],
                    ["i", "h", "k", "r"],
                    ["i", "f", "l", "v"],
                ],
                ["oath", "pea", "eat", "rain"],
            ),
            expected=["eat", "oath"],
            label="example 1",
        ),
        TestCase(
            input=([["a", "b"], ["c", "d"]], ["abcb"]),
            expected=[],
            label="example 2",
        ),
        TestCase(
            input=([["a"]], ["a"]),
            expected=["a"],
            label="1x1 board single char",
        ),
        TestCase(
            input=([["a", "b"], ["c", "d"]], ["xyz"]),
            expected=[],
            label="word not on board",
        ),
        TestCase(
            input=([["a", "a"], ["a", "a"]], ["aaaa"]),
            expected=["aaaa"],
            label="same letter grid",
        ),
        TestCase(
            input=(
                [
                    ["o", "a", "a", "n"],
                    ["e", "t", "a", "e"],
                    ["i", "h", "k", "r"],
                    ["i", "f", "l", "v"],
                ],
                ["oath", "oat"],
            ),
            expected=["oat", "oath"],
            label="prefix is also a word",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        board, words = tc_input
        rows = len(board)
        cols = len(board[0]) if board else 0
        parts = [self.serialize_int(rows), self.serialize_int(cols)]
        for row in board:
            parts.append(self.serialize_string("".join(row)))
        parts.append(self.serialize_int(len(words)))
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


register(P212WordSearchII)
