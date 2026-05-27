/*
 * P388: Longest Absolute File Path [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-absolute-file-path/
 * Topics: String, Stack, Depth-First Search
 */

#include "io.h"
#include <string.h>

int main(void) {
    char *input = read_line();
    int stack[100];
    int sp = 1;
    stack[0] = 0;
    int max_len = 0;
    int len = (int)strlen(input);
    int i = 0;
    while (i < len) {
        int depth = 0;
        while (i < len && input[i] == '\t') { depth++; i++; }
        int name_start = i;
        while (i < len && input[i] != '\n') i++;
        int name_len = i - name_start;
        if (i < len) i++;
        if (sp > depth + 1) sp = depth + 1;
        int is_file = 0;
        for (int j = name_start; j < name_start + name_len; j++) {
            if (input[j] == '.') { is_file = 1; break; }
        }
        if (is_file) {
            int total = stack[sp - 1] + name_len;
            if (total > max_len) max_len = total;
        } else {
            stack[sp] = stack[sp - 1] + name_len + 1;
            sp++;
        }
    }
    write_int(max_len);
    free(input);
    return 0;
}
