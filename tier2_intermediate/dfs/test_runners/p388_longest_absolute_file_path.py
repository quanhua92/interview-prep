from src.utils.judge_base import JudgeBase, TestCase, register


class P388LongestAbsoluteFilePath(JudgeBase):
    name = "388. Longest Absolute File Path"
    test_cases = [
        TestCase(
            input="dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext",
            expected=20,
            label="example 1",
        ),
        TestCase(
            input="dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext",
            expected=32,
            label="example 2",
        ),
        TestCase(input="a", expected=0, label="single directory"),
        TestCase(input="file.txt", expected=8, label="file at root level"),
        TestCase(
            input="dir\n\tsubdir\n\t\tfile.name.ext",
            expected=24,
            label="file with multiple dots",
        ),
        TestCase(
            input="dir\n\tsubdir1\n\tsubdir2",
            expected=0,
            label="no files only dirs",
        ),
        TestCase(input="a\n\tb.txt", expected=7, label="single level nesting"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected


register(P388LongestAbsoluteFilePath)
