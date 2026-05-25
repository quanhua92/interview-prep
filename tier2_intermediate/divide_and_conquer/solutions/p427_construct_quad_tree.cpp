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


#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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

typedef std::pair<int,int> IP;
static std::vector<IP> level_order(QNode *root) {
    std::vector<IP> result;
    if (!root) return result;
    std::queue<QNode*> q;
    q.push(root);
    while (!q.empty()) {
        QNode *node = q.front(); q.pop();
        if (!node) { result.push_back({-1, -1}); continue; }
        result.push_back({node->is_leaf ? 1 : 0, node->val ? 1 : 0});
        if (!node->is_leaf) {
            q.push(node->tl); q.push(node->tr); q.push(node->bl); q.push(node->br);
        }
    }
    while (!result.empty() && result.back().first == -1) result.pop_back();
    return result;
}

static void print_flat(const std::vector<IP> &fv) {
    printf("[");
    for (size_t i = 0; i < fv.size(); i++) {
        if (i) printf(",");
        if (fv[i].first == -1) printf("null");
        else printf("[%d,%d]", fv[i].first, fv[i].second);
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
        std::vector<std::vector<int>> grid = {{0,1},{1,0}};
        QNode *root = build(grid, 0, 0, 2);
        auto got = level_order(root);
        std::vector<IP> exp = {{0,1},{1,0},{1,1},{1,1},{1,0}};
        if (got == exp) { passed++; printf("  Test 1 (example 2): PASS\n"); }
        else { printf("  Test 1 (example 2): FAIL\n  Expected: "); print_flat(exp); printf("\n  Got:      "); print_flat(got); printf("\n"); }
        free_tree(root);
    }
    {
        std::vector<std::vector<int>> grid = {
            {1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},
            {1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0}
        };
        QNode *root = build(grid, 0, 0, 8);
        auto got = level_order(root);
        std::vector<IP> exp = {{0,1},{1,1},{0,1},{1,1},{1,0},{1,0},{1,0},{1,1},{1,1}};
        if (got == exp) { passed++; printf("  Test 2 (example 3): PASS\n"); }
        else { printf("  Test 2 (example 3): FAIL\n  Expected: "); print_flat(exp); printf("\n  Got:      "); print_flat(got); printf("\n"); }
        free_tree(root);
    }
    {
        std::vector<std::vector<int>> grid = {{0}};
        QNode *root = build(grid, 0, 0, 1);
        auto got = level_order(root);
        std::vector<IP> exp = {{1,0}};
        if (got == exp) { passed++; printf("  Test 3 (1x1 all zeros): PASS\n"); }
        else { printf("  Test 3 (1x1 all zeros): FAIL\n"); }
        free_tree(root);
    }
    {
        std::vector<std::vector<int>> grid = {{1}};
        QNode *root = build(grid, 0, 0, 1);
        auto got = level_order(root);
        std::vector<IP> exp = {{1,1}};
        if (got == exp) { passed++; printf("  Test 4 (1x1 all ones): PASS\n"); }
        else { printf("  Test 4 (1x1 all ones): FAIL\n"); }
        free_tree(root);
    }
    {
        std::vector<std::vector<int>> grid = {{1,1},{1,1}};
        QNode *root = build(grid, 0, 0, 2);
        auto got = level_order(root);
        std::vector<IP> exp = {{1,1}};
        if (got == exp) { passed++; printf("  Test 5 (2x2 all same ones): PASS\n"); }
        else { printf("  Test 5 (2x2 all same ones): FAIL\n"); }
        free_tree(root);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
