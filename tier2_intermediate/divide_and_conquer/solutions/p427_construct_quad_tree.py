"""
P427: Construct Quad Tree [PREMIUM] (Medium)
https://leetcode.com/problems/construct-quad-tree/
Topics: Array, Divide and Conquer, Tree, Matrix

Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
Return the root of the Quad-Tree representing grid.
A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:
We can construct a Quad-Tree from a two-dimensional area using the following steps:
If you want to know more about the Quad-Tree, you can refer to the wiki.
Quad-Tree format:
You don't need to read this section for solving the problem. This is only if you want to understand the output format here. The output represents the serialized format of a Quad-Tree using level order traversal, where null signifies a path terminator where no node exists below.
It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list [isLeaf, val].
If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val] and if the value of isLeaf or val is False we represent it as 0.
    class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
    }

Example 1:
    Input: grid = [[0,1],[1,0]]
    Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
    Explanation: The explanation of this example is shown below:
    Notice that 0 represents False and 1 represents True in the photo representing the Quad-Tree.

Example 2:
    Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
    Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
    Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
    The topLeft, bottomLeft and bottomRight each has the same value.
    The topRight have different values so we divide it into 4 sub-grids where each has the same value.
    Explanation is shown in the photo below:

Constraints:
    - n == grid.length == grid[i].length
    - n == 2x where 0 <= x <= 6

Template (python3):
    '''
    # Definition for a QuadTree node.
    class Node:
        def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
            self.val = val
            self.isLeaf = isLeaf
            self.topLeft = topLeft
            self.topRight = topRight
            self.bottomLeft = bottomLeft
            self.bottomRight = bottomRight
    '''

    class Solution:
        def construct(self, grid: List[List[int]]) -> 'Node':
"""

from collections import deque

from src.wasm_libs.py.io import *


def solve(grid: list[list[int]]) -> list:
    def all_same(x, y, size):
        val = grid[x][y]
        for i in range(x, x + size):
            for j in range(y, y + size):
                if grid[i][j] != val:
                    return False
        return True

    def build(x, y, size):
        if all_same(x, y, size):
            return [1, int(grid[x][y])]
        half = size // 2
        tl = build(x, y, half)
        tr = build(x, y + half, half)
        bl = build(x + half, y, half)
        br = build(x + half, y + half, half)
        return [0, 1, tl, tr, bl, br]

    tree = build(0, 0, len(grid))
    queue = deque([tree])
    while queue:
        node = queue.popleft()
        if node is None:
            write_string("null")
            continue
        write_ints([node[0], node[1]])
        if node[0] == 0:
            for child in node[2:]:
                queue.append(child)


if __name__ == "__main__":
    cols = read_int()
    grid = []
    for _ in range(cols):
        grid.append(read_ints())
    solve(grid)
