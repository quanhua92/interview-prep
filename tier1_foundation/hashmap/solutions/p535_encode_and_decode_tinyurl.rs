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

use wasm_libs::*;
use std::collections::HashMap;

struct Codec {
    url_map: HashMap<String, String>,
    short_map: HashMap<String, String>,
    next_id: i32,
}

impl Codec {
    fn new() -> Self {
        Codec {
            url_map: HashMap::new(),
            short_map: HashMap::new(),
            next_id: 0,
        }
    }

    fn encode(&mut self, long_url: &str) -> String {
        let key = self.next_id.to_string();
        self.next_id += 1;
        self.url_map.insert(key.clone(), long_url.to_string());
        self.short_map.insert(key.clone(), long_url.to_string());
        format!("http://tinyurl.com/{}", key)
    }

    fn decode(&self, short_url: &str) -> String {
        let key = short_url.rsplit('/').next().unwrap();
        self.short_map.get(key).cloned().unwrap_or_default()
    }
}

fn solve(long_url: &str) -> String {
    let mut codec = Codec::new();
    let tiny = codec.encode(long_url);
    codec.decode(&tiny)
}

fn main() {
    let url = read_line();
    write_string(&solve(&url));
    std::process::exit(0);
}
