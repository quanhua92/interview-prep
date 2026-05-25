/**
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

function buildTree(arr) {
  if (arr.length === 0) return null;
  const root = { val: arr[0], left: null, right: null };
  const queue = [root];
  let i = 1;
  while (queue.length > 0 && i < arr.length) {
    const node = queue.shift();
    if (i < arr.length && arr[i] !== null) {
      node.left = { val: arr[i], left: null, right: null };
      queue.push(node.left);
    }
    i++;
    if (i < arr.length && arr[i] !== null) {
      node.right = { val: arr[i], left: null, right: null };
      queue.push(node.right);
    }
    i++;
  }
  return root;
}

function treeToList(root) {
  if (!root) return [];
  const result = [];
  const queue = [root];
  while (queue.length > 0) {
    const node = queue.shift();
    if (node) {
      result.push(node.val);
      queue.push(node.left);
      queue.push(node.right);
    } else {
      result.push(null);
    }
  }
  while (result.length > 0 && result[result.length - 1] === null) {
    result.pop();
  }
  return result;
}

function deleteNode(root, key) {
  if (!root) return null;
  if (key < root.val) {
    root.left = deleteNode(root.left, key);
  } else if (key > root.val) {
    root.right = deleteNode(root.right, key);
  } else {
    if (!root.left) return root.right;
    if (!root.right) return root.left;
    let minNode = root.right;
    while (minNode.left) {
      minNode = minNode.left;
    }
    root.val = minNode.val;
    root.right = deleteNode(root.right, minNode.val);
  }
  return root;
}

function solve(root, key) {
  const result = deleteNode(root, key);
  return treeToList(result);
}

const tests = [
  { label: "example 1", input: [buildTree([5, 3, 6, 2, 4, null, 7]), 3], expected: [5, 4, 6, 2, null, null, 7] },
  { label: "example 2", input: [buildTree([5, 3, 6, 2, 4, null, 7]), 0], expected: [5, 3, 6, 2, 4, null, 7] },
  { label: "example 3", input: [buildTree([]), 0], expected: [] },
  { label: "delete single node root", input: [buildTree([5]), 5], expected: [] },
  { label: "delete root with two children", input: [buildTree([3, 1, 4]), 3], expected: [4, 1] },
  { label: "delete left leaf", input: [buildTree([2, 1, 3]), 1], expected: [2, null, 3] },
  { label: "delete node with only left child", input: [buildTree([5, 3, null, 2, null, 1]), 3], expected: [5, 2, null, 1] },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
