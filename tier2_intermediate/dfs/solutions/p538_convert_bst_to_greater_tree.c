/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

#define NL 2147483647

typedef struct TreeNode { int val; struct TreeNode *left, *right; } TreeNode;

static TreeNode *from_list(int *vals, int n) {
    if (n == 0 || vals[0] == NL) return NULL;
    TreeNode **nodes = calloc(n, sizeof(TreeNode*));
    for (int i = 0; i < n; i++) {
        if (vals[i] != NL) { nodes[i] = malloc(sizeof(TreeNode)); nodes[i]->val = vals[i]; nodes[i]->left = nodes[i]->right = NULL; }
    }
    for (int i = 0; i < n; i++) {
        if (nodes[i] && 2*i+1 < n) nodes[i]->left = nodes[2*i+1];
        if (nodes[i] && 2*i+2 < n) nodes[i]->right = nodes[2*i+2];
    }
    TreeNode *root = nodes[0];
    free(nodes);
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

int main(void) {
    char *line = read_line();
    if (!line[0]) { printf("\n"); return 0; }
    int vals[10000], n = 0;
    char *tok = strtok(line, " ");
    while (tok) {
        if (strcmp(tok, "null") == 0) vals[n++] = NL;
        else vals[n++] = atoi(tok);
        tok = strtok(NULL, " ");
    }
    if (n == 0 || vals[0] == NL) { printf("\n"); return 0; }
    TreeNode *root = from_list(vals, n);
    gtotal = 0;
    reverse_inorder(root);
    int first = 1;
    for (int i = 0; i < n; i++) {
        if (!first) printf(" ");
        first = 0;
        if (vals[i] == NL) printf("null");
        else printf("%d", vals[i]);
    }
    while (n > 0 && vals[n-1] == NL) n--;
    first = 1;
    for (int i = 0; i < n; i++) {
        if (!first) printf(" ");
        first = 0;
        printf("%d", vals[i]);
    }
    printf("\n");
    free(line);
    return 0;
}
