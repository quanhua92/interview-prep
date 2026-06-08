/**
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
 */

import { readLine, writeString } from '../../wasm_libs/js/io.mjs';

const BASE62_CHARS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

class Codec {
  constructor() {
    this.codeMap = new Map();
    this.urlMap = new Map();
    this.counter = 0;
  }

  _getBase62(num) {
    if (num === 0) return BASE62_CHARS[0].repeat(6);
    let code = "";
    let n = num;
    while (n > 0) {
      code += BASE62_CHARS[n % 62];
      n = Math.floor(n / 62);
    }
    code = code.split("").reverse().join("");
    return BASE62_CHARS[0].repeat(6 - code.length) + code;
  }

  encode(longUrl) {
    if (this.urlMap.has(longUrl)) {
      return `http://tinyurl.com/${this.urlMap.get(longUrl)}`;
    }
    const code = this._getBase62(this.counter++);
    this.codeMap.set(code, longUrl);
    this.urlMap.set(longUrl, code);
    return `http://tinyurl.com/${code}`;
  }

  decode(shortUrl) {
    const code = shortUrl.split("/").pop();
    return this.codeMap.get(code);
  }
}

function solve(longUrl) {
  const codec = new Codec();
  return codec.decode(codec.encode(longUrl));
}

const url = readLine();
writeString(solve(url));
