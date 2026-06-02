/*
 * P535: Encode and Decode TinyURL [PREMIUM] (Medium)
 * https://leetcode.com/problems/encode-and-decode-tinyurl/
 * Topics: Hash Table, String, Design, Hash Function
 *
 * TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk. Design a class to encode a URL and decode a tiny URL.
 * There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
 * Implement the Solution class:
 * Example 1:
 *     Input: url = "https://leetcode.com/problems/design-tinyurl"
 *     Output: "https://leetcode.com/problems/design-tinyurl"
 *
 *     Explanation:
 *     Solution obj = new Solution();
 *     string tiny = obj.encode(url); // returns the encoded tiny url.
 *     string ans = obj.decode(tiny); // returns the original url after decoding it.
 *
 * Constraints:
 *     - 1 <= url.length <= 10^4
 *     - url is guranteed to be a valid URL.
 *
 * Template (python3):
 *     class Codec:
 *
 *         def encode(self, longUrl: str) -> str:
 *             '''Encodes a URL to a shortened URL.
 *             '''
 *
 *
 *         def decode(self, shortUrl: str) -> str:
 *             '''Decodes a shortened URL to its original URL.
 *             '''
 *
 *     # Your Codec object will be instantiated and called as such:
 *     # codec = Codec()
 *     # codec.decode(codec.encode(url))
 */


#include "io.h"
#include <string>
#include <unordered_map>

struct Codec {
    std::unordered_map<std::string, std::string> url_map;
    std::unordered_map<std::string, std::string> short_map;
    int next_id = 0;

    std::string encode(const std::string &longUrl) {
        abort();
    }

    std::string decode(const std::string &shortUrl) {
        abort();
    }
};

static std::string solve(const std::string &longUrl) {
    abort();
}

int main(void)
{
    std::string url = read_line();
    write_string(solve(url));
    return 0;
}
