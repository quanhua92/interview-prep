"""
P23: Merge k Sorted Lists (Hard)
https://leetcode.com/problems/merge-k-sorted-lists/
Topics: Linked List, Divide and Conquer, Heap (Priority Queue), Merge Sort

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Example 1:
    Input: lists = [[1,4,5],[1,3,4],[2,6]]
    Output: [1,1,2,3,4,4,5,6]
    Explanation: The linked-lists are:
    [
      1->4->5,
      1->3->4,
      2->6
    ]
    merging them into one sorted linked list:
    1->1->2->3->4->4->5->6

Example 2:
    Input: lists = []
    Output: []

Example 3:
    Input: lists = [[]]
    Output: []

Constraints:
    - k == lists.length
    - 0 <= k <= 10^4
    - 0 <= lists[i].length <= 500
    - -10^4 <= lists[i][j] <= 10^4
    - lists[i] is sorted in ascending order.
    - The sum of lists[i].length will not exceed 10^4.

Template (python3):
    # Definition for singly-linked list.
    # class ListNode:
    #     def __init__(self, val=0, next=None):
    #         self.val = val
    #         self.next = next
    class Solution:
        def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
"""

from src.wasm_libs.py.io import *


def solve(lists: list[list[int]]) -> list[int]:
    if not lists:
        return []
    if len(lists) == 1:
        return lists[0][:]

    mid = len(lists) // 2
    left = solve(lists[:mid])
    right = solve(lists[mid:])

    result: list[int] = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result


if __name__ == "__main__":
    k = read_int()
    lists = []
    for _ in range(k):
        lists.append(read_ints())
    result = solve(lists)
    write_ints(result)
