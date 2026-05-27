/*
 * P394: Decode String (Medium)
 * https://leetcode.com/problems/decode-string/
 * Topics: String, Stack, Recursion
 *
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.
 *
 * Hint: Use a stack to handle nested k[encoded] patterns.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static char result_buf[100001];

static char *decode_string(const char *s) {
    int num_stack[30], pos_stack[30];
    int top = 0;
    int curr_num = 0;
    int len = 0;

    for (int i = 0; s[i]; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            curr_num = curr_num * 10 + (s[i] - '0');
        } else if (s[i] == '[') {
            num_stack[top] = curr_num;
            pos_stack[top] = len;
            top++;
            curr_num = 0;
        } else if (s[i] == ']') {
            top--;
            int repeat = num_stack[top];
            int start = pos_stack[top];
            int seg_len = len - start;
            for (int j = 1; j < repeat; j++) {
                memcpy(result_buf + len, result_buf + start, seg_len);
                len += seg_len;
            }
        } else {
            result_buf[len++] = s[i];
        }
    }
    result_buf[len] = '\0';
    return result_buf;
}

int main(void)
{
    char *s = read_line();
    write_string(decode_string(s));
    free(s);
    return 0;
}
