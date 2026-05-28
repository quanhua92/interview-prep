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
