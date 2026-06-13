"""
P572: Subtree of Another Tree [PREMIUM] (Easy)
https://leetcode.com/problems/subtree-of-another-tree/
Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function

Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot.

Example 1:
    Input: root = [3,4,5,1,2], subRoot = [4,1,2]
    Output: true

Example 2:
    Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
    Output: false

Constraints:
    - The number of nodes in root is in the range [1, 2000].
    - -10^4 <= root.val <= 10^4

Template (python3):
    class Solution:
        def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
"""

from src.wasm_libs.py.io import read_line, write_bool


def build_tree(vals):
    if not vals or vals[0] is None:
        return None
    root = {"val": vals[0], "left": None, "right": None}
    queue = [root]
    i = 1
    while queue and i < len(vals):
        node = queue.pop(0)
        if i < len(vals) and vals[i] is not None:
            node["left"] = {"val": vals[i], "left": None, "right": None}
            queue.append(node["left"])
        i += 1
        if i < len(vals) and vals[i] is not None:
            node["right"] = {"val": vals[i], "left": None, "right": None}
            queue.append(node["right"])
        i += 1
    return root


def solve(root, sub_root) -> bool:
    raise NotImplementedError


if __name__ == "__main__":
    root_line = read_line()
    sub_line = read_line()
    root_vals = [None if x == "null" else int(x) for x in root_line.split()]
    sub_vals = [None if x == "null" else int(x) for x in sub_line.split()]
    root = build_tree(root_vals)
    sub_root = build_tree(sub_vals)
    result = solve(root, sub_root)
    write_bool(result)
