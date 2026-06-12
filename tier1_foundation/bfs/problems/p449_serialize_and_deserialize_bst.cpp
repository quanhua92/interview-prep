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
#include <cstdlib>
#include <queue>
#include <climits>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

using namespace std;

const int NULL_VAL = INT_MIN;

/* =====================================================================
 * Core Data Structure
 * ===================================================================== */

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* =====================================================================
 * Codec Class (Using Compact BST Boundaries)
 * ===================================================================== */

class Codec {
public:
    vector<int> serialize(TreeNode *root) {
        abort();
    }

    TreeNode *deserialize(const vector<int> &data) {
        abort();
    }
};

/* =====================================================================
 * Environment Utilities
 * ===================================================================== */

static void free_tree(TreeNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

static TreeNode *build_tree_from_list(const vector<int> &vals) {
    if (vals.empty() || vals[0] == NULL_VAL) return nullptr;
    TreeNode *root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
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

static vector<int> convert_tree_to_list(TreeNode *root) {
    if (!root) return {};
    vector<int> result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front(); q.pop();
        if (node) {
            result.push_back(node->val);
            q.push(node->left);
            q.push(node->right);
        } else {
            result.push_back(NULL_VAL);
        }
    }
    while (!result.empty() && result.back() == NULL_VAL) result.pop_back();
    return result;
}

/* =====================================================================
 * Solve
 * ===================================================================== */

static TreeNode *solve(TreeNode *root) {
    Codec codec;
    auto data = codec.serialize(root);
    return codec.deserialize(data);
}

/* =====================================================================
 * Main
 * ===================================================================== */

int main(void)
{
    int n = read_int();
    if (n == 0) return 0;
    string line = read_line();
    vector<int> vals;
    vals.reserve(n);
    istringstream iss(line);
    string tok;
    for (int i = 0; i < n && iss >> tok; i++) {
        if (tok == "null") vals.push_back(NULL_VAL);
        else vals.push_back(stoi(tok));
    }

    TreeNode *tree = build_tree_from_list(vals);
    TreeNode *result = solve(tree);
    vector<int> out = convert_tree_to_list(result);

    ostringstream oss;
    for (size_t j = 0; j < out.size(); j++) {
        if (j > 0) oss << " ";
        if (out[j] == NULL_VAL) oss << "null";
        else oss << out[j];
    }
    write_string(oss.str());

    free_tree(tree);
    free_tree(result);
    return 0;
}
