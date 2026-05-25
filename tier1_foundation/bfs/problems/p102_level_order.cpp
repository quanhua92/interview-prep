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
#include "cpptest.h"
#include <queue>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

static const int NULL_VAL = INT_MIN;

static TreeNode *build_tree(const vector<int> &vals) {
    /* TODO: Implement */
    return 0;
}

static void free_tree(TreeNode *root) {
    /* TODO: Implement */
    return 0;
}

static vector<vector<int>> levelOrder(TreeNode *root) {
    /* TODO: Implement */
    return 0;
}

int main() {
    (void)print_arr;
    struct TC {
        string label;
        vector<int> vals;
        vector<vector<int>> expected;
    };
    TC tests[] = {
        {"example 1", {3,9,20,NULL_VAL,NULL_VAL,15,7}, {{3},{9,20},{15,7}}},
        {"example 2", {1}, {{1}}},
        {"empty", {}, {}},
        {"right child only", {1,NULL_VAL,2}, {{1},{2}}},
        {"left child only", {1,2}, {{1},{2}}},
        {"full binary tree depth 2", {5,3,8,1,4,7,9}, {{5},{3,8},{1,4,7,9}}},
        {"negative values", {-1,-2,-3}, {{-1},{-2,-3}}},
        {"all same value", {1,1,1,1,1,1,1}, {{1},{1,1},{1,1,1,1}}},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        TreeNode *root = build_tree(tests[i].vals);
        vector<vector<int>> got = levelOrder(root);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
        }
        free_tree(root);
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
