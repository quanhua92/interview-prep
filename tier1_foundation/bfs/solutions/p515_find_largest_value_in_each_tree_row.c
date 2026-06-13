/*
 * P515: Find Largest Value in Each Tree Row [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-largest-value-in-each-tree-row/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).
 * Example 1:
 *     Input: root = [1,3,2,5,3,null,9]
 *     Output: [1,3,9]
 *
 * Example 2:
 *     Input: root = [1,2,3]
 *     Output: [1,3]
 *
 * Constraints:
 *     - The number of nodes in the tree will be in the range [0, 10^4].
 *     - -2^31 <= Node.val <= 2^31 - 1
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def largestValues(self, root: Optional[TreeNode]) -> List[int]:
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 10001
#define NULL_VAL INT_MIN

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

static TreeNode *make_node(int val) {
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

/* =====================================================================
 * Environment Utilities
 * ===================================================================== */

static TreeNode *build_tree_from_list(const int *vals, int n) {
    if (n == 0 || vals[0] == NULL_VAL) return NULL;
    TreeNode *root = make_node(vals[0]);
    TreeNode *queue[MAX_NODES];
    int front = 0, back = 0;
    queue[back++] = root;
    int i = 1;
    while (front < back && i < n) {
        TreeNode *node = queue[front++];
        if (i < n) {
            if (vals[i] != NULL_VAL) { node->left = make_node(vals[i]); queue[back++] = node->left; }
            i++;
        }
        if (i < n) {
            if (vals[i] != NULL_VAL) { node->right = make_node(vals[i]); queue[back++] = node->right; }
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

/* =====================================================================
 * LeetCode Solution
 * ===================================================================== */

static void solve(TreeNode *root) {
    if (!root) return;
    int result[MAX_NODES];
    int count = 0;
    TreeNode *queue[MAX_NODES];
    int front = 0, back = 0;
    queue[back++] = root;
    while (front < back) {
        int sz = back - front;
        int max_val = INT_MIN;
        for (int j = 0; j < sz; j++) {
            TreeNode *node = queue[front++];
            if (node->val > max_val) max_val = node->val;
            if (node->left) queue[back++] = node->left;
            if (node->right) queue[back++] = node->right;
        }
        result[count++] = max_val;
    }
    write_ints(result, count);
}

/* =====================================================================
 * Main
 * ===================================================================== */

int main(void)
{
    int n = read_int();
    if (n == 0) return 0;
    char *line = read_line();
    int *vals = (int *)malloc(sizeof(int) * n);
    char *tok = strtok(line, " ");
    for (int i = 0; i < n; i++) {
        if (strcmp(tok, "null") == 0) vals[i] = NULL_VAL;
        else vals[i] = atoi(tok);
        tok = strtok(NULL, " ");
    }
    free(line);

    TreeNode *tree = build_tree_from_list(vals, n);
    solve(tree);

    free(vals);
    free_tree(tree);
    return 0;
}
