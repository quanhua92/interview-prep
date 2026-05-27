/*
 * P102: Binary Tree Level Order Traversal (Medium)
 * https://leetcode.com/problems/binary-tree-level-order-traversal/
 * Topics: Tree, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).
 *
 * Example 1:
 *     Input: root = [3,9,20,null,null,15,7]
 *     Output: [[3],[9,20],[15,7]]
 *
 * Example 2:
 *     Input: root = [1]
 *     Output: [[1]]
 *
 * Example 3:
 *     Input: root = []
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 2000].
 *     - -1000 <= Node.val <= 1000
 *
 * Hints:
 *     - Use a queue to perform BFS.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
 *
 * Hint: Use a queue to process nodes level by level.
 */

#include "io.h"
#include <queue>
#include <climits>
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

static vector<vector<int>> solve(TreeNode *root) {
    abort();
}

int main(void)
{
    int n = read_int();
    if (n == 0) return 0;
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
    vector<vector<int>> result = solve(root);
    for (auto &row : result) write_ints(row);
    free_tree(root);
    return 0;
}
