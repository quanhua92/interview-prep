from src.utils.judge_base import JudgeBase, TestCase, register


class P323ConnectedComponents(JudgeBase):
    name = "323. Number of Connected Components in an Undirected Graph"
    test_cases = [
        TestCase(input=(5, [[0, 1], [1, 2], [3, 4]]), expected=2, label="example"),
        TestCase(
            input=(5, [[0, 1], [1, 2], [2, 3], [3, 4]]),
            expected=1,
            label="fully connected",
        ),
        TestCase(input=(3, []), expected=3, label="no edges"),
        TestCase(input=(1, []), expected=1, label="single node no edges"),
        TestCase(input=(4, [[0, 1], [2, 3]]), expected=2, label="two disjoint pairs"),
        TestCase(
            input=(6, [[0, 1], [1, 2], [2, 0], [3, 4], [4, 5], [5, 3]]),
            expected=2,
            label="two triangles",
        ),
        TestCase(
            input=(7, [[0, 1], [1, 2], [3, 4], [5, 6]]),
            expected=3,
            label="three components with chain and pairs",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        n, edges = tc_input
        lines = [str(n), str(len(edges))]
        for u, v in edges:
            lines.append(f"{u} {v}")
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P323ConnectedComponents)
