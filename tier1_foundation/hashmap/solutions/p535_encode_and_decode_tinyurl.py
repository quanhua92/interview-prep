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
    - 1 <= url.length <= 10^4
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

from src.wasm_libs.py.io import *


class Codec:
    def __init__(self):
        self.code_map: dict[str, str] = {}
        self.url_map: dict[str, str] = {}
        self.chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        self.counter = 0

    def _get_base62(self, num: int) -> str:
        if num == 0:
            return self.chars[0]
        code = []
        while num > 0:
            code.append(self.chars[num % 62])
            num //= 62
        return "".join(reversed(code)).zfill(6)

    def encode(self, longUrl: str) -> str:
        if longUrl in self.url_map:
            return f"http://tinyurl.com/{self.url_map[longUrl]}"
        short_code = self._get_base62(self.counter)
        self.counter += 1
        self.code_map[short_code] = longUrl
        self.url_map[longUrl] = short_code
        return f"http://tinyurl.com/{short_code}"

    def decode(self, shortUrl: str) -> str:
        short_code = shortUrl.split("/")[-1]
        return self.code_map[short_code]


def solve(longUrl: str) -> str:
    codec = Codec()
    return codec.decode(codec.encode(longUrl))


if __name__ == "__main__":
    url = read_line()
    write_string(solve(url))
