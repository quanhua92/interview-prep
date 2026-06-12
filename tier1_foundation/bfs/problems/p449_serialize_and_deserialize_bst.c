/*
 * P449: Serialize and Deserialize BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/serialize-and-deserialize-bst/
 * Topics: String, Tree, Depth-First Search, Breadth-First Search, Design, Binary Search Tree, Binary Tree
 *
 * Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
 * Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.
 * The encoded string should be as compact as possible.
 * Example 1:
 *     Input: root = [2,1,3]
 *     Output: [2,1,3]
 *
 * Example 2:
 *     Input: root = []
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 10^4].
 *     - 0 <= Node.val <= 10^4
 *     - The input tree is guaranteed to be a binary search tree.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, x):
 *     #         self.val = x
 *     #         self.left = None
 *     #         self.right = None
 *
 *     class Codec:
 *
 *         def serialize(self, root: Optional[TreeNode]) -> str:
 *             '''Encodes a tree to a single string.
 *             '''
 *
 *
 *         def deserialize(self, data: str) -> Optional[TreeNode]:
 *             '''Decodes your encoded data to tree.
 *             '''
 *
 *     # Your Codec object will be instantiated and called as such:
 *     # Your Codec object will be instantiated and called as such:
 *     # ser = Codec()
 *     # deser = Codec()
 *     # tree = ser.serialize(root)
 *     # ans = deser.deserialize(tree)
 *     # return ans
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
 * Codec: Serialize (pre-order, compact — no null markers)
 * ===================================================================== */

static int g_ser[MAX_NODES];
static int g_ser_len;

static void preorder_collect(TreeNode *root) {
    abort();
}

/* =====================================================================
 * Codec: Deserialize (BST bounds reconstruction)
 * ===================================================================== */

static int g_ser_pos;

static TreeNode *build_bst(long long lo, long long hi) {
    abort();
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

#define MAX_OUT 20005

static int g_out[MAX_OUT];
static int g_out_null[MAX_OUT];

static int convert_tree_to_list(TreeNode *root) {
    if (!root) return 0;
    int count = 0;
    TreeNode *queue[MAX_OUT];
    int front = 0, back = 0;
    queue[back++] = root;
    while (front < back) {
        TreeNode *node = queue[front++];
        if (node) {
            g_out[count] = node->val;
            g_out_null[count] = 0;
            count++;
            queue[back++] = node->left;
            queue[back++] = node->right;
        } else {
            g_out_null[count] = 1;
            count++;
        }
    }
    while (count > 0 && g_out_null[count - 1]) count--;
    return count;
}

/* =====================================================================
 * Solve
 * ===================================================================== */

static TreeNode *solve(TreeNode *root) {
    if (!root) return NULL;
    g_ser_len = 0;
    preorder_collect(root);
    g_ser_pos = 0;
    return build_bst(INT_MIN - 1LL, INT_MAX + 1LL);
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
    TreeNode *result = solve(tree);
    int out_count = convert_tree_to_list(result);

    char *buf = (char *)malloc(200000);
    int pos = 0;
    for (int j = 0; j < out_count; j++) {
        if (j > 0) buf[pos++] = ' ';
        if (g_out_null[j]) {
            strcpy(buf + pos, "null");
            pos += 4;
        } else {
            pos += sprintf(buf + pos, "%d", g_out[j]);
        }
    }
    buf[pos] = '\0';
    write_string(buf);

    free(vals);
    free(buf);
    return 0;
}
