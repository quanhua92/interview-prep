"""
P23: Merge k Sorted Lists (Hard)
https://leetcode.com/problems/merge-k-sorted-lists/
Topics: Linked List, Divide and Conquer, Heap (Priority Queue), Merge Sort

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Example 1:
    Input: lists = [[1,4,5],[1,3,4],[2,6]]
    Output: [1,1,2,3,4,4,5,6]

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

Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
"""

from src.wasm_libs.py.io import *


def solve(lists: list[list[int]]) -> list[int]:
    raise NotImplementedError


if __name__ == "__main__":
    k = read_int()
    lists = []
    for _ in range(k):
        lists.append(read_ints())
    result = solve(lists)
    write_ints(result)
