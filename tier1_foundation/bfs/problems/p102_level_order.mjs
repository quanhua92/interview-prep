/**
 * P102: Binary Tree Level Order Traversal (Medium)
 * https://leetcode.com/problems/binary-tree-level-order-traversal/
 * Topics: Tree, Breadth-First Search, Binary Tree
 * 
 * Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).
 * 
 * Example 1:
 *     Input: root = [3,9,20,null,null,15,7]
 *     Output: [[3],[9,20],[15,7]]
 * 
 * Example 2:
 *     Input: root = [1]
 *     Output: [[1]]
 * 
 * Example 3:
 *     Input: root = []
 *     Output: []
 * 
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 2000].
 *     - -1000 <= Node.val <= 1000
 * 
 * Hints:
 *     - Use a queue to perform BFS.
 * 
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
 * 
 * Hint: Use a queue to process nodes level by level.
 */
function buildTree(arr)
  if (arr.length === 0) return null;
  const root = { val: arr[0], left: null, right: null };
  const queue = [root];
  let i = 1;
  while (queue.length > 0 && i < arr.length)
    const node = queue.shift();
    if (i < arr.length && arr[i] !== null)
      node.left = { val: arr[i], left: null, right: null };
      queue.push(node.left);
    }
    i++;
    if (i < arr.length && arr[i] !== null)
      node.right = { val: arr[i], left: null, right: null };
      queue.push(node.right);
    }
    i++;
  }
  return root; {
    throw new Error("NotImplementedError");
}

function levelOrder(root)
  if (!root) return [];
  const result = [];
  const queue = [root];
  while (queue.length > 0)
    const levelSize = queue.length;
    const level = [];
    for (let i = 0; i < levelSize; i++)
      const node = queue.shift();
      level.push(node.val);
      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
    result.push(level);
  }
  return result; {
    throw new Error("NotImplementedError");
}

function solve(root)
  return levelOrder(root); {
    throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: buildTree([3, 9, 20, null, null, 15, 7]), expected: [[3], [9, 20], [15, 7]] },
  { label: "example 2", input: buildTree([1]), expected: [[1]] },
  { label: "empty", input: buildTree([]), expected: [] },
  { label: "right child only", input: buildTree([1, null, 2]), expected: [[1], [2]] },
  { label: "left child only", input: buildTree([1, 2, null]), expected: [[1], [2]] },
  { label: "full binary tree depth 2", input: buildTree([5, 3, 8, 1, 4, 7, 9]), expected: [[5], [3, 8], [1, 4, 7, 9]] },
  { label: "negative values", input: buildTree([-1, -2, -3]), expected: [[-1], [-2, -3]] },
  { label: "all same value", input: buildTree([1, 1, 1, 1, 1, 1, 1]), expected: [[1], [1, 1], [1, 1, 1, 1]] },
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
