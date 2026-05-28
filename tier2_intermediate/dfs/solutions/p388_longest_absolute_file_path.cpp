/*
 * P388: Longest Absolute File Path [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-absolute-file-path/
 * Topics: String, Stack, Depth-First Search
 */

#include "io.h"
#include <string>
#include <vector>

int main() {
    std::string input;
    std::string first = read_line();
    input = first;
    while (true) {
        std::string line = read_line();
        if (line.empty()) break;
        input += "\n" + line;
    }
    std::vector<int> stk = {0};
    int max_len = 0;
    int i = 0, len = input.size();
    while (i < len) {
        int depth = 0;
        while (i < len && input[i] == '\t') { depth++; i++; }
        int name_start = i;
        while (i < len && input[i] != '\n') i++;
        int name_len = i - name_start;
        if (i < len) i++;
        while ((int)stk.size() > depth + 1) stk.pop_back();
        bool is_file = false;
        for (int j = name_start; j < name_start + name_len; j++) {
            if (input[j] == '.') { is_file = true; break; }
        }
        if (is_file) {
            max_len = std::max(max_len, stk.back() + name_len);
        } else {
            stk.push_back(stk.back() + name_len + 1);
        }
    }
    write_int(max_len);
    return 0;
}
