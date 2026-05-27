from src.utils.judge_base import JudgeBase, TestCase, register


class P352DataStreamAsDisjointIntervals(JudgeBase):
    name = "352. Data Stream as Disjoint Intervals"
    test_cases = [
        TestCase(input=[1, 3, 7, 2, 6], expected=[[1, 3], [6, 7]], label="example from problem"),
        TestCase(input=[1, 0], expected=[[0, 1]], label="adjacent values merge"),
        TestCase(input=[0], expected=[[0, 0]], label="single zero"),
        TestCase(input=[100, 1, 50], expected=[[1, 1], [50, 50], [100, 100]], label="no merges sorted output"),
        TestCase(input=[], expected=[], label="empty stream"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_matrix(stdout) == tc_expected


register(P352DataStreamAsDisjointIntervals)
