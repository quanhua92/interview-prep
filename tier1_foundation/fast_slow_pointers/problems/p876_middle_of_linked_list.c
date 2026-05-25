/*
 * P876: Middle of the Linked List (Easy)
 * https://leetcode.com/problems/middle-of-the-linked-list/
 * Topics: Linked List, Two Pointers
 * 
 * Given the head of a singly linked list, return the middle node of the linked list.
 * If there are two middle nodes, return the second middle node.
 * 
 * Example 1:
 *     Input: head = [1,2,3,4,5]
 *     Output: [3,4,5]
 *     Explanation: The middle node of the list is node 3.
 * 
 * Example 2:
 *     Input: head = [1,2,3,4,5,6]
 *     Output: [4,5,6]
 *     Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.
 * 
 * Constraints:
 *     - The number of nodes in the list is in the range [1, 100].
 *     - 1 <= Node.val <= 100
 * 
 * Template (python3):
 *     # Definition for singly-linked list.
 *     # class ListNode:
 *     #     def __init__(self, val=0, next=None):
 *     #         self.val = val
 *     #         self.next = next
 *     class Solution:
 *         def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:
 * 
 * Hint: Fast pointer moves 2 steps, slow moves 1, return slow.to_list().
 */
#include "ctest.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

static ListNode *build_list(const int *arr, int n) {
    abort();
}

static void free_list(ListNode *head) {
    abort();
}

static int *solve(ListNode *head, int *ret_size) {
    abort();
}

int main(void) {
    static TestCase tests[] = {
        {"odd length", {1, 2, 3, 4, 5}, 5, 0, {3, 4, 5}, 3},
        {"even length", {1, 2, 3, 4, 5, 6}, 6, 0, {4, 5, 6}, 3},
        {"single node", {1}, 1, 0, {1}, 1},
        {"two nodes", {1, 2}, 2, 0, {2}, 1},
        {"three nodes", {1, 2, 3}, 3, 0, {2, 3}, 2},
        {"negative values", {1, -2, 3, -4, 5}, 5, 0, {3, -4, 5}, 3},
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  876. Middle of the Linked List\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n; i++) {
        ListNode *head = build_list(tests[i].input_arr, tests[i].input_arr_n);
        int ret_size = 0;
        int *got = solve(head, &ret_size);
        if (th_arr_eq(got, ret_size, tests[i].expected, tests[i].expected_n)) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: ");
            th_print_arr(tests[i].expected, tests[i].expected_n);
            printf("\n    Got:      ");
            if (got) th_print_arr(got, ret_size);
            else printf("NULL");
            printf("\n");
        }
        free(got);
        free_list(head);
    }
    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
