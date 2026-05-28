"""
P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
https://leetcode.com/problems/most-frequent-subtree-sum/
Topics: Hash Table, Tree, Depth-First Search, Binary Tree

Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
Example 1:
    Input: root = [5,2,-3]
    Output: [2,-3,4]

Example 2:
    Input: root = [5,2,-5]
    Output: [2]

Constraints:
    - The number of nodes in the tree is in the range [1, 104].
    - -105 <= Node.val <= 105

Template (python3):
    # Definition for a binary tree node.
    # class TreeNode:
    #     def __init__(self, val=0, left=None, right=None):
    #         self.val = val
    #         self.left = left
    #         self.right = right
    class Solution:
        def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
"""

from src.wasm_libs.py.io import read_line, write_ints

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


def subtree_sum(node):
    if not node:
        return 0
    s = node["val"] + subtree_sum(node.get("left")) + subtree_sum(node.get("right"))
    return s


def collect_sums(node, freq):
    if not node:
        return 0
    s = node["val"] + collect_sums(node.get("left"), freq) + collect_sums(node.get("right"), freq)
    freq[s] = freq.get(s, 0) + 1
    return s


def main():
    line = read_line()
    parts = line.split()
    vals = [None if x == "null" else int(x) for x in parts]
    root = build_tree(vals)
    freq = {}
    collect_sums(root, freq)
    max_count = max(freq.values())
    result = sorted(s for s, c in freq.items() if c == max_count)
    write_ints(result)


if __name__ == "__main__":
    main()
