/*
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 * A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:
 * We can construct a Quad-Tree from a two-dimensional area using the following steps:
 * If you want to know more about the Quad-Tree, you can refer to the wiki.
 * Quad-Tree format:
 * You don't need to read this section for solving the problem. This is only if you want to understand the output format here. The output represents the serialized format of a Quad-Tree using level order traversal, where null signifies a path terminator where no node exists below.
 * It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list [isLeaf, val].
 * If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val] and if the value of isLeaf or val is False we represent it as 0.
 *     class Node {
 *     public boolean val;
 *     public boolean isLeaf;
 *     public Node topLeft;
 *     public Node topRight;
 *     public Node bottomLeft;
 *     public Node bottomRight;
 *     }
 *
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
 *     Explanation: The explanation of this example is shown below:
 *     Notice that 0 represents False and 1 represents True in the photo representing the Quad-Tree.
 *
 * Example 2:
 *     Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
 *     Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
 *     Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
 *     The topLeft, bottomLeft and bottomRight each has the same value.
 *     The topRight have different values so we divide it into 4 sub-grids where each has the same value.
 *     Explanation is shown in the photo below:
 *
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 *
 * Template (python3):
 *     '''
 *     # Definition for a QuadTree node.
 *     class Node:
 *         def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
 *             self.val = val
 *             self.isLeaf = isLeaf
 *             self.topLeft = topLeft
 *             self.topRight = topRight
 *             self.bottomLeft = bottomLeft
 *             self.bottomRight = bottomRight
 *     '''
 *
 *     class Solution:
 *         def construct(self, grid: List[List[int]]) -> 'Node':
 */


#include <stdio.h>
#include <stdlib.h>
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
    QNode *n = calloc(1, sizeof(QNode));
    n->is_leaf = 0; n->val = 1;
    n->tl = tl; n->tr = tr; n->bl = bl; n->br = br;
    return n;
}

static int all_same(int *grid, int n, int row, int col, int size) {
    int v = grid[row * n + col];
    for (int i = row; i < row + size; i++)
        for (int j = col; j < col + size; j++)
            if (grid[i * n + j] != v) return 0;
    return 1;
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
    if (!node) return;
    free_tree(node->tl); free_tree(node->tr);
    free_tree(node->bl); free_tree(node->br);
    free(node);
}

typedef struct { int is_leaf, val; } FlatNode;
typedef struct { FlatNode *data; int len, cap; } FlatVec;

static void fv_init(FlatVec *fv) { fv->cap = 64; fv->data = malloc(fv->cap * sizeof(FlatNode)); fv->len = 0; }
static void fv_push(FlatVec *fv, int is_leaf, int val) {
    if (fv->len == fv->cap) { fv->cap *= 2; fv->data = realloc(fv->data, fv->cap * sizeof(FlatNode)); }
    fv->data[fv->len++] = (FlatNode){is_leaf, val};
}
static void fv_free(FlatVec *fv) { free(fv->data); }

static FlatVec level_order(QNode *root) {
    FlatVec result; fv_init(&result);
    if (!root) { fv_free(&result); return result; }
    typedef struct { QNode **data; int len, cap, head; } Queue;
    Queue q; q.cap = 64; q.data = malloc(q.cap * sizeof(QNode*)); q.len = 0; q.head = 0;
    q.data[q.len++] = root;
    while (q.head < q.len) {
        QNode *node = q.data[q.head++];
        if (!node) { fv_push(&result, -1, -1); continue; }
        fv_push(&result, node->is_leaf, node->val);
        if (!node->is_leaf) {
            if (q.len + 4 > q.cap) { q.cap *= 2; q.data = realloc(q.data, q.cap * sizeof(QNode*)); }
            q.data[q.len++] = node->tl;
            q.data[q.len++] = node->tr;
            q.data[q.len++] = node->bl;
            q.data[q.len++] = node->br;
        }
    }
    while (result.len > 0 && result.data[result.len - 1].is_leaf == -1) result.len--;
    free(q.data);
    return result;
}

static void print_flat(FlatVec *fv) {
    printf("[");
    for (int i = 0; i < fv->len; i++) {
        if (i) printf(",");
        if (fv->data[i].is_leaf == -1) printf("null");
        else printf("[%d,%d]", fv->data[i].is_leaf, fv->data[i].val);
    }
    printf("]");
}

int main(void)
{
    printf("\n============================================================\n");
    printf("  427. Construct Quad Tree\n");
    printf("============================================================\n");
    int passed = 0, total = 5;

    {
        int grid[] = {0,1,1,0};
        QNode *root = build(grid, 2, 0, 0, 2);
        FlatVec got = level_order(root);
        int exp_il[] = {0,1,1,1,1}, exp_v[] = {1,0,1,1,0};
        int ok = got.len == 5;
        if (ok) for (int i = 0; i < 5; i++) if (got.data[i].is_leaf != exp_il[i] || got.data[i].val != exp_v[i]) { ok = 0; break; }
        if (ok) { passed++; printf("  Test 1 (example 2): PASS\n"); }
        else { printf("  Test 1 (example 2): FAIL\n  Expected: [[0,1],[1,0],[1,1],[1,1],[1,0]]\n  Got:      "); print_flat(&got); printf("\n"); }
        fv_free(&got); free_tree(root);
    }
    {
        int grid[] = {
            1,1,1,1,0,0,0,0,
            1,1,1,1,0,0,0,0,
            1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,
            1,1,1,1,0,0,0,0,
            1,1,1,1,0,0,0,0,
            1,1,1,1,0,0,0,0,
            1,1,1,1,0,0,0,0
        };
        QNode *root = build(grid, 8, 0, 0, 8);
        FlatVec got = level_order(root);
        int exp_il[] = {0,1,0,1,1,1,1,1,1}, exp_v[] = {1,1,1,1,0,0,0,1,1};
        int ok = got.len == 9;
        if (ok) for (int i = 0; i < 9; i++) if (got.data[i].is_leaf != exp_il[i] || got.data[i].val != exp_v[i]) { ok = 0; break; }
        if (ok) { passed++; printf("  Test 2 (example 3): PASS\n"); }
        else { printf("  Test 2 (example 3): FAIL\n  Expected: [[0,1],[1,1],[0,1],[1,1],[1,0],[1,0],[1,0],[1,1],[1,1]]\n  Got:      "); print_flat(&got); printf("\n"); }
        fv_free(&got); free_tree(root);
    }
    {
        int grid[] = {0};
        QNode *root = build(grid, 1, 0, 0, 1);
        FlatVec got = level_order(root);
        int ok = got.len == 1 && got.data[0].is_leaf == 1 && got.data[0].val == 0;
        if (ok) { passed++; printf("  Test 3 (1x1 all zeros): PASS\n"); }
        else { printf("  Test 3 (1x1 all zeros): FAIL\n"); }
        fv_free(&got); free_tree(root);
    }
    {
        int grid[] = {1};
        QNode *root = build(grid, 1, 0, 0, 1);
        FlatVec got = level_order(root);
        int ok = got.len == 1 && got.data[0].is_leaf == 1 && got.data[0].val == 1;
        if (ok) { passed++; printf("  Test 4 (1x1 all ones): PASS\n"); }
        else { printf("  Test 4 (1x1 all ones): FAIL\n"); }
        fv_free(&got); free_tree(root);
    }
    {
        int grid[] = {1,1,1,1};
        QNode *root = build(grid, 2, 0, 0, 2);
        FlatVec got = level_order(root);
        int ok = got.len == 1 && got.data[0].is_leaf == 1 && got.data[0].val == 1;
        if (ok) { passed++; printf("  Test 5 (2x2 all same ones): PASS\n"); }
        else { printf("  Test 5 (2x2 all same ones): FAIL\n"); }
        fv_free(&got); free_tree(root);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
