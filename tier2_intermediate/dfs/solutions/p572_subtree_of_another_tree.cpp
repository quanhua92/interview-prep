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
#include <queue>
#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

static TreeNode *from_list(const std::vector<int>& vals) {
    if (vals.empty() || vals[0] == 2147483647) return nullptr;
    TreeNode *root = new TreeNode(vals[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode *node = q.front(); q.pop();
        if (i < vals.size()) {
            if (vals[i] != 2147483647) { node->left = new TreeNode(vals[i]); q.push(node->left); }
            i++;
        }
        if (i < vals.size()) {
            if (vals[i] != 2147483647) { node->right = new TreeNode(vals[i]); q.push(node->right); }
            i++;
        }
    }
    return root;
}

static bool is_same(TreeNode *a, TreeNode *b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->val == b->val && is_same(a->left, b->left) && is_same(a->right, b->right);
}

static bool isSubtree(TreeNode *root, TreeNode *subRoot) {
    if (!subRoot) return true;
    if (!root) return false;
    if (is_same(root, subRoot)) return true;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

int main() {
    auto root_line = read_line();
    auto sub_line = read_line();
    auto parse = [](const std::string& s) -> std::vector<int> {
        std::vector<int> v;
        size_t pos = 0;
        while (pos < s.size()) {
            while (pos < s.size() && s[pos] == ' ') pos++;
            size_t end = s.find(' ', pos);
            if (end == std::string::npos) end = s.size();
            std::string tok = s.substr(pos, end - pos);
            pos = end;
            v.push_back(tok == "null" ? 2147483647 : std::stoi(tok));
        }
        return v;
    };
    TreeNode *root = from_list(parse(root_line));
    TreeNode *sub = from_list(parse(sub_line));
    write_bool(isSubtree(root, sub));
    return 0;
}
