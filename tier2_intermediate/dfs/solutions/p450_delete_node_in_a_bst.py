"""
P450: Delete Node in a BST [PREMIUM] (Medium)
https://leetcode.com/problems/delete-node-in-a-bst/
Topics: Tree, Binary Search Tree, Binary Tree

Given the root of a Binary Search Tree (BST) and a key, delete the node with the given key in the BST.
Return the root node reference (possibly updated) of the BST.

The deletion process involves finding the node and handling three cases:
- Node has no children: simply remove it.
- Node has one child: replace the node with its child.
- Node has two children: find the inorder successor (smallest in the right subtree),
  attach the deleted node's left subtree to the successor, and replace with the right subtree.

Example 1:
    Input: root = [5,3,6,2,4,null,7], key = 3
    Output: [5,4,6,2,null,null,7]
    Explanation: The node with value 3 is deleted. One valid answer is [5,4,6,2,null,null,7],
    another is [5,2,6,null,4,null,7].

Example 2:
    Input: root = [5,3,6,2,4,null,7], key = 0
    Output: [5,3,6,2,4,null,7]
    Explanation: The key 0 is not found, so the tree is unchanged.

Example 3:
    Input: root = [], key = 0
    Output: []

Constraints:
    - The number of nodes in the tree is in the range [0, 10^4].
    - -10^5 <= Node.val <= 10^5
    - Each node has a unique value.
    - root is a valid binary search tree.

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:

Hint: Recurse down the BST to find the target. When found with two children,
find the leftmost node in the right subtree (inorder successor), attach the left
subtree to it, and return the right subtree as the new root.
"""

from src.wasm_libs.py.io import read_line, write_string

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


def delete_node(root, key):
    if not root:
        return None
    if key < root["val"]:
        root["left"] = delete_node(root["left"], key)
    elif key > root["val"]:
        root["right"] = delete_node(root["right"], key)
    else:
        if not root["left"]:
            return root["right"]
        if not root["right"]:
            return root["left"]
        min_node = root["right"]
        while min_node["left"]:
            min_node = min_node["left"]
        root["val"] = min_node["val"]
        root["right"] = delete_node(root["right"], min_node["val"])
    return root


def main():
    tree_line = read_line()
    key = int(read_line())
    parts = tree_line.split()
    vals = [None if x == "null" else int(x) for x in parts]
    if not vals or vals[0] is None:
        root = None
    else:
        root = build_tree(vals)
    root = delete_node(root, key)
    result = tree_to_bfs(root)
    output = " ".join("null" if v is None else str(v) for v in result) if result else "null"
    write_string(output)


if __name__ == "__main__":
    main()
