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


#include "ctest.h"
#include <limits.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

#define NULL_VAL INT_MIN

static TreeNode *make_node(int val) {
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

static TreeNode *build_tree(const int *vals, int n) {
    if (n == 0 || vals[0] == NULL_VAL) return NULL;
    TreeNode *root = make_node(vals[0]);
    TreeNode *queue[10000];
    int front = 0, back = 0;
    queue[back++] = root;
    int i = 1;
    while (front < back && i < n) {
        TreeNode *node = queue[front++];
        if (i < n) {
            if (vals[i] != NULL_VAL) {
                node->left = make_node(vals[i]);
                queue[back++] = node->left;
            }
            i++;
        }
        if (i < n) {
            if (vals[i] != NULL_VAL) {
                node->right = make_node(vals[i]);
                queue[back++] = node->right;
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
    free(root);
}

static int *findLargestValues(TreeNode *root, int *returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }
    int *result = (int *)malloc(sizeof(int) * 10000);
    int count = 0;
    TreeNode *queue[10000];
    int front = 0, back = 0;
    queue[back++] = root;
    while (front < back) {
        int sz = back - front;
        int max_val = INT_MIN;
        for (int j = 0; j < sz; j++) {
            TreeNode *node = queue[front++];
            if (node->val > max_val) max_val = node->val;
            if (node->left) queue[back++] = node->left;
            if (node->right) queue[back++] = node->right;
        }
        result[count++] = max_val;
    }
    *returnSize = count;
    return result;
}

typedef struct {
    const char *label;
    int vals[20];
    int n;
    int expected[20];
    int expected_n;
} TC;

int main(void) {
    TC tests[] = {
        {"example 1", {1, 3, 2, 5, 3, NULL_VAL, 9}, 7, {1, 3, 9}, 3},
        {"example 2", {1, 2, 3}, 3, {1, 3}, 2},
        {"empty tree", {0}, 0, {0}, 0},
        {"negative values", {-1, -2, -3, -4}, 4, {-1, -2, -4}, 3},
        {"left chain", {1, 2, NULL_VAL, 3}, 4, {1, 2, 3}, 3},
        {"single node", {5}, 1, {5}, 1},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        TreeNode *root = build_tree(tests[i].vals, tests[i].n);
        int got_size = 0;
        int *got = findLargestValues(root, &got_size);
        int eq = (got_size == 0 && tests[i].expected_n == 0) ||
                 th_arr_eq(got, got_size, tests[i].expected, tests[i].expected_n);
        if (eq) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: ");
            th_print_arr(tests[i].expected, tests[i].expected_n);
            printf("\n    Got:      ");
            th_print_arr(got, got_size);
            printf("\n");
        }
        free(got);
        free_tree(root);
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
