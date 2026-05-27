/*
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 */

#include "io.h"
#include <vector>

static bool dfs(const std::vector<int>& arr, int i, std::vector<char>& visited) {
    if (i < 0 || i >= (int)arr.size() || visited[i]) return false;
    if (arr[i] == 0) return true;
    visited[i] = 1;
    return dfs(arr, i + arr[i], visited) || dfs(arr, i - arr[i], visited);
}

int main() {
    auto arr = read_ints();
    int start = std::stoi(read_line());
    std::vector<char> visited(arr.size(), 0);
    write_bool(dfs(arr, start, visited));
    return 0;
}
