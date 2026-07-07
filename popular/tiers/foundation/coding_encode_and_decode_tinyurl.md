# Encode and Decode TinyURL

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 535, Glassdoor

---

## Question Description

TinyURL is a URL shortening service where you enter a URL such as `https://leetcode.com/problems/design-tinyurl` and it returns a short URL such as `http://tinyurl.com/4e9iAk`. Design a class to encode a URL and decode a tiny URL.

There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.

Implement the `Solution` class:

*   `Solution()` Initializes the object.
*   `string encode(string longUrl)` Returns a tiny URL for the given `longUrl`.
*   `string decode(string shortUrl)` Returns the original long URL for the given `shortUrl`.

### Examples

*   **Input**: `url = "https://leetcode.com/problems/design-tinyurl"`
    *   **Output**: `"https://leetcode.com/problems/design-tinyurl"`
    *   **Explanation**:
        ```cpp
        Solution solution;
        string tiny = solution.encode("https://leetcode.com/problems/design-tinyurl"); 
        // returns "http://tinyurl.com/000000" (or similar short code)
        string original = solution.decode(tiny); 
        // returns "https://leetcode.com/problems/design-tinyurl"
        ```

---

## Detailed Solution (C++)

For the single-machine coding version, we can map URLs using an incremental counter:
1.  Use a counter that increments for each unique long URL encoded.
2.  Convert the counter value to a **Base-62** string (characters `0-9`, `a-z`, `A-Z`) to represent the short code. A 6-character Base-62 string supports $62^6 \approx 56.8$ billion unique URLs.
3.  Store the mapping `shortCode -> longUrl` and `longUrl -> shortCode` in two hash maps (`std::unordered_map`) to ensure both encoding and decoding run in $\mathcal{O}(1)$ average time.

### Standard C++ Production Code

```cpp
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution {
private:
    std::unordered_map<std::string, std::string> code_map;
    std::unordered_map<std::string, std::string> url_map;
    int counter = 0;
    
    // Self-contained character set for Base-62 conversion
    const std::string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string get_base62(int num) {
        if (num == 0) {
            return std::string(6, chars[0]);
        }
        std::string code = "";
        while (num > 0) {
            code += chars[num % 62];
            num /= 62;
        }
        std::reverse(code.begin(), code.end());
        // Left-pad with '0' to ensure fixed 6-character length
        if (code.size() < 6) {
            code = std::string(6 - code.size(), chars[0]) + code;
        }
        return code;
    }

public:
    // Encodes a URL to a shortened URL.
    std::string encode(const std::string& longUrl) {
        if (url_map.find(longUrl) != url_map.end()) {
            return "http://tinyurl.com/" + url_map[longUrl];
        }
        
        std::string code = get_base62(counter++);
        code_map[code] = longUrl;
        url_map[longUrl] = code;
        
        return "http://tinyurl.com/" + code;
    }

    // Decodes a shortened URL to its original URL.
    std::string decode(const std::string& shortUrl) {
        size_t last_slash = shortUrl.rfind('/');
        if (last_slash == std::string::npos) {
            return "";
        }
        std::string code = shortUrl.substr(last_slash + 1);
        return code_map.count(code) ? code_map[code] : "";
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
class Codec:
    def __init__(self):
        """
        Initializes the maps and character library for Base-62.
        """
        self.code_map: dict[str, str] = {}
        self.url_map: dict[str, str] = {}
        self.chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        self.counter = 0

    def _get_base62(self, num: int) -> str:
        """
        Helper method to encode an integer into a 6-character Base-62 string.
        """
        if num == 0:
            return self.chars[0].zfill(6)
        
        code = []
        while num > 0:
            code.append(self.chars[num % 62])
            num //= 62
            
        # Join reversed characters and left-pad with '0' to length 6
        return "".join(reversed(code)).zfill(6)

    def encode(self, longUrl: str) -> str:
        """
        Encodes a URL to a shortened URL.
        """
        if longUrl in self.url_map:
            return f"http://tinyurl.com/{self.url_map[longUrl]}"
            
        short_code = self._get_base62(self.counter)
        self.counter += 1
        
        self.code_map[short_code] = longUrl
        self.url_map[longUrl] = short_code
        
        return f"http://tinyurl.com/{short_code}"

    def decode(self, shortUrl: str) -> str:
        """
        Decodes a shortened URL to its original URL.
        """
        # Split by '/' and take the last part representing the unique code
        short_code = shortUrl.split("/")[-1]
        return self.code_map.get(short_code, "")
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Precision and zfill
*   Python handles arbitrarily large integers natively, meaning our `counter` will never overflow a standard data type, unlike standard fixed-width 32-bit integers in C++.
*   `str.zfill(width)` is a convenient built-in Python string method that left-pads a numeric string with ASCII `'0'` characters to reach the target width.

### 2. URL Parsing Security
*   Using `shortUrl.split("/")[-1]` is quick but vulnerable if the short URL contains trailing query parameters or fragments (e.g., `http://tinyurl.com/000000?ref=newsletter`).
*   In production Python code, use `urllib.parse.urlparse` to safely extract only the path segment of the URL.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(1)$ | Dictionary lookups and insertions run in constant time. Base-62 conversion takes constant time since key length is bounded. |
| **Space Complexity** | $\mathcal{O}(N)$ | We store the mappings for all $N$ unique long URLs encoded. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do you scale this service to handle billions of requests across a distributed system?
*   **Answer**: In a distributed system:
    1.  **Centralized ID Generation**: A single counter would cause thread contention and single-point-of-failure bottlenecks. Instead, use a distributed ID generator (e.g., **Twitter Snowflake** or a **ZooKeeper** coordinate server) to allocate ranges of IDs to each application server.
    2.  **Consistent Hashing**: Distribute the URL database across multiple database shards using consistent hashing.

### Q2: How can you optimize this service for high read throughput?
*   **Answer**: URL redirection is highly read-heavy.
    *   Deploy a **Redis** or **Memcached** caching layer. Since most redirects follow a power-law distribution (a few URLs get $90\%$ of clicks), storing active URL mapping keys in cache yields sub-millisecond response times.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight URL Harvesting Vulnerability**: Warn the interviewer that using sequential counter-based codes (e.g. `000000`, `000001`) makes the service vulnerable to **URL harvesting**—adversaries can easily iterate through all sequence numbers and scrape the private target URLs. Suggest encrypting/obfuscating the counter (e.g. using a Feistel Cipher or a small encryption tool like Skip32) to generate pseudorandom looking short codes from sequential IDs.
*   **Estimate Database Storage Size**: Calculate storage requirements to show real-world system architectural thinking:
    *   Assume 100 million new URLs/day.
    *   If each record (ID, long URL, short URL, metadata) takes 500 bytes:
        $$\text{Storage/day} = 10^8 \times 500 \text{ bytes} \approx 50 \text{ GB/day}$$
        $$\text{Storage/year} \approx 18 \text{ TB/year}$$
    *   This shows you think like a Systems Architect, not just a programmer.
