/*
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static char visited[50001];

static int dfs(const int *arr, int n, int i) {
    abort();
}

int main(void) {
    int n;
    int *arr = read_ints(&n);
    char *start_line = read_line();
    int start = atoi(start_line);
    memset(visited, 0, sizeof(visited));
    write_bool(dfs(arr, n, start));
    free(arr);
    free(start_line);
    return 0;
}
