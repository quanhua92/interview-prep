/*
 * P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/most-frequent-subtree-sum/
 * Topics: Hash Table, Tree, Depth-First Search, Binary Tree
 * 
 * Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
 * The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
 * Example 1:
 *     Input: root = [5,2,-3]
 *     Output: [2,-3,4]
 * 
 * Example 2:
 *     Input: root = [5,2,-5]
 *     Output: [2]
 * 
 * Constraints:
 *     - The number of nodes in the tree is in the range [1, 104].
 *     - -105 <= Node.val <= 105
 * 
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
 */
#include "cpptest.h"
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(v), left(l), right(r) {}
};

static TreeNode* from_list(const std::vector<int>& vals) {
    /* TODO: Implement */
    return 0;
}

static void free_tree(TreeNode *root) {
    /* TODO: Implement */
    return 0;
}

static int subtree_sum(TreeNode *node, std::unordered_map<int, int>& freq) {
    /* TODO: Implement */
    return 0;
}

static std::vector<int> findFrequentTreeSum(TreeNode *root) {
    /* TODO: Implement */
    return 0;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  508. Most Frequent Subtree Sum\n");
    printf("============================================================\n");

    int passed = 0;

    struct TC { const char *label; std::vector<int> vals; std::vector<int> expected; };
    TC tests[] = {
        {"example 1", {5, 2, -3}, {-3, 2, 4}},
        {"example 2", {5, 2, -5}, {2}},
        {"single node", {1}, {1}},
        {"balanced tree", {1, 2, 3}, {2, 3, 6}},
        {"all negative values", {-1, -2, -3}, {-6, -3, -2}},
    };

    for (int t = 0; t < 5; t++) {
        TreeNode *root = from_list(tests[t].vals);
        std::vector<int> got = findFrequentTreeSum(root);
        if (got == tests[t].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
        } else {
            printf("  Test %d (%s): FAIL\n    Expected: ", t + 1, tests[t].label);
            print_arr(tests[t].expected); printf("\n    Got:      "); print_arr(got); printf("\n");
        }
        free_tree(root);
    }

    printf("\n  %d/5 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 5 ? 0 : 1;
}
