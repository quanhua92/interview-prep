/*
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
 *
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
 * Basically, the deletion can be divided into two stages:
 * Example 3:
 * Follow up: Could you solve it with time complexity O(height of tree)?
 * Example 1:
 *     Input: root = [5,3,6,2,4,null,7], key = 3
 *     Output: [5,4,6,2,null,null,7]
 *     Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
 *     One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
 *     Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.
 *
 * Example 2:
 *     Input: root = [5,3,6,2,4,null,7], key = 0
 *     Output: [5,3,6,2,4,null,7]
 *     Explanation: The tree does not contain a node with value = 0.
 *
 * Example 3:
 *     Input: root = [], key = 0
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 104].
 *     - -105 <= Node.val <= 105
 *     - Each node has a unique value.
 *     - root is a valid binary search tree.
 *     - -105 <= key <= 105
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct QNode { struct TreeNode *node; struct QNode *next; } QNode;

static void enqueue(QNode **front, QNode **back, TreeNode *n)
{
    QNode *q = (QNode *)malloc(sizeof(QNode));
    q->node = n; q->next = NULL;
    if (*back) (*back)->next = q; else *front = q;
    *back = q;
}

static TreeNode *dequeue(QNode **front, QNode **back)
{
    if (!*front) return NULL;
    QNode *q = *front;
    TreeNode *n = q->node;
    *front = q->next;
    if (!*front) *back = NULL;
    free(q);
    return n;
}

static void free_q(QNode **front, QNode **back)
{
    while (*front) dequeue(front, back);
}

static TreeNode *make_node(int val)
{
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    n->val = val; n->left = n->right = NULL;
    return n;
}

static TreeNode *insert(TreeNode *root, int val)
{
    if (!root) return make_node(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

static TreeNode *deleteNode(TreeNode *root, int key)
{
    if (!root) return NULL;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) { TreeNode *tmp = root->right; free(root); return tmp; }
        if (!root->right) { TreeNode *tmp = root->left; free(root); return tmp; }
        TreeNode *mn = root->right;
        while (mn->left) mn = mn->left;
        root->val = mn->val;
        root->right = deleteNode(root->right, mn->val);
    }
    return root;
}

static int tree_to_bfs(TreeNode *root, int *arr, int max_n)
{
    if (!root) { arr[0] = 0x7FFFFFFF; return 1; }
    QNode *front = NULL, *back = NULL;
    enqueue(&front, &back, root);
    int sz = 0;
    while (front && sz < max_n) {
        TreeNode *cur = dequeue(&front, &back);
        if (cur) {
            arr[sz++] = cur->val;
            enqueue(&front, &back, cur->left);
            enqueue(&front, &back, cur->right);
        } else {
            arr[sz++] = 0x7FFFFFFF;
        }
    }
    free_q(&front, &back);
    while (sz > 1 && arr[sz - 1] == 0x7FFFFFFF) sz--;
    return sz;
}

static void free_tree(TreeNode *root)
{
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

static TreeNode *build_from_list(const int *vals, int n)
{
    TreeNode *root = NULL;
    for (int i = 0; i < n; i++)
        if (vals[i] != 0x7FFFFFFF) root = insert(root, vals[i]);
    return root;
}

#define NL 0x7FFFFFFF

int main(void)
{
    struct {
        const char *label;
        int input[10]; int input_n; int key;
        int expected[10]; int expected_n;
        int pass;
    } tests[] = {
        { "example 1", {5,3,6,2,4,NL,7}, 7, 3, {5,4,6,2,NL,NL,7}, 7, 0 },
        { "example 2", {5,3,6,2,4,NL,7}, 7, 0, {5,3,6,2,4,NL,7}, 7, 0 },
        { "example 3", {NL}, 1, 0, {NL}, 1, 0 },
        { "delete single node root", {5}, 1, 5, {NL}, 1, 0 },
        { "delete root with two children", {3,1,4}, 3, 3, {4,1}, 2, 0 },
        { "delete left leaf", {2,1,3}, 3, 1, {2,NL,3}, 3, 0 },
        { "delete node with only left child", {5,3,NL,2,NL,1}, 6, 3, {5,2,NL,1}, 4, 0 },
    };
    int tn = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    for (int i = 0; i < tn; i++) {
        TreeNode *root = build_from_list(tests[i].input, tests[i].input_n);
        root = deleteNode(root, tests[i].key);
        int got[30] = {0};
        int got_n = tree_to_bfs(root, got, 30);

        int min_n = got_n < tests[i].expected_n ? got_n : tests[i].expected_n;
        tests[i].pass = 1;
        if (got_n != tests[i].expected_n) tests[i].pass = 0;
        else {
            for (int j = 0; j < min_n && tests[i].pass; j++)
                if (got[j] != tests[i].expected[j]) tests[i].pass = 0;
        }
        if (tests[i].pass) passed++;
        free_tree(root);
    }

    printf("\n============================================================\n");
    printf("  450. Delete Node in a BST\n");
    printf("============================================================\n");
    for (int i = 0; i < tn; i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, tn);
    printf("============================================================\n");
    return passed == tn ? 0 : 1;
}
