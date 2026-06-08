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
#define BASE62_CHARS "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct {
    char *codes[MAP_SIZE];
    char *urls[MAP_SIZE];
    char *url_codes[MAP_SIZE];
    int code_count;
    int url_count;
    int counter;
} Codec;

static void codec_init(Codec *c) {
    memset(c, 0, sizeof(*c));
}

static void codec_free(Codec *c) {
    for (int i = 0; i < c->code_count; i++) {
        free(c->codes[i]);
        free(c->urls[i]);
    }
    for (int i = 0; i < c->url_count; i++) {
        free(c->url_codes[i]);
    }
}

static void codec_get_base62(char *out, int num) {
    char buf[16];
    int len = 0;
    if (num == 0) {
        buf[len++] = BASE62_CHARS[0];
    } else {
        while (num > 0) {
            buf[len++] = BASE62_CHARS[num % 62];
            num /= 62;
        }
    }
    int pad = 6 - len;
    for (int i = 0; i < pad; i++) out[i] = BASE62_CHARS[0];
    for (int i = 0; i < len; i++) out[pad + i] = buf[len - 1 - i];
    out[6] = '\0';
}

static char *codec_encode(Codec *c, const char *longUrl) {
    for (int i = 0; i < c->url_count; i++) {
        if (strcmp(c->url_codes[i], longUrl) == 0) {
            char *result = malloc(30);
            sprintf(result, "http://tinyurl.com/%s", c->codes[i]);
            return result;
        }
    }
    char code[7];
    codec_get_base62(code, c->counter++);

    if (c->code_count < MAP_SIZE) {
        c->codes[c->code_count] = strdup(code);
        c->urls[c->code_count] = strdup(longUrl);
        c->code_count++;
    }
    if (c->url_count < MAP_SIZE) {
        c->url_codes[c->url_count] = strdup(longUrl);
        c->url_count++;
    }

    char *result = malloc(30);
    sprintf(result, "http://tinyurl.com/%s", code);
    return result;
}

static char *codec_decode(Codec *c, const char *shortUrl) {
    const char *code = strrchr(shortUrl, '/');
    code = code ? code + 1 : shortUrl;
    for (int i = 0; i < c->code_count; i++) {
        if (strcmp(c->codes[i], code) == 0) {
            return strdup(c->urls[i]);
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
