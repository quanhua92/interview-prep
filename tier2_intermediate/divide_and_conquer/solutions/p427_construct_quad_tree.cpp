/*
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 *
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 *
 * Hint: Recursively divide grid into 4 quadrants, make leaf if all same value.
 */


#include "io.h"
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

struct QNode {
    bool is_leaf;
    bool val;
    QNode *tl, *tr, *bl, *br;
    QNode(bool il, bool v, QNode *a = nullptr, QNode *b = nullptr, QNode *c = nullptr, QNode *d = nullptr)
        : is_leaf(il), val(v), tl(a), tr(b), bl(c), br(d) {}
};

static bool all_same(const std::vector<std::vector<int>> &g, int row, int col, int size) {
    int v = g[row][col];
    for (int i = row; i < row + size; i++)
        for (int j = col; j < col + size; j++)
            if (g[i][j] != v) return false;
    return true;
}

static QNode *build(const std::vector<std::vector<int>> &g, int row, int col, int size) {
    if (all_same(g, row, col, size)) return new QNode(true, g[row][col] != 0);
    int half = size / 2;
    return new QNode(false, true,
        build(g, row, col, half), build(g, row, col + half, half),
        build(g, row + half, col, half), build(g, row + half, col + half, half));
}

static void free_tree(QNode *n) {
    if (!n) return;
    free_tree(n->tl); free_tree(n->tr); free_tree(n->bl); free_tree(n->br);
    delete n;
}

static void print_level_order(QNode *root) {
    if (!root) return;
    std::queue<QNode*> q;
    q.push(root);
    while (!q.empty()) {
        QNode *node = q.front(); q.pop();
        if (!node) { printf("null\n"); continue; }
        printf("%d %d\n", node->is_leaf ? 1 : 0, node->val ? 1 : 0);
        if (!node->is_leaf) {
            q.push(node->tl); q.push(node->tr); q.push(node->bl); q.push(node->br);
        }
    }
}

int main(void)
{
    std::vector<int> header = read_ints();
    int cols = header[0];
    std::vector<std::vector<int>> grid(cols);
    for (int i = 0; i < cols; i++) {
        grid[i] = read_ints();
    }
    QNode *root = build(grid, 0, 0, cols);
    print_level_order(root);
    free_tree(root);
    return 0;
}
