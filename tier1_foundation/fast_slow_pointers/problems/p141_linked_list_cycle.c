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
 *     - The number of the nodes in the list is in the range [0, 104].
 *     - -105 <= Node.val <= 105
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
#include <stdlib.h>

static int read_int(void)
{
    char *line = read_line();
    int val = atoi(line);
    free(line);
    return val;
}

struct ListNode {
    int val;
    struct ListNode *next;
};

int hasCycle(struct ListNode *head, int n, int pos)
{
    abort();
}

int main(void)
{
    int n;
    int *vals = read_ints(&n);
    int pos = read_int();
    struct ListNode *nodes = NULL;
    if (n > 0) {
        nodes = (struct ListNode *)malloc(n * sizeof(struct ListNode));
        for (int i = 0; i < n; i++) {
            nodes[i].val = vals[i];
            nodes[i].next = (i + 1 < n) ? &nodes[i + 1] : NULL;
        }
    }
    int result = hasCycle(nodes, n, pos);
    write_bool(result);
    free(nodes);
    free(vals);
    return 0;
}
