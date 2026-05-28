/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 * Example 2:
 * Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
 * Example 1:
 *     Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
 *     Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
 *
 * Example 2:
 *     Input: root = [0,null,1]
 *     Output: [1,null,1]
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - -104 <= Node.val <= 104
 *     - All the values in the tree are unique.
 *     - root is guaranteed to be a valid binary search tree.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
 */

#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NL 2147483647

typedef struct TreeNode { int val; struct TreeNode *left, *right; } TreeNode;

static TreeNode *make_node(int val) {
    TreeNode *n = malloc(sizeof(TreeNode));
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

static TreeNode *build_tree(const int *vals, int n) {
    if (n == 0 || vals[0] == NL) return NULL;
    TreeNode *root = make_node(vals[0]);
    TreeNode **queue = malloc(n * sizeof(TreeNode *));
    int front = 0, back = 0;
    queue[back++] = root;
    int i = 1;
    while (front < back && i < n) {
        TreeNode *node = queue[front++];
        if (i < n) {
            if (vals[i] != NL) { node->left = make_node(vals[i]); queue[back++] = node->left; }
            i++;
        }
        if (i < n) {
            if (vals[i] != NL) { node->right = make_node(vals[i]); queue[back++] = node->right; }
            i++;
        }
    }
    free(queue);
    return root;
}

static int gtotal;
static void reverse_inorder(TreeNode *node) {
    if (!node) return;
    reverse_inorder(node->right);
    gtotal += node->val;
    node->val = gtotal;
    reverse_inorder(node->left);
}

static void serialize_level_order(TreeNode *root, int *out, int *out_n) {
    if (!root) { *out_n = 0; return; }
    TreeNode **queue = malloc(10000 * sizeof(TreeNode *));
    int front = 0, back = 0;
    queue[back++] = root;
    int count = 0;
    while (front < back) {
        TreeNode *node = queue[front++];
        if (node) {
            out[count++] = node->val;
            queue[back++] = node->left;
            queue[back++] = node->right;
        } else {
            out[count++] = NL;
        }
    }
    while (count > 0 && out[count - 1] == NL) count--;
    *out_n = count;
    free(queue);
}

int main(void) {
    char *line = read_line();
    if (!line || !line[0]) { write_string(""); free(line); return 0; }
    int *vals = malloc(10000 * sizeof(int));
    int n = 0;
    char *tok = strtok(line, " ");
    while (tok) {
        if (strcmp(tok, "null") == 0) vals[n++] = NL;
        else vals[n++] = atoi(tok);
        tok = strtok(NULL, " ");
    }
    if (n == 0 || vals[0] == NL) { write_string(""); free(line); free(vals); return 0; }
    TreeNode *root = build_tree(vals, n);
    gtotal = 0;
    reverse_inorder(root);

    int *result = malloc(10000 * sizeof(int));
    int result_n;
    serialize_level_order(root, result, &result_n);

    char *buf = malloc(100000);
    int bpos = 0;
    for (int i = 0; i < result_n; i++) {
        if (i > 0) buf[bpos++] = ' ';
        if (result[i] == NL) { strcpy(buf + bpos, "null"); bpos += 4; }
        else bpos += sprintf(buf + bpos, "%d", result[i]);
    }
    buf[bpos] = '\0';
    write_string(buf);
    free(line);
    free(vals);
    free(result);
    free(buf);
    return 0;
}
