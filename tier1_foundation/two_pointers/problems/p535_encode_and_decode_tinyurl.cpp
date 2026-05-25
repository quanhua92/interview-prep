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
 *     - 1 <= url.length <= 104
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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>

struct Codec {
    std::unordered_map<std::string, std::string> url_map;
    std::unordered_map<std::string, std::string> short_map;
    int next_id = 0;

    std::string encode(const std::string &longUrl) {
        /* TODO: Implement */
        return {};
    }

    std::string decode(const std::string &shortUrl) {
        size_t pos = shortUrl.rfind('/');
        std::string key = shortUrl.substr(pos + 1);
        return short_map[key];
    }
};

static std::string solve(const std::string &longUrl) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    int passed = 0, total = 4;
    printf("\n============================================================\n");
    printf("  535. Encode and Decode TinyURL\n");
    printf("============================================================\n");

    {
        std::string got = solve("https://leetcode.com/problems/design-tinyurl");
        if (got == "https://leetcode.com/problems/design-tinyurl") { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: https://leetcode.com/problems/design-tinyurl, Got: %s\n", got.c_str()); }
    }
    {
        std::string got = solve("https://example.com/path/to/resource?query=1&param=2#section");
        if (got == "https://example.com/path/to/resource?query=1&param=2#section") { passed++; printf("  Test 2 (URL with query and fragment): PASS\n"); }
        else { printf("  Test 2 (URL with query and fragment): FAIL\n  Expected: https://example.com/path/to/resource?query=1&param=2#section, Got: %s\n", got.c_str()); }
    }
    {
        std::string got = solve("http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u");
        if (got == "http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u") { passed++; printf("  Test 3 (URL with many path segments): PASS\n"); }
        else { printf("  Test 3 (URL with many path segments): FAIL\n  Expected: http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u, Got: %s\n", got.c_str()); }
    }
    {
        std::string got = solve("https://site.com");
        if (got == "https://site.com") { passed++; printf("  Test 4 (minimal URL): PASS\n"); }
        else { printf("  Test 4 (minimal URL): FAIL\n  Expected: https://site.com, Got: %s\n", got.c_str()); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
