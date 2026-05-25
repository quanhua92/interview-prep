/**
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
 *     class Solution:
 *         def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
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
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [5, 2, -3], expected: [-3, 2, 4] },
  { label: "example 2", input: [5, 2, -5], expected: [2] },
  { label: "single node", input: [1], expected: [1] },
  { label: "balanced tree", input: [1, 2, 3], expected: [2, 3, 6] },
  { label: "all negative values", input: [-1, -2, -3], expected: [-6, -3, -2] },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(TreeNode.buildTree(t.input));
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
