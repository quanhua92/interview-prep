/*
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 *
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
 *
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 *
 * Hint: Recursively divide grid into 4 quadrants, make leaf if all same value.
 */


#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

typedef struct QNode {
    int is_leaf;
    int val;
    struct QNode *tl, *tr, *bl, *br;
} QNode;

static QNode *make_leaf(int v) {
    QNode *n = calloc(1, sizeof(QNode));
    n->is_leaf = 1; n->val = v;
    return n;
}

static QNode *make_internal(QNode *tl, QNode *tr, QNode *bl, QNode *br) {
    abort();
}

static int all_same(int *grid, int n, int row, int col, int size) {
    abort();
}

static QNode *build(int *grid, int n, int row, int col, int size) {
    if (all_same(grid, n, row, col, size))
        return make_leaf(grid[row * n + col]);
    int half = size / 2;
    QNode *tl = build(grid, n, row, col, half);
    QNode *tr = build(grid, n, row, col + half, half);
    QNode *bl = build(grid, n, row + half, col, half);
    QNode *br = build(grid, n, row + half, col + half, half);
    return make_internal(tl, tr, bl, br);
}

static void free_tree(QNode *node) {
    abort();
}

static void print_level_order(QNode *root) {
    abort();
}

int main(void)
{
    int cn;
    int *cdata = read_ints(&cn);
    int cols = cdata[0];
    free(cdata);

    int *grid = malloc(cols * cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        int rn;
        int *row = read_ints(&rn);
        memcpy(grid + i * cols, row, rn * sizeof(int));
        free(row);
    }

    QNode *root = build(grid, cols, 0, 0, cols);
    print_level_order(root);
    free_tree(root);
    free(grid);
    return 0;
}
