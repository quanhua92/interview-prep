/*
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
 *
 * Given the root of a Binary Search Tree (BST) and a key, delete the node with the given key in the BST.
 * Return the root node reference (possibly updated) of the BST.
 *
 * The deletion process involves finding the node and handling three cases:
 * - Node has no children: simply remove it.
 * - Node has one child: replace the node with its child.
 * - Node has two children: find the inorder successor (smallest in the right subtree),
 *   attach the deleted node's left subtree to the successor, and replace with the right subtree.
 *
 * Example 1:
 *     Input: root = [5,3,6,2,4,null,7], key = 3
 *     Output: [5,4,6,2,null,null,7]
 *     Explanation: The node with value 3 is deleted. One valid answer is [5,4,6,2,null,null,7],
 *     another is [5,2,6,null,4,null,7].
 *
 * Example 2:
 *     Input: root = [5,3,6,2,4,null,7], key = 0
 *     Output: [5,3,6,2,4,null,7]
 *     Explanation: The key 0 is not found, so the tree is unchanged.
 *
 * Example 3:
 *     Input: root = [], key = 0
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 10^4].
 *     - -10^5 <= Node.val <= 10^5
 *     - Each node has a unique value.
 *     - root is a valid binary search tree.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
 *
 * Hint: Recurse down the BST to find the target. When found with two children,
 * find the leftmost node in the right subtree (inorder successor), attach the left
 * subtree to it, and return the right subtree as the new root.
 */

#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode { int val; struct TreeNode *left, *right; } TreeNode;

static TreeNode *make_node(int val) {
    TreeNode *n = malloc(sizeof(TreeNode));
    n->val = val; n->left = n->right = NULL;
    return n;
}

static TreeNode *insert(TreeNode *root, int val) {
    if (!root) return make_node(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

static TreeNode *deleteNode(TreeNode *root, int key) {
    if (!root) return NULL;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) { TreeNode *t = root->right; free(root); return t; }
        if (!root->right) { TreeNode *t = root->left; free(root); return t; }
        TreeNode *mn = root->right;
        while (mn->left) mn = mn->left;
        root->val = mn->val;
        root->right = deleteNode(root->right, mn->val);
    }
    return root;
}

#define NL 2147483647

static void print_bfs(TreeNode *root) {
    if (!root) { printf("null"); return; }
    TreeNode *queue[10000];
    int front = 0, back = 0;
    queue[back++] = root;
    int first = 1;
    while (front < back) {
        TreeNode *cur = queue[front++];
        if (!first) printf(" ");
        first = 0;
        if (cur) {
            printf("%d", cur->val);
            queue[back++] = cur->left;
            queue[back++] = cur->right;
        } else {
            printf("null");
        }
    }
    while (back > 0 && !queue[back-1] && back >= 2) { back--; }
}

int main(void) {
    char *line = read_line();
    int key;
    {
        char *key_line = read_line();
        key = atoi(key_line);
        free(key_line);
    }
    TreeNode *root = NULL;
    char *p = strtok(line, " ");
    while (p) {
        int v = strcmp(p, "null") == 0 ? NL : atoi(p);
        if (v != NL) root = insert(root, v);
        p = strtok(NULL, " ");
    }
    root = deleteNode(root, key);
    if (!root) { printf("null\n"); }
    else { print_bfs(root); printf("\n"); }
    free(line);
    return 0;
}
