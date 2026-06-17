from src.utils.judge_base import JudgeBase, TestCase, register


class P352DataStreamAsDisjointIntervals(JudgeBase):
    name = "352. Data Stream as Disjoint Intervals"
    test_cases = [
        TestCase(
            input=(
                ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals",
                 "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"],
                [[], [1], [], [3], [], [7], [], [2], [], [6], []],
            ),
            expected=[[[1, 1]], [[1, 1], [3, 3]], [[1, 1], [3, 3], [7, 7]], [[1, 3], [7, 7]], [[1, 3], [6, 7]]],
            label="example from problem with interleaved getIntervals",
        ),
        TestCase(
            input=(
                ["SummaryRanges", "addNum", "addNum", "getIntervals", "addNum", "getIntervals"],
                [[], [1], [0], [], [2], []],
            ),
            expected=[[[0, 1]], [[0, 2]]],
            label="adjacent values merge",
        ),
        TestCase(
            input=(["SummaryRanges", "addNum", "getIntervals"], [[], [0], []]),
            expected=[[[0, 0]]],
            label="single zero",
        ),
        TestCase(
            input=(
                ["SummaryRanges", "addNum", "addNum", "addNum", "getIntervals"],
                [[], [100], [1], [50], []],
            ),
            expected=[[[1, 1], [50, 50], [100, 100]]],
            label="no merges sorted output",
        ),
        TestCase(
            input=(
                ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals"],
                [[], [5], [], [5], []],
            ),
            expected=[[[5, 5]], [[5, 5]]],
            label="duplicate addNum ignored",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        ops, values = tc_input
        parts = [self.serialize_int(len(ops))]
        for op, val in zip(ops, values):
            parts.append(self.serialize_string(op))
            parts.append(self.serialize_int(len(val)))
            if val:
                parts.append(self.serialize_int_array(val))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [line.strip() for line in stdout.strip().split("\n") if line.strip()]
        idx = 0
        for exp_matrix in tc_expected:
            if idx >= len(lines):
                return False
            try:
                k = int(lines[idx])
            except ValueError:
                return False
            idx += 1
            if idx + k > len(lines):
                return False
            got = []
            for _ in range(k):
                parts = lines[idx].split()
                idx += 1
                if len(parts) != 2:
                    return False
                got.append([int(parts[0]), int(parts[1])])
            if got != exp_matrix:
                return False
        return idx == len(lines)


register(P352DataStreamAsDisjointIntervals)
