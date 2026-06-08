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

use wasm_libs::*;
use std::collections::HashMap;

struct Codec {
    code_map: HashMap<String, String>,
    url_map: HashMap<String, String>,
    counter: i32,
}

impl Codec {
    fn new() -> Self {
        Codec {
            code_map: HashMap::new(),
            url_map: HashMap::new(),
            counter: 0,
        }
    }

    fn get_base62(&self, mut num: i32) -> String {
        let chars: Vec<char> = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".chars().collect();
        if num == 0 {
            return chars[0].to_string().repeat(6);
        }
        let mut code: Vec<char> = Vec::new();
        while num > 0 {
            code.push(chars[(num % 62) as usize]);
            num /= 62;
        }
        code.reverse();
        let mut result: String = String::new();
        for _ in 0..(6 - code.len()) {
            result.push(chars[0]);
        }
        for c in code {
            result.push(c);
        }
        result
    }

    fn encode(&mut self, long_url: &str) -> String {
        if let Some(code) = self.url_map.get(long_url) {
            return format!("http://tinyurl.com/{}", code);
        }
        let code = self.get_base62(self.counter);
        self.counter += 1;
        self.code_map.insert(code.clone(), long_url.to_string());
        self.url_map.insert(long_url.to_string(), code.clone());
        format!("http://tinyurl.com/{}", code)
    }

    fn decode(&self, short_url: &str) -> String {
        let code = short_url.rsplit('/').next().unwrap();
        self.code_map.get(code).cloned().unwrap_or_default()
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
