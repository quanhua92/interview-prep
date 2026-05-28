/*
 * P385: Mini Parser [PREMIUM] (Medium)
 * https://leetcode.com/problems/mini-parser/
 * Topics: String, Stack, Depth-First Search
 */

#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_nested(const char *s, int len) {
    abort();
}

int main(void) {
    char *s = read_line();
    int len = (int)strlen(s);
    if (s[0] != '[') {
        write_int(atoi(s));
    } else {
        write_string(s);
    }
    free(s);
    return 0;
}
