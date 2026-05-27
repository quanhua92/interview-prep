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
    int parent[26], rank[26];
    for (int i = 0; i < 26; i++) { parent[i] = i; rank[i] = 0; }

    for (int i = 0; i < n_eq; i++) {
        if (equations[i][1] == '=') {
            unite(parent, rank, equations[i][0] - 'a', equations[i][3] - 'a');
        }
    }

    for (int i = 0; i < n_eq; i++) {
        if (equations[i][1] == '!') {
            if (find(parent, equations[i][0] - 'a') == find(parent, equations[i][3] - 'a'))
                return 0;
        }
    }
    return 1;
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
