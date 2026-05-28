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
    abort();
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
