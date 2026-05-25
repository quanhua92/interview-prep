/**
 * P515: Find Largest Value in Each Tree Row [PREMIUM] (Medium)
 * https://leetcode.com/problems/find-largest-value-in-each-tree-row/
 * Topics: Tree, Depth-First Search, Breadth-First Search, Binary Tree
 * 
 * Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).
 * Example 1:
 *     Input: root = [1,3,2,5,3,null,9]
 *     Output: [1,3,9]
 * 
 * Example 2:
 *     Input: root = [1,2,3]
 *     Output: [1,3]
 * 
 * Constraints:
 *     - The number of nodes in the tree will be in the range [0, 104].
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
 *         def largestValues(self, root: Optional[TreeNode]) -> List[int]:
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

function largestValues(root)
  if (!root) return [];
  const result = [];
  const queue = [root];
  while (queue.length > 0)
    const levelSize = queue.length;
    let maxVal = -Infinity;
    for (let i = 0; i < levelSize; i++)
      const node = queue.shift();
      maxVal = Math.max(maxVal, node.val);
      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
    result.push(maxVal);
  }
  return result; {
    throw new Error("NotImplementedError");
}

function solve(input)
  return largestValues(input); {
    throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: buildTree([1, 3, 2, 5, 3, null, 9]), expected: [1, 3, 9] },
  { label: "example 2", input: buildTree([1, 2, 3]), expected: [1, 3] },
  { label: "empty tree", input: buildTree([]), expected: [] },
  { label: "negative values", input: buildTree([-1, -2, -3, -4]), expected: [-1, -2, -4] },
  { label: "left chain", input: buildTree([1, 2, null, 3]), expected: [1, 2, 3] },
  { label: "single node", input: buildTree([5]), expected: [5] },
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
