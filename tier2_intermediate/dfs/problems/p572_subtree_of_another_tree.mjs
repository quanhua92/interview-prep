/**
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 * 
 * Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
 * A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
 * Example 1:
 *     Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 *     Output: true
 * 
 * Example 2:
 *     Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
 *     Output: false
 * 
 * Constraints:
 *     - The number of nodes in the root tree is in the range [1, 2000].
 *     - The number of nodes in the subRoot tree is in the range [1, 1000].
 *     - -104 <= root.val <= 104
 *     - -104 <= subRoot.val <= 104
 * 
 * Hint: Which approach is better here- recursive or iterative?
 * Hint: If recursive approach is better, can you write recursive function with its parameters?
 * Hint: Two trees <b>s</b> and <b>t</b> are said to be identical if their root values are same and their left and right subtrees are identical. Can you write this in form of recursive formulae?
 * Hint: Recursive formulae can be:
 * isIdentical(s,t)= s.val==t.val AND isIdentical(s.left,t.left) AND isIdentical(s.right,t.right)
 * 
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
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

function isSame(a, b)
  if (!a && !b) return true;
  if (!a || !b) return false;
  return a.val === b.val && isSame(a.left, b.left) && isSame(a.right, b.right); {
    throw new Error("NotImplementedError");
}

function solve(root, subRoot)
  if (!subRoot) return true;
  if (!root) return false;
  if (isSame(root, subRoot)) return true;
  return solve(root.left, subRoot) || solve(root.right, subRoot); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [buildTree([3, 4, 5, 1, 2]), buildTree([4, 1, 2])], expected: true },
  { label: "example 2", input: [buildTree([3, 4, 5, 1, 2, null, null, null, null, 0]), buildTree([4, 1, 2])], expected: false },
  { label: "identical trees", input: [buildTree([1, 2, 3]), buildTree([1, 2, 3])], expected: true },
  { label: "single node match", input: [buildTree([1]), buildTree([1])], expected: true },
  { label: "right-skewed subtree", input: [buildTree([1, null, 2, null, 3]), buildTree([2, null, 3])], expected: true },
  { label: "no matching value", input: [buildTree([1, 2]), buildTree([3])], expected: false },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0], t.input[1]);
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
