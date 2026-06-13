/*
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
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
    abort();
}

#define NL 2147483647

static void print_bfs(TreeNode *root) {
    abort();
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
