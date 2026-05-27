/*
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 */

#include "io.h"
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

static int is_same(TreeNode *a, TreeNode *b) {
    if (!a && !b) return 1;
    if (!a || !b) return 0;
    return a->val == b->val && is_same(a->left, b->left) && is_same(a->right, b->right);
}

static int isSubtree(TreeNode *root, TreeNode *subRoot) {
    if (!subRoot) return 1;
    if (!root) return 0;
    if (is_same(root, subRoot)) return 1;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

int main(void) {
    char *root_line = read_line();
    char *sub_line = read_line();
    int rv[1000], rn = 0, sv[1000], sn = 0;
    char *tok;
    tok = strtok(root_line, " ");
    while (tok) { rv[rn++] = strcmp(tok, "null") == 0 ? NL : atoi(tok); tok = strtok(NULL, " "); }
    tok = strtok(sub_line, " ");
    while (tok) { sv[sn++] = strcmp(tok, "null") == 0 ? NL : atoi(tok); tok = strtok(NULL, " "); }
    TreeNode *root = from_list(rv, rn);
    TreeNode *sub = from_list(sv, sn);
    write_bool(isSubtree(root, sub));
    free(root_line);
    free(sub_line);
    return 0;
}
