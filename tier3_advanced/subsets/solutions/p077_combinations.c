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
#include <stdlib.h>

static int **result;
static int *col_sizes;
static int result_count;
static int result_cap;
static int k_val;

static void add_result(int *path) {
    if (result_count >= result_cap) {
        result_cap = result_cap ? result_cap * 2 : 64;
        result = realloc(result, result_cap * sizeof(int *));
        col_sizes = realloc(col_sizes, result_cap * sizeof(int));
    }
    result[result_count] = malloc(k_val * sizeof(int));
    for (int i = 0; i < k_val; i++) result[result_count][i] = path[i];
    col_sizes[result_count] = k_val;
    result_count++;
}

static void backtrack(int start, int n, int *path, int depth) {
    if (depth == k_val) {
        add_result(path);
        return;
    }
    for (int i = start; i <= n; i++) {
        path[depth] = i;
        backtrack(i + 1, n, path, depth + 1);
    }
}

int main(void)
{
    char *line_n = read_line();
    int n = atoi(line_n);
    free(line_n);
    char *line_k = read_line();
    int k = atoi(line_k);
    free(line_k);
    result = NULL;
    col_sizes = NULL;
    result_count = 0;
    result_cap = 0;
    k_val = k;
    int path[21];
    backtrack(1, n, path, 0);
    for (int i = 0; i < result_count; i++) {
        write_ints(result[i], col_sizes[i]);
    }
    for (int i = 0; i < result_count; i++) free(result[i]);
    free(result);
    free(col_sizes);
    return 0;
}
