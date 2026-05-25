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
    abort();
}

static void free_tree(TreeNode *root) {
    abort();
}

static vector<int> largestValues(TreeNode *root) {
    abort();
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
