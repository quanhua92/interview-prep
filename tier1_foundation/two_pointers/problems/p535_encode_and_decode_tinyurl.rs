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
use std::collections::HashMap;

struct Codec {
    url_map: HashMap<String, String>,
    short_map: HashMap<String, String>,
    next_id: i32,
}

impl Codec {
    fn new() -> Self {
        todo!()
    }

    fn encode(&mut self, long_url: &str) -> String {
        todo!()
    }

    fn decode(&self, short_url: &str) -> String {
        let key = short_url.rsplit('/').next().unwrap();
        self.short_map.get(key).cloned().unwrap_or_default()
    }
}

fn solve(long_url: &str) -> String {
    todo!()
}

fn main() {
    let mut passed = 0;
    let total = 4;
    println!("\n============================================================");
    println!("  535. Encode and Decode TinyURL");
    println!("============================================================");

    {
        let got = solve("https://leetcode.com/problems/design-tinyurl");
        if got == "https://leetcode.com/problems/design-tinyurl" { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n  Expected: https://leetcode.com/problems/design-tinyurl, Got: {}", got); }
    }
    {
        let got = solve("https://example.com/path/to/resource?query=1&param=2#section");
        if got == "https://example.com/path/to/resource?query=1&param=2#section" { passed += 1; println!("  Test 2 (URL with query and fragment): PASS"); }
        else { println!("  Test 2 (URL with query and fragment): FAIL\n  Expected: https://example.com/path/to/resource?query=1&param=2#section, Got: {}", got); }
    }
    {
        let got = solve("http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u");
        if got == "http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u" { passed += 1; println!("  Test 3 (URL with many path segments): PASS"); }
        else { println!("  Test 3 (URL with many path segments): FAIL\n  Expected: http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u, Got: {}", got); }
    }
    {
        let got = solve("https://site.com");
        if got == "https://site.com" { passed += 1; println!("  Test 4 (minimal URL): PASS"); }
        else { println!("  Test 4 (minimal URL): FAIL\n  Expected: https://site.com, Got: {}", got); }
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
