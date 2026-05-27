from src.utils.judge_base import JudgeBase, TestCase, register


class P391PerfectRectangle(JudgeBase):
    name = "391. Perfect Rectangle"
    test_cases = [
        TestCase(
            input=[
                [1, 1, 3, 3],
                [3, 1, 4, 2],
                [3, 2, 4, 4],
                [1, 3, 2, 4],
                [2, 3, 3, 4],
            ],
            expected=True,
            label="example 1",
        ),
        TestCase(
            input=[[1, 1, 2, 3], [1, 3, 2, 4], [3, 1, 4, 2], [3, 2, 4, 4]],
            expected=False,
            label="example 2",
        ),
        TestCase(
            input=[[1, 1, 3, 3], [3, 1, 4, 2], [1, 3, 2, 4], [2, 2, 4, 4]],
            expected=False,
            label="example 3",
        ),
        TestCase(
            input=[[0, 0, 1, 1]],
            expected=True,
            label="single rectangle",
        ),
        TestCase(
            input=[[0, 0, 1, 2], [1, 0, 2, 2]],
            expected=True,
            label="two rects side by side",
        ),
        TestCase(
            input=[[0, 0, 2, 2], [1, 1, 3, 3]],
            expected=False,
            label="overlapping rectangles",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for rect in tc_input:
            lines.append(" ".join(str(x) for x in rect))
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P391PerfectRectangle)
