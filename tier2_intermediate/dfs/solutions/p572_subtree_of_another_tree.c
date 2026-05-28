/*
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 *
 * Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
 * A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
 * Example 1:
 *     Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 *     Output: true
 *
 * Example 2:
 *     Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
 *     Output: false
 *
 * Constraints:
 *     - The number of nodes in the root tree is in the range [1, 2000].
 *     - The number of nodes in the subRoot tree is in the range [1, 1000].
 *     - -104 <= root.val <= 104
 *     - -104 <= subRoot.val <= 104
 *
 * Hint: Which approach is better here- recursive or iterative?
 * Hint: If recursive approach is better, can you write recursive function with its parameters?
 * Hint: Two trees <b>s</b> and <b>t</b> are said to be identical if their root values are same and their left and right subtrees are identical. Can you write this in form of recursive formulae?
 * Hint: Recursive formulae can be:
 * isIdentical(s,t)= s.val==t.val AND isIdentical(s.left,t.left) AND isIdentical(s.right,t.right)
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
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
    TreeNode *root = build_tree(rv, rn);
    TreeNode *sub = build_tree(sv, sn);
    write_bool(isSubtree(root, sub));
    free(root_line);
    free(sub_line);
    return 0;
}
