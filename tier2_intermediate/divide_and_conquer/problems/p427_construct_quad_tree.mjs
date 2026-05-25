/**
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 * 
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 * A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:
 * We can construct a Quad-Tree from a two-dimensional area using the following steps:
 * If you want to know more about the Quad-Tree, you can refer to the wiki.
 * Quad-Tree format:
 * You don't need to read this section for solving the problem. This is only if you want to understand the output format here. The output represents the serialized format of a Quad-Tree using level order traversal, where null signifies a path terminator where no node exists below.
 * It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list [isLeaf, val].
 * If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val] and if the value of isLeaf or val is False we represent it as 0.
 *     class Node {
 *     public boolean val;
 *     public boolean isLeaf;
 *     public Node topLeft;
 *     public Node topRight;
 *     public Node bottomLeft;
 *     public Node bottomRight;
 *     }
 * 
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
 *     Explanation: The explanation of this example is shown below:
 *     Notice that 0 represents False and 1 represents True in the photo representing the Quad-Tree.
 * 
 * Example 2:
 *     Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
 *     Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
 *     Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
 *     The topLeft, bottomLeft and bottomRight each has the same value.
 *     The topRight have different values so we divide it into 4 sub-grids where each has the same value.
 *     Explanation is shown in the photo below:
 * 
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 * 
 * Template (python3):
 *     '''
 *     # Definition for a QuadTree node.
 *     class Node:
 *         def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
 *             self.val = val
 *             self.isLeaf = isLeaf
 *             self.topLeft = topLeft
 *             self.topRight = topRight
 *             self.bottomLeft = bottomLeft
 *             self.bottomRight = bottomRight
 *     '''
 * 
 *     class Solution:
 *         def construct(self, grid: List[List[int]]) -> 'Node':
 */
function solve(grid)
  function allSame(x, y, size)
    const val = grid[x][y];
    for (let i = x; i < x + size; i++)
      for (let j = y; j < y + size; j++)
        if (grid[i][j] !== val) return false;
      }
    }
    return true;
  }

  function build(x, y, size)
    if (allSame(x, y, size))
      return [1, grid[x][y]];
    }
    const half = Math.floor(size / 2);
    const tl = build(x, y, half);
    const tr = build(x, y + half, half);
    const bl = build(x + half, y, half);
    const br = build(x + half, y + half, half);
    return [0, 1, tl, tr, bl, br];
  }

  const tree = build(0, 0, grid.length);
  const result = [];
  const queue = [tree];
  while (queue.length > 0)
    const node = queue.shift();
    if (node === null || node === undefined)
      result.push(null);
      continue;
    }
    result.push([node[0], node[1]]);
    if (node[0] === 0)
      for (let c = 2; c < node.length; c++)
        queue.push(node[c]);
      }
    }
  }
  while (result.length > 0 && result[result.length - 1] === null)
    result.pop();
  }
  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 2", input: [[0, 1], [1, 0]], expected: [[0, 1], [1, 0], [1, 1], [1, 1], [1, 0]] },
  {
    label: "example 3",
    input: [
      [1, 1, 1, 1, 0, 0, 0, 0],
      [1, 1, 1, 1, 0, 0, 0, 0],
      [1, 1, 1, 1, 1, 1, 1, 1],
      [1, 1, 1, 1, 1, 1, 1, 1],
      [1, 1, 1, 1, 0, 0, 0, 0],
      [1, 1, 1, 1, 0, 0, 0, 0],
      [1, 1, 1, 1, 0, 0, 0, 0],
      [1, 1, 1, 1, 0, 0, 0, 0],
    ],
    expected: [
      [0, 1],
      [1, 1],
      [0, 1],
      [1, 1],
      [1, 0],
      [1, 0],
      [1, 0],
      [1, 1],
      [1, 1],
    ],
  },
  { label: "1x1 all zeros", input: [[0]], expected: [[1, 0]] },
  { label: "1x1 all ones", input: [[1]], expected: [[1, 1]] },
  { label: "2x2 all same (ones)", input: [[1, 1], [1, 1]], expected: [[1, 1]] },
  { label: "4x4 all zeros", input: [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]], expected: [[1, 0]] },
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
