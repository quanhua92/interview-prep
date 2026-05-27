/*
 * P77: Combinations (Medium)
 * https://leetcode.com/problems/combinations/
 * Topics: Backtracking
 *
 * Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
 * You may return the answer in any order.
 *
 * Example 1:
 *     Input: n = 4, k = 2
 *     Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 *
 * Example 2:
 *     Input: n = 1, k = 1
 *     Output: [[1]]
 *
 * Constraints:
 *     - 1 <= n <= 20
 *     - 1 <= k <= n
 *
 * Hint: Use backtracking with a start index to generate all k-length combinations from 1..n.
 */

#include "io.h"
#include <vector>

static void backtrack(int start, int n, int k, std::vector<int>& path, std::vector<std::vector<int>>& res) {
    if ((int)path.size() == k) {
        res.push_back(path);
        return;
    }
    for (int i = start; i <= n; i++) {
        path.push_back(i);
        backtrack(i + 1, n, k, path, res);
        path.pop_back();
    }
}

static std::vector<std::vector<int>> combine(int n, int k) {
    std::vector<std::vector<int>> res;
    std::vector<int> path;
    backtrack(1, n, k, path, res);
    return res;
}

int main(void)
{
    std::string line_n = read_line();
    int n = std::stoi(line_n);
    std::string line_k = read_line();
    int k = std::stoi(line_k);
    auto result = combine(n, k);
    for (const auto& row : result)
        write_ints(row);
    return 0;
}
