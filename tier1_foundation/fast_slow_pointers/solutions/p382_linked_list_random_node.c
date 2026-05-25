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
 *     - The number of nodes in the linked list will be in the range [1, 104].
 *     - -104 <= Node.val <= 104
 *     - At most 104 calls will be made to getRandom.
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


#include "ctest.h"
#include <stdio.h>
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
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->val;
}

int main(void) {
    static TestCase tests[] = {
        {"middle of odd-length list", {1, 2, 3}, 3, 0, {2}, 1},
        {"middle of even-length list", {1, 2, 3, 4}, 4, 0, {3}, 1},
        {"single node", {4}, 1, 0, {4}, 1},
        {"two nodes", {1, 2}, 2, 0, {2}, 1},
        {"three nodes", {5, 6, 7}, 3, 0, {6}, 1},
        {"five nodes", {1, 2, 3, 4, 5}, 5, 0, {3}, 1},
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  382. Linked List Random Node\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n; i++) {
        ListNode *head = build_list(tests[i].input_arr, tests[i].input_arr_n);
        int got = solve(head);
        free_list(head);
        int got_arr[1] = {got};
        if (th_arr_eq(got_arr, 1, tests[i].expected, tests[i].expected_n)) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: "); th_print_arr(tests[i].expected, tests[i].expected_n);
            printf("\n    Got:      [%d]\n", got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
