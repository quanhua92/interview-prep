"""
P572: Subtree of Another Tree [PREMIUM] (Easy)
https://leetcode.com/problems/subtree-of-another-tree/
Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function

Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
Example 1:
    Input: root = [3,4,5,1,2], subRoot = [4,1,2]
    Output: true

Example 2:
    Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
    Output: false

Constraints:
    - The number of nodes in the root tree is in the range [1, 2000].
    - The number of nodes in the subRoot tree is in the range [1, 1000].
    - -10^4 <= root.val <= 10^4
    - -10^4 <= subRoot.val <= 10^4

Hint: Which approach is better here- recursive or iterative?
Hint: If recursive approach is better, can you write recursive function with its parameters?
Hint: Two trees <b>s</b> and <b>t</b> are said to be identical if their root values are same and their left and right subtrees are identical. Can you write this in form of recursive formulae?
Hint: Recursive formulae can be:
isIdentical(s,t)= s.val==t.val AND isIdentical(s.left,t.left) AND isIdentical(s.right,t.right)

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
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


def is_same(a, b):
    if not a and not b:
        return True
    if not a or not b:
        return False
    return (
        a["val"] == b["val"]
        and is_same(a.get("left"), b.get("left"))
        and is_same(a.get("right"), b.get("right"))
    )


def is_subtree(root, sub_root):
    if not sub_root:
        return True
    if not root:
        return False
    if is_same(root, sub_root):
        return True
    return is_subtree(root.get("left"), sub_root) or is_subtree(
        root.get("right"), sub_root
    )


def solve(root, sub_root) -> bool:
    return is_subtree(root, sub_root)


if __name__ == "__main__":
    root_line = read_line()
    sub_line = read_line()
    root_vals = [None if x == "null" else int(x) for x in root_line.split()]
    sub_vals = [None if x == "null" else int(x) for x in sub_line.split()]
    root = build_tree(root_vals)
    sub_root = build_tree(sub_vals)
    result = solve(root, sub_root)
    write_bool(result)
