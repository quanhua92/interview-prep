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

#include "io.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int solve(TreeNode *root) {
    abort();
}

int main(void)
{
    int n = read_int();
    char *line = read_line();
    int *vals = (int *)malloc(sizeof(int) * n);
    char *tok = strtok(line, " ");
    for (int i = 0; i < n; i++) {
        if (strcmp(tok, "null") == 0) vals[i] = NULL_VAL;
        else vals[i] = atoi(tok);
        tok = strtok(NULL, " ");
    }
    free(line);
    TreeNode *root = build_tree(vals, n);
    int result = solve(root);
    write_int(result);
    free(vals);
    free_tree(root);
    return 0;
}
