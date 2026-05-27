from src.utils.judge_base import JudgeBase, TestCase, register


class P500KeyboardRow(JudgeBase):
    name = "500. Keyboard Row"
    test_cases = [
        TestCase(
            input=["Hello", "Alaska", "Dad", "Peace"],
            expected=["Alaska", "Dad"],
            label="example 1",
        ),
        TestCase(input=["omk"], expected=[], label="example 2"),
        TestCase(input=["adsdf", "sfd"], expected=["adsdf", "sfd"], label="example 3"),
        TestCase(input=["a", "b", "c"], expected=["a", "b", "c"], label="single letter words"),
        TestCase(input=["qz", "asdf", "qzxc"], expected=["asdf"], label="mixed row words"),
        TestCase(input=["typewriter"], expected=["typewriter"], label="entire top row word"),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for w in tc_input:
            lines.append(w)
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        text = stdout.strip()
        if not text:
            return tc_expected == []
        return text.split("\n") == tc_expected


register(P500KeyboardRow)
