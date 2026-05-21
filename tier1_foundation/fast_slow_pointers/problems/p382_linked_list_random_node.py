"""
P382: Linked List Random Node [PREMIUM] (Medium)
https://leetcode.com/problems/linked-list-random-node/
Topics: Linked List, Math, Reservoir Sampling, Randomized

Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.
Implement the Solution class:
Example 1:
Follow up:
    Input
Example 1:
    ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
    [[[1, 2, 3]], [], [], [], [], []]
    Output
    [null, 1, 3, 2, 2, 3]

    Explanation
    Solution solution = new Solution([1, 2, 3]);
    solution.getRandom(); // return 1
    solution.getRandom(); // return 3
    solution.getRandom(); // return 2
    solution.getRandom(); // return 2
    solution.getRandom(); // return 3
    // getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.

Constraints:
    - The number of nodes in the linked list will be in the range [1, 104].
    - -104 <= Node.val <= 104
    - At most 104 calls will be made to getRandom.

Template (python3):
    # Definition for singly-linked list.
    # class ListNode:
    #     def __init__(self, val=0, next=None):
    #         self.val = val
    #         self.next = next
    class Solution:

        def __init__(self, head: Optional[ListNode]):


        def getRandom(self) -> int:



    # Your Solution object will be instantiated and called as such:
    # obj = Solution(head)
    # param_1 = obj.getRandom()
"""

import sys

sys.path.insert(0, ".")
from src.utils import ListNode, Problem, TestCase
from typing import Any


class Solution(Problem):
    name = "382. Linked List Random Node"
    test_cases = [
        TestCase(
            input=ListNode.from_list([1, 2, 3]),
            expected=2,
            label="middle of odd-length list",
        ),
        TestCase(
            input=ListNode.from_list([1, 2, 3, 4]),
            expected=3,
            label="middle of even-length list",
        ),
        TestCase(
            input=ListNode.from_list([4]),
            expected=4,
            label="single node",
        ),
    ]

    def solve(self, head: ListNode) -> int:
        raise NotImplementedError("TODO: Implement solve(self, head: ListNode) -> int")


if __name__ == "__main__":
    Solution().run()
