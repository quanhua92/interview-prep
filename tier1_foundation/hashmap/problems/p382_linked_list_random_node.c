/*
 * P382: Linked List Random Node [PREMIUM] (Medium)
 * https://leetcode.com/problems/linked-list-random-node/
 * Topics: Linked List, Math, Reservoir Sampling, Randomized
 *
 * Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.
 * Implement the Solution class:
 * Example 1:
 * Follow up:
 *     Input
 * Example 1:
 *     ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
 *     [[[1, 2, 3]], [], [], [], [], []]
 *     Output
 *     [null, 1, 3, 2, 2, 3]
 *
 *     Explanation
 *     Solution solution = new Solution([1, 2, 3]);
 *     solution.getRandom(); // return 1
 *     solution.getRandom(); // return 3
 *     solution.getRandom(); // return 2
 *     solution.getRandom(); // return 2
 *     solution.getRandom(); // return 3
 *     // getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
 *
 * Constraints:
 *     - The number of nodes in the linked list will be in the range [1, 10^4].
 *     - -10^4 <= Node.val <= 10^4
 *     - At most 10^4 calls will be made to getRandom.
 *
 * Template (python3):
 *     # Definition for singly-linked list.
 *     # class ListNode:
 *     #     def __init__(self, val=0, next=None):
 *     #         self.val = val
 *     #         self.next = next
 *     class Solution:
 *
 *         def __init__(self, head: Optional[ListNode]):
 *
 *
 *         def getRandom(self) -> int:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(head)
 *     # param_1 = obj.getRandom()
 */


#include "io.h"
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

static ListNode *build_list(const int *arr, int n) {
    ListNode dummy = {0, NULL};
    ListNode *cur = &dummy;
    for (int i = 0; i < n; i++) {
        ListNode *node = malloc(sizeof(ListNode));
        node->val = arr[i];
        node->next = NULL;
        cur->next = node;
        cur = node;
    }
    return dummy.next;
}

static void free_list(ListNode *head) {
    while (head) {
        ListNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}

static int solve(ListNode *head) {
    abort();
}

int main(void)
{
    int n;
    int *arr = read_ints(&n);
    ListNode *head = build_list(arr, n);
    write_int(solve(head));
    free_list(head);
    free(arr);
    return 0;
}
