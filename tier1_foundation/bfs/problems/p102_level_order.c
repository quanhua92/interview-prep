/*
 * P102: Binary Tree Level Order Traversal (Medium)
 * https://leetcode.com/problems/binary-tree-level-order-traversal/
 * Topics: Tree, Breadth-First Search, Binary Tree
 * 
 * Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).
 * 
 * Example 1:
 *     Input: root = [3,9,20,null,null,15,7]
 *     Output: [[3],[9,20],[15,7]]
 * 
 * Example 2:
 *     Input: root = [1]
 *     Output: [[1]]
 * 
 * Example 3:
 *     Input: root = []
 *     Output: []
 * 
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 2000].
 *     - -1000 <= Node.val <= 1000
 * 
 * Hints:
 *     - Use a queue to perform BFS.
 * 
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
 * 
 * Hint: Use a queue to process nodes level by level.
 */
#include "ctest.h"
#include <limits.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

#define NULL_VAL INT_MIN

static TreeNode *make_node(int val) {
    /* TODO: Implement */
    return 0;
}

static TreeNode *build_tree(const int *vals, int n) {
    /* TODO: Implement */
    return 0;
}

static void free_tree(TreeNode *root) {
    /* TODO: Implement */
    return 0;
}

static int **levelOrder(TreeNode *root, int *returnSize, int **returnColumnSizes) {
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    int vals[20];
    int vals_n;
    int expected_flat[20];
    int row_sizes[20];
    int num_rows;
} TC;

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;
    TC tests[] = {
        {"example 1", {3,9,20,NULL_VAL,NULL_VAL,15,7}, 7, {3,9,20,15,7}, {1,2,2}, 3},
        {"example 2", {1}, 1, {1}, {1}, 1},
        {"empty", {0}, 0, {0}, {0}, 0},
        {"right child only", {1,NULL_VAL,2}, 3, {1,2}, {1,1}, 2},
        {"left child only", {1,2}, 2, {1,2}, {1,1}, 2},
        {"full binary tree depth 2", {5,3,8,1,4,7,9}, 7, {5,3,8,1,4,7,9}, {1,2,4}, 3},
        {"negative values", {-1,-2,-3}, 3, {-1,-2,-3}, {1,2}, 2},
        {"all same value", {1,1,1,1,1,1,1}, 7, {1,1,1,1,1,1,1}, {1,2,4}, 3},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        TreeNode *root = build_tree(tests[i].vals, tests[i].vals_n);
        int got_rows = 0;
        int *got_sizes = NULL;
        int **got = levelOrder(root, &got_rows, &got_sizes);
        int ok = (got_rows == tests[i].num_rows);
        if (ok) {
            int idx = 0;
            for (int r = 0; r < got_rows; r++) {
                if (got_sizes[r] != tests[i].row_sizes[r]) { ok = 0; break; }
                for (int c = 0; c < got_sizes[r]; c++) {
                    if (got[r][c] != tests[i].expected_flat[idx]) { ok = 0; break; }
                    idx++;
                }
                if (!ok) break;
            }
        }
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected rows: %d, Got rows: %d\n", tests[i].num_rows, got_rows);
        }
        for (int r = 0; r < got_rows; r++) free(got[r]);
        free(got);
        free(got_sizes);
        free_tree(root);
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
