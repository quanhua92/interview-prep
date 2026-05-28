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
#include <stdlib.h>
#include <string.h>

static int find(int *parent, int x) {
    if (parent[x] != x)
        parent[x] = find(parent, parent[x]);
    return parent[x];
}

static void unite(int *parent, int *rank, int x, int y) {
    int rx = find(parent, x), ry = find(parent, y);
    if (rx == ry) return;
    if (rank[rx] < rank[ry]) { int t = rx; rx = ry; ry = t; }
    parent[ry] = rx;
    if (rank[rx] == rank[ry]) rank[rx]++;
}

int equationsPossible(int n_eq, const char **equations) {
    abort();
}

int main(void)
{
    int cnt;
    int *first = read_ints(&cnt);
    int n_eq = first[0];
    free(first);
    const char **equations = malloc(n_eq * sizeof(char *));
    for (int i = 0; i < n_eq; i++) {
        equations[i] = read_line();
    }
    int result = equationsPossible(n_eq, equations);
    write_bool(result);
    for (int i = 0; i < n_eq; i++) free((void *)equations[i]);
    free(equations);
    return 0;
}
