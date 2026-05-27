from src.utils.judge_base import JudgeBase, TestCase, register


class P427ConstructQuadTree(JudgeBase):
    name = "427. Construct Quad Tree"
    test_cases = [
        TestCase(
            input=[[0, 1], [1, 0]],
            expected=[[0, 1], [1, 0], [1, 1], [1, 1], [1, 0]],
            label="example 2",
        ),
        TestCase(
            input=[
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 0],
                [1, 1, 1, 1, 0, 0, 0, 0],
            ],
            expected=[
                [0, 1],
                [1, 1],
                [0, 1],
                [1, 1],
                [1, 0],
                [1, 0],
                [1, 0],
                [1, 1],
                [1, 1],
            ],
            label="example 3",
        ),
        TestCase(input=[[0]], expected=[[1, 0]], label="1x1 all zeros"),
        TestCase(input=[[1]], expected=[[1, 1]], label="1x1 all ones"),
        TestCase(
            input=[[1, 1], [1, 1]],
            expected=[[1, 1]],
            label="2x2 all same (ones)",
        ),
        TestCase(
            input=[[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]],
            expected=[[1, 0]],
            label="4x4 all zeros",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_matrix(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        got_lines = []
        for line in stdout.strip().split("\n"):
            line = line.strip()
            if line == "null":
                got_lines.append(None)
            elif line:
                got_lines.append([int(x) for x in line.split()])
        while got_lines and got_lines[-1] is None:
            got_lines.pop()
        exp_lines = []
        for item in tc_expected:
            if item is None:
                exp_lines.append(None)
            else:
                exp_lines.append(list(item))
        while exp_lines and exp_lines[-1] is None:
            exp_lines.pop()
        return got_lines == exp_lines


register(P427ConstructQuadTree)
