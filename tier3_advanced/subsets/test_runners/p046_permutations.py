from src.utils.judge_base import JudgeBase, TestCase, register


class P046Permutations(JudgeBase):
    name = "46. Permutations"
    test_cases = [
        TestCase(
            input=[1, 2, 3],
            expected=[
                [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1],
            ],
            label="example 1",
        ),
        TestCase(
            input=[0, 1],
            expected=[[0, 1], [1, 0]],
            label="example 2",
        ),
        TestCase(
            input=[1],
            expected=[[1]],
            label="single element",
        ),
        TestCase(
            input=[-1, 0, 1],
            expected=[
                [-1, 0, 1], [-1, 1, 0], [0, -1, 1], [0, 1, -1], [1, -1, 0], [1, 0, -1],
            ],
            label="negative and zero mix",
        ),
        TestCase(
            input=[-3, -1],
            expected=[[-3, -1], [-1, -3]],
            label="two negative elements",
        ),
        TestCase(
            input=[1, 2, 3, 4],
            expected=[
                [1, 2, 3, 4], [1, 2, 4, 3], [1, 3, 2, 4], [1, 3, 4, 2], [1, 4, 2, 3], [1, 4, 3, 2],
                [2, 1, 3, 4], [2, 1, 4, 3], [2, 3, 1, 4], [2, 3, 4, 1], [2, 4, 1, 3], [2, 4, 3, 1],
                [3, 1, 2, 4], [3, 1, 4, 2], [3, 2, 1, 4], [3, 2, 4, 1], [3, 4, 1, 2], [3, 4, 2, 1],
                [4, 1, 2, 3], [4, 1, 3, 2], [4, 2, 1, 3], [4, 2, 3, 1], [4, 3, 1, 2], [4, 3, 2, 1],
            ],
            label="four elements",
        ),
        TestCase(
            input=[-5],
            expected=[[-5]],
            label="single negative element",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        if not lines and not tc_expected:
            return True
        got = sorted([list(map(int, line.split())) for line in lines])
        exp = sorted([list(t) for t in tc_expected])
        return got == exp


register(P046Permutations)
