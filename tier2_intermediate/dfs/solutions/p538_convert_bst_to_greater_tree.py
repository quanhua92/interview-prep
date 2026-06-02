"""
P538: Convert BST to Greater Tree [PREMIUM] (Medium)
https://leetcode.com/problems/convert-bst-to-greater-tree/
Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree

Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
As a reminder, a binary search tree is a tree that satisfies these constraints:
Example 2:
Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
Example 1:
    Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

Example 2:
    Input: root = [0,null,1]
    Output: [1,null,1]

Constraints:
    - The number of nodes in the tree is in the range [0, 10^4].
    - -10^4 <= Node.val <= 10^4
    - All the values in the tree are unique.
    - root is guaranteed to be a valid binary search tree.

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
"""

from src.wasm_libs.py.io import read_line

NL = 2147483647


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


def tree_to_bfs(root):
    if not root:
        return []
    result = []
    queue = [root]
    while queue:
        node = queue.pop(0)
        if node:
            result.append(node["val"])
            queue.append(node.get("left"))
            queue.append(node.get("right"))
        else:
            result.append(None)
    while len(result) > 1 and result[-1] is None:
        result.pop()
    return result


def reverse_inorder(node, total):
    if not node:
        return total
    total = reverse_inorder(node.get("right"), total)
    total += node["val"]
    node["val"] = total
    total = reverse_inorder(node.get("left"), total)
    return total


def main():
    line = read_line()
    if not line.strip():
        print()
        return
    parts = line.split()
    vals = [None if x == "null" else int(x) for x in parts]
    if not vals or vals[0] is None:
        print()
        return
    root = build_tree(vals)
    reverse_inorder(root, 0)
    result = tree_to_bfs(root)
    output = " ".join("null" if v is None else str(v) for v in result)
    print(output)


if __name__ == "__main__":
    main()
