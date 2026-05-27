from src.utils.judge_base import JudgeBase, TestCase, register


class P535EncodeAndDecodeTinyURL(JudgeBase):
    name = "535. Encode and Decode TinyURL"
    test_cases = [
        TestCase(
            input="https://leetcode.com/problems/design-tinyurl",
            expected="https://leetcode.com/problems/design-tinyurl",
            label="example 1",
        ),
        TestCase(
            input="https://example.com/path/to/resource?query=1&param=2#section",
            expected="https://example.com/path/to/resource?query=1&param=2#section",
            label="URL with query and fragment",
        ),
        TestCase(
            input="http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u",
            expected="http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u",
            label="URL with many path segments",
        ),
        TestCase(
            input="https://site.com",
            expected="https://site.com",
            label="minimal URL",
        ),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_string(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_string(stdout) == tc_expected


register(P535EncodeAndDecodeTinyURL)
