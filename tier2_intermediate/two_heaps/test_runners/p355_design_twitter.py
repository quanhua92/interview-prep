from src.utils.judge_base import JudgeBase, TestCase, register


class P355DesignTwitter(JudgeBase):
    name = "355. Design Twitter"
    test_cases = [
        TestCase(
            input=(
                [
                    ("postTweet", [1, 5]),
                    ("getNewsFeed", [1]),
                    ("follow", [1, 2]),
                    ("postTweet", [2, 6]),
                    ("getNewsFeed", [1]),
                    ("unfollow", [1, 2]),
                    ("getNewsFeed", [1]),
                ],
                [[5], [6, 5], [5]],
            ),
            expected=[[5], [6, 5], [5]],
            label="example 1",
        ),
        TestCase(
            input=(
                [
                    ("postTweet", [1, 10]),
                    ("postTweet", [1, 20]),
                    ("postTweet", [2, 30]),
                    ("follow", [1, 2]),
                    ("getNewsFeed", [1]),
                ],
                [[20, 10, 30]],
            ),
            expected=[[30, 20, 10]],
            label="multiple tweets merge feed",
        ),
        TestCase(
            input=(
                [
                    ("postTweet", [1, 1]),
                    ("getNewsFeed", [1]),
                ],
                [[1]],
            ),
            expected=[[1]],
            label="single user single tweet",
        ),
        TestCase(
            input=(
                [
                    ("follow", [1, 2]),
                    ("getNewsFeed", [1]),
                ],
                [[]],
            ),
            expected=[[]],
            label="follow with no tweets",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        ops, _feeds = tc_input
        parts = [self.serialize_int(len(ops))]
        for op_name, args in ops:
            parts.append(self.serialize_string(op_name))
            parts.append(self.serialize_int(len(args)))
            for a in args:
                parts.append(self.serialize_int(a))
        return self.serialize_multi(*parts)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        text = stdout.strip()
        if not text:
            return all(len(exp) == 0 for exp in tc_expected)
        lines = [line.strip() for line in text.split("\n") if line.strip()]
        if len(lines) != len(tc_expected):
            return False
        for line, exp in zip(lines, tc_expected):
            if not line:
                got = []
            else:
                got = list(map(int, line.split()))
            if got != exp:
                return False
        return True


register(P355DesignTwitter)
