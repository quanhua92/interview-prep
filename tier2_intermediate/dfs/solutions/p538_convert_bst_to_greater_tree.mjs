/**
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
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
 *     class Solution:
 *         def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
 */

class TreeNode {
  constructor(val, left, right) {
    this.val = val === undefined ? 0 : val;
    this.left = left === undefined ? null : left;
    this.right = right === undefined ? null : right;
  }

  static buildTree(arr) {
    if (arr === null || arr.length === 0) return null;
    const root = new TreeNode(arr[0]);
    const queue = [root];
    let i = 1;
    while (i < arr.length && queue.length > 0) {
      const node = queue.shift();
      if (i < arr.length && arr[i] !== null) {
        node.left = new TreeNode(arr[i]);
        queue.push(node.left);
      }
      i++;
      if (i < arr.length && arr[i] !== null) {
        node.right = new TreeNode(arr[i]);
        queue.push(node.right);
      }
      i++;
    }
    return root;
  }

  toList() {
    const result = [];
    const queue = [this];
    while (queue.length > 0) {
      const node = queue.shift();
      result.push(node ? node.val : null);
      if (node) {
        queue.push(node.left);
        queue.push(node.right);
      }
    }
    while (result.length > 0 && result[result.length - 1] === null) {
      result.pop();
    }
    return result;
  }
}

function solve(root) {
  let total = 0;

  function reverseInorder(node) {
    if (!node) return;
    reverseInorder(node.right);
    total += node.val;
    node.val = total;
    reverseInorder(node.left);
  }

  reverseInorder(root);
  return root;
}

function treeToList(root) {
  if (root === null) return null;
  return root.toList();
}

const tests = [
  {
    label: "example 1",
    input: [4, 1, 6, 0, 2, 5, 7, null, null, null, 3, null, null, null, 8],
    expected: [30, 36, 21, 36, 35, 26, 15, null, null, null, 33, null, null, null, 8],
  },
  { label: "example 2", input: [0, null, 1], expected: [1, null, 1] },
  { label: "small balanced BST", input: [2, 1, 3], expected: [5, 6, 3] },
  { label: "single node", input: [1], expected: [1] },
  { label: "right-skewed BST", input: [1, null, 2, null, 3], expected: [6, null, 5, null, 3] },
  { label: "empty tree", input: null, expected: null },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = treeToList(solve(TreeNode.buildTree(t.input)));
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
