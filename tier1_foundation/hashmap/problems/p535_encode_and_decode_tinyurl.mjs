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
import { createHash } from "node:crypto";

class Codec
  constructor()
    this.urlMap = new Map();
    this.shortMap = new Map();
  }

  encode(longUrl)
    const key = createHash("md5").update(longUrl).digest("hex").slice(0, 6);
    this.urlMap.set(key, longUrl);
    this.shortMap.set(key, longUrl);
    return `http://tinyurl.com/${key}`;
  }

  decode(shortUrl)
    const key = shortUrl.split("/").pop();
    return this.shortMap.get(key);
  } {
    throw new Error("NotImplementedError");
}

function solve(longUrl)
  const codec = new Codec();
  return codec.decode(codec.encode(longUrl)); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: "https://leetcode.com/problems/design-tinyurl", expected: "https://leetcode.com/problems/design-tinyurl" },
  { label: "URL with query and fragment", input: "https://example.com/path/to/resource?query=1&param=2#section", expected: "https://example.com/path/to/resource?query=1&param=2#section" },
  { label: "URL with many path segments", input: "http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u", expected: "http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u" },
  { label: "minimal URL", input: "https://site.com", expected: "https://site.com" },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
