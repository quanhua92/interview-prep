/*
 * P990: Satisfiability of Equality Equations (Medium)
 * https://leetcode.com/problems/satisfiability-of-equality-equations/
 * Topics: Array, String, Union Find, Graph
 *
 * Return true if it is possible to assign integers to variable names so as to satisfy all the given equations.
 *
 * Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
 */


#include "io.h"
#include <functional>
#include <string>
#include <vector>

bool equationsPossible(const std::vector<std::string> &equations) {
    int parent[26], rank_[26];
    for (int i = 0; i < 26; i++) { parent[i] = i; rank_[i] = 0; }

    std::function<int(int)> find = [&](int x) -> int {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    };

    auto unite = [&](int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (rank_[rx] < rank_[ry]) std::swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
    };

    for (auto &eq : equations) {
        if (eq[1] == '=') {
            unite(eq[0] - 'a', eq[3] - 'a');
        }
    }

    for (auto &eq : equations) {
        if (eq[1] == '!') {
            if (find(eq[0] - 'a') == find(eq[3] - 'a')) return false;
        }
    }
    return true;
}

int main(void)
{
    std::vector<int> first = read_ints();
    int n = first[0];
    std::vector<std::string> equations;
    for (int i = 0; i < n; i++) {
        equations.push_back(read_line());
    }
    write_bool(equationsPossible(equations));
    return 0;
}
