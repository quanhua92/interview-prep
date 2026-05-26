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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 1024

typedef struct {
    char *keys[MAP_SIZE];
    char *vals[MAP_SIZE];
    int count;
    int next_id;
} Codec;

static void codec_init(Codec *c) {
    memset(c, 0, sizeof(*c));
}

static void codec_free(Codec *c) {
    for (int i = 0; i < c->count; i++) {
        free(c->keys[i]);
        free(c->vals[i]);
    }
}

static char *codec_encode(Codec *c, const char *longUrl) {
    char key[16];
    sprintf(key, "%d", c->next_id++);
    char *kcopy = strdup(key);
    char *vcopy = strdup(longUrl);
    c->keys[c->count] = kcopy;
    c->vals[c->count] = vcopy;
    c->count++;
    char *result = malloc(strlen(key) + 22);
    sprintf(result, "http://tinyurl.com/%s", key);
    return result;
}

static char *codec_decode(Codec *c, const char *shortUrl) {
    const char *key = strrchr(shortUrl, '/');
    key = key ? key + 1 : shortUrl;
    for (int i = 0; i < c->count; i++) {
        if (strcmp(c->keys[i], key) == 0) {
            return strdup(c->vals[i]);
        }
    }
    return strdup("");
}

static char *solve(const char *longUrl) {
    Codec c;
    codec_init(&c);
    char *tiny = codec_encode(&c, longUrl);
    char *result = codec_decode(&c, tiny);
    free(tiny);
    codec_free(&c);
    return result;
}

int main(void) {
    int passed = 0, total = 4;
    printf("\n============================================================\n");
    printf("  535. Encode and Decode TinyURL\n");
    printf("============================================================\n");

    {
        char *got = solve("https://leetcode.com/problems/design-tinyurl");
        if (strcmp(got, "https://leetcode.com/problems/design-tinyurl") == 0) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: https://leetcode.com/problems/design-tinyurl, Got: %s\n", got); }
        free(got);
    }
    {
        char *got = solve("https://example.com/path/to/resource?query=1&param=2#section");
        if (strcmp(got, "https://example.com/path/to/resource?query=1&param=2#section") == 0) { passed++; printf("  Test 2 (URL with query and fragment): PASS\n"); }
        else { printf("  Test 2 (URL with query and fragment): FAIL\n  Expected: https://example.com/path/to/resource?query=1&param=2#section, Got: %s\n", got); }
        free(got);
    }
    {
        char *got = solve("http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u");
        if (strcmp(got, "http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u") == 0) { passed++; printf("  Test 3 (URL with many path segments): PASS\n"); }
        else { printf("  Test 3 (URL with many path segments): FAIL\n  Expected: http://a.co/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u, Got: %s\n", got); }
        free(got);
    }
    {
        char *got = solve("https://site.com");
        if (strcmp(got, "https://site.com") == 0) { passed++; printf("  Test 4 (minimal URL): PASS\n"); }
        else { printf("  Test 4 (minimal URL): FAIL\n  Expected: https://site.com, Got: %s\n", got); }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
