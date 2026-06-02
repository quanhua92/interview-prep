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
    abort();
}

static void codec_free(Codec *c) {
    abort();
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

int main(void)
{
    char *url = read_line();
    char *result = solve(url);
    write_string(result);
    free(result);
    free(url);
    return 0;
}
