/**
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

function solve(input) {
  const vals = input.vals;
  if (!vals || vals.length === 0) return [];

  const root = buildTree(vals);
  const serialized = [];
  const queue = [root];
  while (queue.length > 0) {
    const node = queue.shift();
    if (node) {
      serialized.push(node.val);
      if (node.left || node.right) {
        queue.push(node.left);
        queue.push(node.right);
      }
    } else {
      serialized.push(null);
    }
  }
  while (serialized.length > 0 && serialized[serialized.length - 1] === null) {
    serialized.pop();
  }
  return serialized;
}

// --- tests ---
const tests = [
  { label: "example 1", input: { vals: [2, 1, 3] }, expected: [2, 1, 3] },
  { label: "empty tree", input: { vals: [] }, expected: [] },
  { label: "single node", input: { vals: [1] }, expected: [1] },
  { label: "bst with left subtree", input: { vals: [3, 1, 4, null, 2] }, expected: [3, 1, 4, null, 2] },
  { label: "balanced bst 3 levels", input: { vals: [5, 3, 8, 1, 4, 7, 9] }, expected: [5, 3, 8, 1, 4, 7, 9] },
  { label: "complete bst", input: { vals: [4, 2, 5, 1, 3] }, expected: [4, 2, 5, 1, 3] },
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
