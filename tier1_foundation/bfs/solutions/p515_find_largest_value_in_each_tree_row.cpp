/*
 * P515: Find Largest Value in Each Tree Row [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-largest-value-in-each-tree-row/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).
 * Example 1:
 *     Input: root = [1,3,2,5,3,null,9]
 *     Output: [1,3,9]
 *
 * Example 2:
 *     Input: root = [1,2,3]
 *     Output: [1,3]
 *
 * Constraints:
 *     - The number of nodes in the tree will be in the range [0, 104].
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
 *         def largestValues(self, root: Optional[TreeNode]) -> List[int]:
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

static vector<int> largestValues(TreeNode *root) {
    vector<int> result;
    if (!root) return result;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        int sz = (int)q.size();
        int max_val = INT_MIN;
        for (int j = 0; j < sz; j++) {
            TreeNode *node = q.front();
            q.pop();
            if (node->val > max_val) max_val = node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(max_val);
    }
    return result;
}

int main() {
    struct TC {
        string label;
        vector<int> vals;
        vector<int> expected;
    };
    TC tests[] = {
        {"example 1", {1, 3, 2, 5, 3, NULL_VAL, 9}, {1, 3, 9}},
        {"example 2", {1, 2, 3}, {1, 3}},
        {"empty tree", {}, {}},
        {"negative values", {-1, -2, -3, -4}, {-1, -2, -4}},
        {"left chain", {1, 2, NULL_VAL, 3}, {1, 2, 3}},
        {"single node", {5}, {5}},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        TreeNode *root = build_tree(tests[i].vals);
        vector<int> got = largestValues(root);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
            printf("    Expected: ");
            print_arr(tests[i].expected);
            printf("\n    Got:      ");
            print_arr(got);
            printf("\n");
        }
        free_tree(root);
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
