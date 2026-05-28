/*
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 */

#include "io.h"
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

static int is_same(TreeNode *a, TreeNode *b) {
    abort();
}

static int isSubtree(TreeNode *root, TreeNode *subRoot) {
    abort();
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
    TreeNode *root = build_tree(rv, rn);
    TreeNode *sub = build_tree(sv, sn);
    write_bool(isSubtree(root, sub));
    free(root_line);
    free(sub_line);
    return 0;
}
