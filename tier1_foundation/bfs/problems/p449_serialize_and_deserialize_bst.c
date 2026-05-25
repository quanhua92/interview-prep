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
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - 0 <= Node.val <= 104
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
#include "ctest.h"
#include <limits.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

#define NULL_VAL INT_MIN

static TreeNode *make_node(int val) {
    abort();
}

static void free_tree(TreeNode *root) {
    abort();
}

static int *solve(const int *vals, int vals_n, int *returnSize) {
    abort();
}

typedef struct {
    const char *label;
    int vals[20];
    int vals_n;
    int expected[20];
    int expected_n;
} TC;

int main(void) {
    TC tests[] = {
        {"example 1", {2,1,3}, 3, {2,1,3}, 3},
        {"empty tree", {0}, 0, {0}, 0},
        {"single node", {1}, 1, {1}, 1},
        {"bst with left subtree", {3,1,4,NULL_VAL,2}, 5, {3,1,4,NULL_VAL,2}, 5},
        {"balanced bst 3 levels", {5,3,8,1,4,7,9}, 7, {5,3,8,1,4,7,9}, 7},
        {"complete bst", {4,2,5,1,3}, 5, {4,2,5,1,3}, 5},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        int got_size = 0;
        int *got = solve(tests[i].vals, tests[i].vals_n, &got_size);
        int ok;
        if (tests[i].expected_n == 0) {
            ok = (got_size == 0);
        } else {
            ok = th_arr_eq(got, got_size, tests[i].expected, tests[i].expected_n);
        }
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: ");
            th_print_arr(tests[i].expected, tests[i].expected_n);
            printf("\n    Got:      ");
            if (got) th_print_arr(got, got_size);
            else printf("NULL");
            printf("\n");
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
