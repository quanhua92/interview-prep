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
 *     - The number of nodes in the tree is in the range [1, 104].
 *     - -231 <= Node.val <= 231 - 1
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


#include "cpptest.h"
#include <climits>
#include <queue>

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
        TreeNode *node = q.front();
        q.pop();
        if (i < vals.size()) {
            if (vals[i] != NULL_VAL) {
                node->left = new TreeNode(vals[i]);
                q.push(node->left);
            }
            i++;
        }
        if (i < vals.size()) {
            if (vals[i] != NULL_VAL) {
                node->right = new TreeNode(vals[i]);
                q.push(node->right);
            }
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

static int findBottomLeftValue(TreeNode *root) {
    queue<TreeNode *> q;
    q.push(root);
    int result = root->val;
    while (!q.empty()) {
        int sz = (int)q.size();
        result = q.front()->val;
        for (int j = 0; j < sz; j++) {
            TreeNode *node = q.front();
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}

int main() {
    (void)print_arr;
    struct TC {
        string label;
        vector<int> vals;
        int expected;
    };
    TC tests[] = {
        {"example 1", {2, 1, 3}, 1},
        {"example 2", {1, 2, 3, 4, NULL_VAL, 5, 6, NULL_VAL, NULL_VAL, 7}, 7},
        {"single node", {1}, 1},
        {"left child only", {1, 2}, 2},
        {"right child only", {1, NULL_VAL, 2}, 2},
        {"left skewed deep", {1, 2, NULL_VAL, 3, NULL_VAL, 4}, 4},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        TreeNode *root = build_tree(tests[i].vals);
        int got = findBottomLeftValue(root);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
        free_tree(root);
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
