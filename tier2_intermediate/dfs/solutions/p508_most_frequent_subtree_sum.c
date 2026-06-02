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
 *     - The number of nodes in the tree is in the range [1, 10^4].
 *     - -10^5 <= Node.val <= 10^5
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

#include "io.h"
#include <stdlib.h>
#include <string.h>

#define NL 2147483647

typedef struct TreeNode { int val; struct TreeNode *left, *right; } TreeNode;

static TreeNode *make_node(int val, TreeNode *left, TreeNode *right) {
    TreeNode *n = malloc(sizeof(TreeNode));
    n->val = val; n->left = left; n->right = right;
    return n;
}

static TreeNode *from_list(int *vals, int n, int i) {
    if (i >= n || vals[i] == NL) return NULL;
    TreeNode *root = make_node(vals[i], NULL, NULL);
    root->left = from_list(vals, n, 2 * i + 1);
    root->right = from_list(vals, n, 2 * i + 2);
    return root;
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

static int subtree_sum(TreeNode *node) {
    if (!node) return 0;
    int s = node->val + subtree_sum(node->left) + subtree_sum(node->right);
    map_add(s);
    return s;
}

int main(void) {
    char *line = read_line();
    int vals[10000], n = 0;
    char *tok = strtok(line, " ");
    while (tok) {
        if (strcmp(tok, "null") == 0) vals[n++] = NL;
        else vals[n++] = atoi(tok);
        tok = strtok(NULL, " ");
    }
    TreeNode *root = from_list(vals, n, 0);
    map_count = 0;
    subtree_sum(root);
    int max_freq = 0;
    for (int i = 0; i < map_count; i++)
        if (map_vals[i] > max_freq) max_freq = map_vals[i];
    int *result = malloc(map_count * sizeof(int));
    int rn = 0;
    for (int i = 0; i < map_count; i++)
        if (map_vals[i] == max_freq) result[rn++] = map_keys[i];
    for (int i = 0; i < rn - 1; i++)
        for (int j = i + 1; j < rn; j++)
            if (result[i] > result[j]) { int t = result[i]; result[i] = result[j]; result[j] = t; }
    write_ints(result, rn);
    free(result);
    free(line);
    return 0;
}
