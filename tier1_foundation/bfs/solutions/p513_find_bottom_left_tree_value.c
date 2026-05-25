/*
 * P513: Find Bottom Left Tree Value [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-bottom-left-tree-value/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return the leftmost value in the last row of the tree.
 * Example 1:
 *     Input: root = [2,1,3]
 *     Output: 1
 *
 * Example 2:
 *     Input: root = [1,2,3,4,null,5,6,null,null,7]
 *     Output: 7
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [1, 104].
 *     - -231 <= Node.val <= 231 - 1
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
 */


#include "ctest.h"
#include <limits.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

#define NULL_VAL INT_MIN

static TreeNode *make_node(int val) {
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

static TreeNode *build_tree(const int *vals, int n) {
    if (n == 0 || vals[0] == NULL_VAL) return NULL;
    TreeNode *root = make_node(vals[0]);
    TreeNode *queue[10000];
    int front = 0, back = 0;
    queue[back++] = root;
    int i = 1;
    while (front < back && i < n) {
        TreeNode *node = queue[front++];
        if (i < n) {
            if (vals[i] != NULL_VAL) {
                node->left = make_node(vals[i]);
                queue[back++] = node->left;
            }
            i++;
        }
        if (i < n) {
            if (vals[i] != NULL_VAL) {
                node->right = make_node(vals[i]);
                queue[back++] = node->right;
            }
            i++;
        }
    }
    return root;
}

static void free_tree(TreeNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

static int findBottomLeftValue(TreeNode *root) {
    TreeNode *queue[10000];
    int front = 0, back = 0;
    queue[back++] = root;
    int result = root->val;
    while (front < back) {
        int sz = back - front;
        result = queue[front]->val;
        for (int j = 0; j < sz; j++) {
            TreeNode *node = queue[front++];
            if (node->left) queue[back++] = node->left;
            if (node->right) queue[back++] = node->right;
        }
    }
    return result;
}

typedef struct {
    const char *label;
    int vals[20];
    int n;
    int expected;
} TC;

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;
    TC tests[] = {
        {"example 1", {2, 1, 3}, 3, 1},
        {"example 2", {1, 2, 3, 4, NULL_VAL, 5, 6, NULL_VAL, NULL_VAL, 7}, 10, 7},
        {"single node", {1}, 1, 1},
        {"left child only", {1, 2}, 2, 2},
        {"right child only", {1, NULL_VAL, 2}, 3, 2},
        {"left skewed deep", {1, 2, NULL_VAL, 3, NULL_VAL, 4}, 6, 4},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        TreeNode *root = build_tree(tests[i].vals, tests[i].n);
        int got = findBottomLeftValue(root);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
        free_tree(root);
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
