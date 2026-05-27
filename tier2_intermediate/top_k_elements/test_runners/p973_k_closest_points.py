from src.utils.judge_base import JudgeBase, TestCase, register


class P973KClosestPoints(JudgeBase):
    name = "973. K Closest Points to Origin"
    test_cases = [
        TestCase(
            input=([[1, 3], [-2, 2]], 1),
            expected=[[-2, 2]],
            label="example 1",
        ),
        TestCase(
            input=([[3, 3], [5, -1], [-2, 4]], 2),
            expected=[[-2, 4], [3, 3]],
            label="example 2 (sorted)",
        ),
        TestCase(input=([[0, 0]], 1), expected=[[0, 0]], label="origin itself"),
        TestCase(
            input=([[1, 0], [0, 1], [2, 0]], 2),
            expected=[[0, 1], [1, 0]],
            label="tie on distance",
        ),
        TestCase(
            input=([[-1, -1], [2, 2], [3, 3]], 1),
            expected=[[-1, -1]],
            label="negative coords",
        ),
        TestCase(
            input=([[1, 0], [0, 1], [2, 0]], 2),
            expected=[[0, 1], [1, 0]],
            label="two tied closest",
        ),
        TestCase(
            input=([[1, 1], [1, 1], [1, 1]], 2),
            expected=[[1, 1], [1, 1]],
            label="all same point",
        ),
        TestCase(
            input=([[3, 4], [0, 0], [1, 1]], 1),
            expected=[[0, 0]],
            label="origin is closest",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        points, k = tc_input
        flat = []
        for p in points:
            flat.extend(p)
        return self.serialize_multi(self.serialize_int_array(flat), self.serialize_int(k))

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        got = sorted(self.parse_int_matrix(stdout))
        exp = sorted(tc_expected)
        return got == exp


register(P973KClosestPoints)
