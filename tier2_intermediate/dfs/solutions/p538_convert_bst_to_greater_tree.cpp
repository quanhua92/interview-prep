/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 * Example 2:
 * Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
 * Example 1:
 *     Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
 *     Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
 *
 * Example 2:
 *     Input: root = [0,null,1]
 *     Output: [1,null,1]
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - -104 <= Node.val <= 104
 *     - All the values in the tree are unique.
 *     - root is guaranteed to be a valid binary search tree.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
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
    if (vals.empty() || vals[0] == 100001) return nullptr;
    TreeNode *root = new TreeNode(vals[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode *node = q.front(); q.pop();
        if (i < vals.size()) {
            if (vals[i] != 100001) { node->left = new TreeNode(vals[i]); q.push(node->left); }
            i++;
        }
        if (i < vals.size()) {
            if (vals[i] != 100001) { node->right = new TreeNode(vals[i]); q.push(node->right); }
            i++;
        }
    }
    return root;
}

static bool trees_equal(TreeNode *a, TreeNode *b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->val == b->val && trees_equal(a->left, b->left) && trees_equal(a->right, b->right);
}

static void free_tree(TreeNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

static int gtotal;

static void reverse_inorder(TreeNode *node) {
    if (!node) return;
    reverse_inorder(node->right);
    gtotal += node->val;
    node->val = gtotal;
    reverse_inorder(node->left);
}

static TreeNode* convertBST(TreeNode *root) {
    gtotal = 0;
    reverse_inorder(root);
    return root;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  538. Convert BST to Greater Tree\n");
    printf("============================================================\n");

    int passed = 0;

    struct TC { const char *label; std::vector<int> input; std::vector<int> expected; };
    TC tests[] = {
        {"example 1", {4,1,6,0,2,5,7,100001,100001,100001,3,100001,100001,100001,8}, {30,36,21,36,35,26,15,100001,100001,100001,33,100001,100001,100001,8}},
        {"example 2", {0,100001,1}, {1,100001,1}},
        {"small balanced BST", {2,1,3}, {5,6,3}},
        {"single node", {1}, {1}},
        {"right-skewed BST", {1,100001,2,100001,3}, {6,100001,5,100001,3}},
    };

    for (int t = 0; t < 5; t++) {
        TreeNode *root = from_list(tests[t].input);
        TreeNode *expected = from_list(tests[t].expected);
        root = convertBST(root);
        if (trees_equal(root, expected)) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tests[t].label);
        }
        free_tree(root);
        free_tree(expected);
    }

    {
        TreeNode *root = convertBST(nullptr);
        if (!root) { passed++; printf("  Test 6 (empty tree): PASS\n"); }
        else { printf("  Test 6 (empty tree): FAIL\n"); }
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
