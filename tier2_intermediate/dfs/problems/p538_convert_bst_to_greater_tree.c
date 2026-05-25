/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 * 
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 * Example 2:
 * Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
 * Example 1:
 *     Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
 *     Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
 * 
 * Example 2:
 *     Input: root = [0,null,1]
 *     Output: [1,null,1]
 * 
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - -104 <= Node.val <= 104
 *     - All the values in the tree are unique.
 *     - root is guaranteed to be a valid binary search tree.
 * 
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
 */
#include "ctest.h"
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode* make_node(int val) {
    abort();
}

static struct TreeNode* from_list(int *vals, int n) {
    abort();
}

static void free_tree(struct TreeNode *root) {
    abort();
}

static int trees_equal(struct TreeNode *a, struct TreeNode *b) {
    abort();
}

static int gtotal;

static void reverse_inorder(struct TreeNode *node) {
    abort();
}

static struct TreeNode* convertBST(struct TreeNode *root) {
    abort();
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  538. Convert BST to Greater Tree\n");
    printf("============================================================\n");

    int passed = 0;

    {
        int input[] = {4,1,6,0,2,5,7,100001,100001,100001,3,100001,100001,100001,8};
        int exp[] = {30,36,21,36,35,26,15,100001,100001,100001,33,100001,100001,100001,8};
        struct TreeNode *root = from_list(input, 15);
        struct TreeNode *expected = from_list(exp, 15);
        root = convertBST(root);
        if (trees_equal(root, expected)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
        free_tree(root);
        free_tree(expected);
    }
    {
        int input[] = {0,100001,1};
        int exp[] = {1,100001,1};
        struct TreeNode *root = from_list(input, 3);
        struct TreeNode *expected = from_list(exp, 3);
        root = convertBST(root);
        if (trees_equal(root, expected)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
        free_tree(root);
        free_tree(expected);
    }
    {
        int input[] = {2,1,3};
        int exp[] = {5,6,3};
        struct TreeNode *root = from_list(input, 3);
        struct TreeNode *expected = from_list(exp, 3);
        root = convertBST(root);
        if (trees_equal(root, expected)) { passed++; printf("  Test 3 (small balanced BST): PASS\n"); }
        else { printf("  Test 3 (small balanced BST): FAIL\n"); }
        free_tree(root);
        free_tree(expected);
    }
    {
        int input[] = {1};
        int exp[] = {1};
        struct TreeNode *root = from_list(input, 1);
        struct TreeNode *expected = from_list(exp, 1);
        root = convertBST(root);
        if (trees_equal(root, expected)) { passed++; printf("  Test 4 (single node): PASS\n"); }
        else { printf("  Test 4 (single node): FAIL\n"); }
        free_tree(root);
        free_tree(expected);
    }
    {
        int input[] = {1,100001,2,100001,3};
        int exp[] = {6,100001,5,100001,3};
        struct TreeNode *root = from_list(input, 5);
        struct TreeNode *expected = from_list(exp, 5);
        root = convertBST(root);
        if (trees_equal(root, expected)) { passed++; printf("  Test 5 (right-skewed BST): PASS\n"); }
        else { printf("  Test 5 (right-skewed BST): FAIL\n"); }
        free_tree(root);
        free_tree(expected);
    }
    {
        struct TreeNode *root = convertBST(NULL);
        if (!root) { passed++; printf("  Test 6 (empty tree): PASS\n"); }
        else { printf("  Test 6 (empty tree): FAIL\n"); }
    }

    printf("\n  %d/6 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 6 ? 0 : 1;
}
