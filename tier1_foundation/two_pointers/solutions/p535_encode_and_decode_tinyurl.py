"""
P535: Encode and Decode TinyURL [PREMIUM] (Medium)
https://leetcode.com/problems/encode-and-decode-tinyurl/
Topics: Hash Table, String, Design, Hash Function

TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk. Design a class to encode a URL and decode a tiny URL.
There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
Implement the Solution class:
Example 1:
    Input: url = "https://leetcode.com/problems/design-tinyurl"
    Output: "https://leetcode.com/problems/design-tinyurl"

    Explanation:
    Solution obj = new Solution();
    string tiny = obj.encode(url); // returns the encoded tiny url.
    string ans = obj.decode(tiny); // returns the original url after decoding it.

Constraints:
    - 1 <= url.length <= 104
    - url is guranteed to be a valid URL.

Template (python3):
    class Codec:

        def encode(self, longUrl: str) -> str:
            '''Encodes a URL to a shortened URL.
            '''


        def decode(self, shortUrl: str) -> str:
            '''Decodes a shortened URL to its original URL.
            '''

    # Your Codec object will be instantiated and called as such:
    # codec = Codec()
    # codec.decode(codec.encode(url))
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "535. Encode and Decode TinyURL"
    test_cases = [
        TestCase(
            input="https://leetcode.com/problems/design-tinyurl",
            expected="https://leetcode.com/problems/design-tinyurl",
            label="example 1",
        ),
    ]

    def solve(self, longUrl: str) -> str:
        import hashlib

        class Codec:
            def __init__(self):
                self.url_map: dict[str, str] = {}
                self.short_map: dict[str, str] = {}

            def encode(self, longUrl: str) -> str:
                key = hashlib.md5(longUrl.encode()).hexdigest()[:6]
                self.url_map[key] = longUrl
                self.short_map[key] = longUrl
                return f"http://tinyurl.com/{key}"

            def decode(self, shortUrl: str) -> str:
                key = shortUrl.split("/")[-1]
                return self.short_map[key]

        codec = Codec()
        return codec.decode(codec.encode(longUrl))


if __name__ == "__main__":
    Solution().run()
