/*
 * P513: Find Bottom Left Tree Value [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-bottom-left-tree-value/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return the leftmost value in the last row of the tree.
 * Example 1:
 *     Input: root = [2,1,3]
 *     Output: 1
 *
 * Example 2:
 *     Input: root = [1,2,3,4,null,5,6,null,null,7]
 *     Output: 7
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [1, 10^4].
 *     - -2^31 <= Node.val <= 2^31 - 1
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
 */

#include "io.h"
#include <cstdlib>
#include <climits>
#include <queue>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

static const int NULL_VAL = INT_MIN;

static TreeNode *build_tree(const vector<int> &vals) {
    if (vals.empty() || vals[0] == NULL_VAL) return nullptr;
    TreeNode *root = new TreeNode(vals[0]);
    queue<TreeNode *> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode *node = q.front(); q.pop();
        if (i < vals.size()) {
            if (vals[i] != NULL_VAL) { node->left = new TreeNode(vals[i]); q.push(node->left); }
            i++;
        }
        if (i < vals.size()) {
            if (vals[i] != NULL_VAL) { node->right = new TreeNode(vals[i]); q.push(node->right); }
            i++;
        }
    }
    return root;
}

static void free_tree(TreeNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

static int solve(TreeNode *root) {
    queue<TreeNode *> q;
    q.push(root);
    int result = root->val;
    while (!q.empty()) {
        int sz = (int)q.size();
        result = q.front()->val;
        for (int j = 0; j < sz; j++) {
            TreeNode *node = q.front(); q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}

int main(void)
{
    int n = read_int();
    string line = read_line();
    vector<int> vals;
    vals.reserve(n);
    size_t pos = 0;
    for (int i = 0; i < n; i++) {
        size_t next = line.find(' ', pos);
        string tok = (next == string::npos) ? line.substr(pos) : line.substr(pos, next - pos);
        if (tok == "null") vals.push_back(NULL_VAL);
        else vals.push_back(stoi(tok));
        pos = (next == string::npos) ? string::npos : next + 1;
        if (pos == string::npos) break;
    }
    TreeNode *root = build_tree(vals);
    write_int(solve(root));
    free_tree(root);
    return 0;
}
