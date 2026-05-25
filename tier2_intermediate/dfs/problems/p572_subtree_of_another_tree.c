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
#include "ctest.h"
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode* make_node(int val) {
    abort();
}

static struct TreeNode* from_list(int *vals, int n) {
    abort();
}

static void free_tree(struct TreeNode *root) {
    abort();
}

static int is_same(struct TreeNode *a, struct TreeNode *b) {
    abort();
}

static int isSubtree(struct TreeNode *root, struct TreeNode *subRoot) {
    abort();
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  572. Subtree of Another Tree\n");
    printf("============================================================\n");

    int passed = 0;

    struct { const char *label; int root_v[12]; int rn; int sub_v[12]; int sn; int expected; } tests[] = {
        {"example 1", {3,4,5,1,2}, 5, {4,1,2}, 3, 1},
        {"example 2", {3,4,5,1,2,100001,100001,100001,100001,0}, 10, {4,1,2}, 3, 0},
        {"identical trees", {1,2,3}, 3, {1,2,3}, 3, 1},
        {"single node match", {1}, 1, {1}, 1, 1},
        {"right-skewed subtree", {1,100001,2,100001,3}, 5, {2,100001,3}, 3, 1},
        {"no matching value", {1,2}, 2, {3}, 1, 0},
    };

    for (int t = 0; t < 6; t++) {
        struct TreeNode *root = from_list(tests[t].root_v, tests[t].rn);
        struct TreeNode *sub = from_list(tests[t].sub_v, tests[t].sn);
        int got = isSubtree(root, sub);
        if (got == tests[t].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
        } else {
            printf("  Test %d (%s): FAIL\n    Expected: %d\n    Got:      %d\n", t + 1, tests[t].label, tests[t].expected, got);
        }
        free_tree(root);
        free_tree(sub);
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
