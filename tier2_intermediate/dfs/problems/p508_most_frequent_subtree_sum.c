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
#include "ctest.h"
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode* make_node(int val, struct TreeNode *left, struct TreeNode *right) {
    abort();
}

static struct TreeNode* from_list(int *vals, int n, int i) {
    abort();
}

static void free_tree(struct TreeNode *root) {
    abort();
}

#define MAP_SIZE 20001
static int map_keys[MAP_SIZE], map_vals[MAP_SIZE], map_count;

static void map_add(int key) {
    abort();
}

static int subtree_sum(struct TreeNode *node) {
    abort();
}

static int *findFrequentTreeSum(struct TreeNode *root, int *returnSize) {
    abort();
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  508. Most Frequent Subtree Sum\n");
    printf("============================================================\n");

    int passed = 0;

    struct { const char *label; int vals[3]; int n; int expected[3]; int exp_n; } tests[] = {
        {"example 1", {5, 2, -3}, 3, {2, -3, 4}, 3},
        {"example 2", {5, 2, -5}, 3, {2}, 1},
        {"single node", {1}, 1, {1}, 1},
        {"balanced tree", {1, 2, 3}, 3, {2, 3, 6}, 3},
        {"all negative values", {-1, -2, -3}, 3, {-6, -3, -2}, 3},
    };

    for (int t = 0; t < 5; t++) {
        struct TreeNode *root = from_list(tests[t].vals, tests[t].n, 0);
        int ret_size = 0;
        int *got = findFrequentTreeSum(root, &ret_size);
        if (ret_size == tests[t].exp_n) {
            int match = 1;
            char used[3] = {0};
            for (int i = 0; i < ret_size && match; i++) {
                int found = 0;
                for (int j = 0; j < ret_size; j++) {
                    if (!used[j] && got[i] == tests[t].expected[j]) { used[j] = 1; found = 1; break; }
                }
                if (!found) match = 0;
            }
            if (match) {
                passed++;
                printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
            } else {
                printf("  Test %d (%s): FAIL (content mismatch)\n", t + 1, tests[t].label);
            }
        } else {
            printf("  Test %d (%s): FAIL (size %d vs %d)\n", t + 1, tests[t].label, ret_size, tests[t].exp_n);
        }
        free(got);
        free_tree(root);
    }

    printf("\n  %d/5 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 5 ? 0 : 1;
}
