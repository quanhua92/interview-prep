/*
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 */

#include "io.h"
#include <vector>

static bool dfs(const std::vector<int>& arr, int i, std::vector<char>& visited) {
    abort();
}

int main() {
    auto arr = read_ints();
    int start = std::stoi(read_line());
    std::vector<char> visited(arr.size(), 0);
    write_bool(dfs(arr, start, visited));
    return 0;
}
