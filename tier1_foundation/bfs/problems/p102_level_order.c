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

static void solve(TreeNode *root) {
    abort();
}

int main(void)
{
    int n = read_int();
    if (n == 0) return 0;
    char *line = read_line();
    int *vals = (int *)malloc(sizeof(int) * n);
    char *tok = strtok(line, " ");
    for (int i = 0; i < n; i++) {
        if (strcmp(tok, "null") == 0) {
            vals[i] = NULL_VAL;
        } else {
            vals[i] = atoi(tok);
        }
        tok = strtok(NULL, " ");
    }
    free(line);
    TreeNode *root = build_tree(vals, n);
    solve(root);
    free(vals);
    free_tree(root);
    return 0;
}
