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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find(int *parent, int x) {
    /* TODO: Implement */
    return 0;
}

static void unite(int *parent, int *rank, int x, int y) {
    /* TODO: Implement */
    return 0;
}

int equationsPossible(int n_eq, const char **equations) {
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    int n_eq;
    const char *equations[8];
    int expected;
} TC;

int main(void) {
    TC tcs[] = {
        { "example 1", 2, {"a==b","b!=a"}, 0 },
        { "example 2", 2, {"b==a","a==b"}, 1 },
        { "example 3", 3, {"a==b","b==c","a==c"}, 1 },
        { "contradiction", 1, {"a!=a"}, 0 },
        { "all different no contradiction", 3, {"a!=b","b!=c","c!=a"}, 1 },
        { "chain equality then inequality", 4, {"a==b","b==c","c==d","a!=d"}, 0 },
        { "independent groups", 2, {"a==b","c!=d"}, 1 },
        { "self equality", 1, {"a==a"}, 1 },
    };
    int n_tcs = sizeof(tcs) / sizeof(tcs[0]);

    printf("\n============================================================\n");
    printf("  990. Satisfiability of Equality Equations\n");
    printf("============================================================\n");

    int passed = 0;
    for (int i = 0; i < n_tcs; i++) {
        int got = equationsPossible(tcs[i].n_eq, tcs[i].equations);
        if (got == tcs[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tcs[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tcs[i].label);
            printf("    Expected: %s\n    Got:      %s\n",
                   tcs[i].expected ? "true" : "false", got ? "true" : "false");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tcs);
    printf("============================================================\n\n");
    return passed == n_tcs ? 0 : 1;
}
