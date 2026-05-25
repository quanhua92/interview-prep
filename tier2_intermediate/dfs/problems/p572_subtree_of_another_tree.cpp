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
#include "cpptest.h"
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

static TreeNode* from_list(const std::vector<int>& vals) {
    abort();
}

static void free_tree(TreeNode *root) {
    abort();
}

static bool is_same(TreeNode *a, TreeNode *b) {
    abort();
}

static bool isSubtree(TreeNode *root, TreeNode *subRoot) {
    abort();
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  572. Subtree of Another Tree\n");
    printf("============================================================\n");

    int passed = 0;

    struct TC { const char *label; std::vector<int> root; std::vector<int> sub; bool expected; };
    TC tests[] = {
        {"example 1", {3,4,5,1,2}, {4,1,2}, true},
        {"example 2", {3,4,5,1,2,100001,100001,100001,100001,0}, {4,1,2}, false},
        {"identical trees", {1,2,3}, {1,2,3}, true},
        {"single node match", {1}, {1}, true},
        {"right-skewed subtree", {1,100001,2,100001,3}, {2,100001,3}, true},
        {"no matching value", {1,2}, {3}, false},
    };

    for (int t = 0; t < 6; t++) {
        TreeNode *root = from_list(tests[t].root);
        TreeNode *sub = from_list(tests[t].sub);
        bool got = isSubtree(root, sub);
        if (got == tests[t].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
        } else {
            printf("  Test %d (%s): FAIL\n    Expected: %d\n    Got:      %d\n", t + 1, tests[t].label, (int)tests[t].expected, (int)got);
        }
        free_tree(root);
        free_tree(sub);
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
