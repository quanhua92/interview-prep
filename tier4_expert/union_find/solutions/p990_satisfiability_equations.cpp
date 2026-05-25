/*
 * P990: Satisfiability of Equality Equations (Medium)
 * https://leetcode.com/problems/satisfiability-of-equality-equations/
 * Topics: Array, String, Union Find, Graph
 *
 * You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
 * Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.
 *
 * Example 1:
 *     Input: equations = ["a==b","b!=a"]
 *     Output: false
 *     Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
 *     There is no way to assign the variables to satisfy both equations.
 *
 * Example 2:
 *     Input: equations = ["b==a","a==b"]
 *     Output: true
 *     Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
 *
 * Constraints:
 *     - 1 <= equations.length <= 500
 *     - equations[i].length == 4
 *     - equations[i][0] is a lowercase letter.
 *     - equations[i][1] is either '=' or '!'.
 *     - equations[i][2] is '='.
 *     - equations[i][3] is a lowercase letter.
 *
 * Template (python3):
 *     class Solution:
 *         def equationsPossible(self, equations: List[str]) -> bool:
 *
 * Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
 */


#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

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

struct TC {
    const char *label;
    std::vector<std::string> equations;
    bool expected;
};

int main(void) {
    std::vector<TC> tcs = {
        { "example 1", {"a==b","b!=a"}, false },
        { "example 2", {"b==a","a==b"}, true },
        { "example 3", {"a==b","b==c","a==c"}, true },
        { "contradiction", {"a!=a"}, false },
        { "all different no contradiction", {"a!=b","b!=c","c!=a"}, true },
        { "chain equality then inequality", {"a==b","b==c","c==d","a!=d"}, false },
        { "independent groups", {"a==b","c!=d"}, true },
        { "self equality", {"a==a"}, true },
    };

    printf("\n============================================================\n");
    printf("  990. Satisfiability of Equality Equations\n");
    printf("============================================================\n");

    int passed = 0;
    for (int i = 0; i < (int)tcs.size(); i++) {
        bool got = equationsPossible(tcs[i].equations);
        if (got == tcs[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tcs[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tcs[i].label);
            printf("    Expected: %s\n    Got:      %s\n",
                   tcs[i].expected ? "true" : "false", got ? "true" : "false");
        }
    }
    printf("\n  %d/%d passed\n", passed, (int)tcs.size());
    printf("============================================================\n\n");
    return passed == (int)tcs.size() ? 0 : 1;
}
