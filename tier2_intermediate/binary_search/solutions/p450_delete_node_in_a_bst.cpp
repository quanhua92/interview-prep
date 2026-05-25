/*
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
 *
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
 * Basically, the deletion can be divided into two stages:
 * Example 3:
 * Follow up: Could you solve it with time complexity O(height of tree)?
 * Example 1:
 *     Input: root = [5,3,6,2,4,null,7], key = 3
 *     Output: [5,4,6,2,null,null,7]
 *     Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
 *     One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
 *     Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.
 *
 * Example 2:
 *     Input: root = [5,3,6,2,4,null,7], key = 0
 *     Output: [5,3,6,2,4,null,7]
 *     Explanation: The tree does not contain a node with value = 0.
 *
 * Example 3:
 *     Input: root = [], key = 0
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - -105 <= Node.val <= 105
 *     - Each node has a unique value.
 *     - root is a valid binary search tree.
 *     - -105 <= key <= 105
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
 */


#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

static TreeNode *insert(TreeNode *root, int val)
{
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

static TreeNode *deleteNode(TreeNode *root, int key)
{
    if (!root) return nullptr;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) { auto *t = root->right; delete root; return t; }
        if (!root->right) { auto *t = root->left; delete root; return t; }
        TreeNode *mn = root->right;
        while (mn->left) mn = mn->left;
        root->val = mn->val;
        root->right = deleteNode(root->right, mn->val);
    }
    return root;
}

static std::vector<int> tree_to_bfs(TreeNode *root)
{
    const int NL = 0x7FFFFFFF;
    std::vector<int> result;
    if (!root) { result.push_back(NL); return result; }
    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *cur = q.front(); q.pop();
        if (cur) {
            result.push_back(cur->val);
            q.push(cur->left);
            q.push(cur->right);
        } else {
            result.push_back(NL);
        }
    }
    while ((int)result.size() > 1 && result.back() == NL) result.pop_back();
    return result;
}

static TreeNode *build_from_list(const std::vector<int> &vals)
{
    const int NL = 0x7FFFFFFF;
    TreeNode *root = nullptr;
    for (int v : vals) if (v != NL) root = insert(root, v);
    return root;
}

static void free_tree(TreeNode *root)
{
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

#define NL 0x7FFFFFFF

int main(void)
{
    struct Tc {
        const char *label;
        std::vector<int> input, expected;
        int key;
        bool pass;
    };
    std::vector<Tc> tests = {
        {"example 1", {5,3,6,2,4,NL,7}, {5,4,6,2,NL,NL,7}, 3, false},
        {"example 2", {5,3,6,2,4,NL,7}, {5,3,6,2,4,NL,7}, 0, false},
        {"example 3", {NL}, {NL}, 0, false},
        {"delete single node root", {5}, {NL}, 5, false},
        {"delete root with two children", {3,1,4}, {4,1}, 3, false},
        {"delete left leaf", {2,1,3}, {2,NL,3}, 1, false},
        {"delete node with only left child", {5,3,NL,2,NL,1}, {5,2,NL,1}, 3, false},
    };

    int passed = 0;
    for (auto &tc : tests) {
        TreeNode *root = build_from_list(tc.input);
        root = deleteNode(root, tc.key);
        std::vector<int> got = tree_to_bfs(root);
        tc.pass = (got == tc.expected);
        if (tc.pass) passed++;
        free_tree(root);
    }

    printf("\n============================================================\n");
    printf("  450. Delete Node in a BST\n");
    printf("============================================================\n");
    for (int i = 0; i < (int)tests.size(); i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n");
    return passed == (int)tests.size() ? 0 : 1;
}
