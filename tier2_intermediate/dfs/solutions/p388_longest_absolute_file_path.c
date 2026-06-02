/*
 * P388: Longest Absolute File Path [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-absolute-file-path/
 * Topics: String, Stack, Depth-First Search
 *
 * Suppose we have a file system that stores both files and directories. An example of one system is represented in the following picture:
 * Here, we have dir as the only directory in the root. dir contains two subdirectories, subdir1 and subdir2. subdir1 contains a file file1.ext and subdirectory subsubdir1. subdir2 contains a subdirectory subsubdir2, which contains a file file2.ext.
 * In text form, it looks like this (with -> representing the tab character):
 * If we were to write this representation in code, it will look like this: "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext". Note that the '\n' and '\t' are the new-line and tab characters.
 * Every file and directory has a unique absolute path in the file system, which is the order of directories that must be opened to reach the file/directory itself, all concatenated by '/'s. Using the above example, the absolute path to file2.ext is "dir/subdir2/subsubdir2/file2.ext". Each directory name consists of letters, digits, and/or spaces. Each file name is of the form name.extension, where name and extension consist of letters, digits, and/or spaces.
 * Given a string input representing the file system in the explained format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.
 * Note that the testcases are generated such that the file system is valid and no file or directory name has length 0.
 * Example 3:
 *     dir
 *     -> subdir1
 *     -> -> file1.ext
 *     -> -> subsubdir1
 *     -> subdir2
 *     -> -> subsubdir2
 *     -> -> -> file2.ext
 *
 * Example 1:
 *     Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
 *     Output: 20
 *     Explanation: We have only one file, and the absolute path is "dir/subdir2/file.ext" of length 20.
 *
 * Example 2:
 *     Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
 *     Output: 32
 *     Explanation: We have two files:
 *     "dir/subdir1/file1.ext" of length 21
 *     "dir/subdir2/subsubdir2/file2.ext" of length 32.
 *     We return 32 since it is the longest absolute path to a file.
 *
 * Example 3:
 *     Input: input = "a"
 *     Output: 0
 *     Explanation: We do not have any files, just a single directory named "a".
 *
 * Constraints:
 *     - 1 <= input.length <= 10^4
 *     - input may contain lowercase or uppercase English letters, a new line character '\n', a tab character '\t', a dot '.', a space ' ', and digits.
 *     - All file and directory names have positive length.
 *
 * Template (python3):
 *     class Solution:
 *         def lengthLongestPath(self, input: str) -> int:
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *input = read_line();
    int input_cap = strlen(input) + 1;
    while (1) {
        char *next = read_line();
        int next_len = strlen(next);
        if (next_len == 0) { free(next); break; }
        int old_len = strlen(input);
        while (old_len + 1 + next_len + 1 > input_cap) {
            input_cap *= 2;
        }
        input = realloc(input, input_cap);
        input[old_len] = '\n';
        memcpy(input + old_len + 1, next, next_len + 1);
        free(next);
    }
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
