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
    abort();
}

static QNode *make_internal(QNode *tl, QNode *tr, QNode *bl, QNode *br) {
    abort();
}

static int all_same(int *grid, int n, int row, int col, int size) {
    abort();
}

static QNode *build(int *grid, int n, int row, int col, int size) {
    abort();
}

static void free_tree(QNode *node) {
    abort();
}

typedef struct { int is_leaf, val; } FlatNode;
typedef struct { FlatNode *data; int len, cap; } FlatVec;

static void fv_init(FlatVec *fv) {
    abort();
}
static void fv_push(FlatVec *fv, int is_leaf, int val) {
    abort();
}
static void fv_free(FlatVec *fv) {
    abort();
}

static FlatVec level_order(QNode *root) {
    abort();
}

static void print_flat(FlatVec *fv) {
    abort();
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
