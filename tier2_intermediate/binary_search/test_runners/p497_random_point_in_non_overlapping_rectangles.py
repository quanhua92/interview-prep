from src.utils.judge_base import JudgeBase, TestCase, register


class P497RandomPointInNonOverlappingRectangles(JudgeBase):
    name = "497. Random Point in Non-overlapping Rectangles"
    test_cases = [
        TestCase(input=[[-2, -2, 1, 1], [2, 2, 4, 6]], expected=[16, 31], label="area sum for two rectangles"),
        TestCase(input=[[0, 0, 2, 2]], expected=[9], label="area for single 3x3 rectangle"),
        TestCase(input=[[0, 0, 0, 0]], expected=[1], label="single point rectangle"),
        TestCase(input=[[-5, -5, -3, -3], [1, 1, 3, 3]], expected=[9, 18], label="negative and positive rects same size"),
        TestCase(input=[[1, 1, 2, 2], [3, 3, 5, 5]], expected=[4, 13], label="different sized rects"),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for row in tc_input:
            lines.append(" ".join(str(x) for x in row))
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected


register(P497RandomPointInNonOverlappingRectangles)
