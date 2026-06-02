/*
 * P141: Linked List Cycle (Easy)
 * https://leetcode.com/problems/linked-list-cycle/
 * Topics: Hash Table, Linked List, Two Pointers
 *
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 * There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 *
 * Example 1:
 *     Input: head = [3,2,0,-4], pos = 1
 *     Output: true
 *     Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
 *
 * Example 2:
 *     Input: head = [1,2], pos = 0
 *     Output: true
 *     Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
 *
 * Example 3:
 *     Input: head = [1], pos = -1
 *     Output: false
 *     Explanation: There is no cycle in the linked list.
 *
 * Constraints:
 *     - The number of the nodes in the list is in the range [0, 10^4].
 *     - -10^5 <= Node.val <= 10^5
 *     - pos is -1 or a valid index in the linked-list.
 *
 * Follow up:
 *     - Can you solve it using O(1) (i.e. constant) memory?
 *
 * Template (python3):
 *     # Definition for singly-linked list.
 *     # class ListNode:
 *     #     def __init__(self, x):
 *     #         self.val = x
 *     #         self.next = None
 *
 *     class Solution:
 *         def hasCycle(self, head: Optional[ListNode]) -> bool:
 *
 * Hint: Use Floyd's cycle-finding algorithm with fast and slow pointers.
 */

#include "io.h"
#include <cstdlib>
#include <algorithm>
#include <vector>


struct ListNode {
    int val;
    ListNode *next;
};

int hasCycle(ListNode *head, int n, int pos)
{
    if (!head) return false;
    if (pos >= 0 && pos < n) {
        ListNode *tail = head;
        while (tail->next) tail = tail->next;
        ListNode *target = head;
        for (int i = 0; i < pos; i++) target = target->next;
        tail->next = target;
    }
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

int main(void)
{
    std::vector<int> vals = read_ints();
    int pos = read_int();
    int n = (int)vals.size();
    std::vector<ListNode> nodes;
    for (int v : vals) nodes.push_back({v, nullptr});
    for (int i = 0; i + 1 < n; i++) nodes[i].next = &nodes[i + 1];
    ListNode *head = n > 0 ? &nodes[0] : nullptr;
    int result = hasCycle(head, n, pos);
    write_bool(result);
    return 0;
}
