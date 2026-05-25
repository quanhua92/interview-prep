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
    struct TreeNode *n = malloc(sizeof(*n));
    n->val = val; n->left = left; n->right = right;
    return n;
}

static struct TreeNode* from_list(int *vals, int n, int i) {
    if (i >= n || vals[i] == 100001) return NULL;
    struct TreeNode *root = make_node(vals[i], NULL, NULL);
    root->left = from_list(vals, n, 2 * i + 1);
    root->right = from_list(vals, n, 2 * i + 2);
    return root;
}

static void free_tree(struct TreeNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

#define MAP_SIZE 20001
static int map_keys[MAP_SIZE], map_vals[MAP_SIZE], map_count;

static void map_add(int key) {
    for (int i = 0; i < map_count; i++) {
        if (map_keys[i] == key) { map_vals[i]++; return; }
    }
    map_keys[map_count] = key;
    map_vals[map_count] = 1;
    map_count++;
}

static int subtree_sum(struct TreeNode *node) {
    if (!node) return 0;
    int s = node->val + subtree_sum(node->left) + subtree_sum(node->right);
    map_add(s);
    return s;
}

static int *findFrequentTreeSum(struct TreeNode *root, int *returnSize) {
    map_count = 0;
    subtree_sum(root);
    int max_freq = 0;
    for (int i = 0; i < map_count; i++) {
        if (map_vals[i] > max_freq) max_freq = map_vals[i];
    }
    int *result = malloc(map_count * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < map_count; i++) {
        if (map_vals[i] == max_freq) result[(*returnSize)++] = map_keys[i];
    }
    return result;
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
