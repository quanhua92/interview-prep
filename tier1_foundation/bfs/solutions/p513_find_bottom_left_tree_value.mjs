/**
 * P513: Find Bottom Left Tree Value [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-bottom-left-tree-value/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 *
 * Given the root of a binary tree, return the leftmost value in the last row of the tree.
 * Example 1:
 *     Input: root = [2,1,3]
 *     Output: 1
 *
 * Example 2:
 *     Input: root = [1,2,3,4,null,5,6,null,null,7]
 *     Output: 7
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [1, 104].
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
 *         def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
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

function findBottomLeftValue(root) {
  const queue = [root];
  let result = 0;
  while (queue.length > 0) {
    const levelSize = queue.length;
    result = queue[0].val;
    for (let i = 0; i < levelSize; i++) {
      const node = queue.shift();
      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
  }
  return result;
}

function solve(input) {
  return findBottomLeftValue(input);
}

// --- tests ---
const tests = [
  { label: "example 1", input: buildTree([2, 1, 3]), expected: 1 },
  { label: "example 2", input: buildTree([1, 2, 3, 4, null, 5, 6, null, null, 7]), expected: 7 },
  { label: "single node", input: buildTree([1]), expected: 1 },
  { label: "left child only", input: buildTree([1, 2]), expected: 2 },
  { label: "right child only", input: buildTree([1, null, 2]), expected: 2 },
  { label: "left skewed deep", input: buildTree([1, 2, null, 3, null, 4]), expected: 4 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input);
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
