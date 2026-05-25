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
#include "cpptest.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
};

static ListNode *build_list(const std::vector<int> &arr) {
    /* TODO: Implement */
    return 0;
}

static void free_list(ListNode *head) {
    /* TODO: Implement */
    return 0;
}

static std::vector<int> solve(ListNode *head) {
    /* TODO: Implement */
    return 0;
}

int main() {
    TestCase tests[] = {
        {"odd length", {1, 2, 3, 4, 5}, 0, {3, 4, 5}},
        {"even length", {1, 2, 3, 4, 5, 6}, 0, {4, 5, 6}},
        {"single node", {1}, 0, {1}},
        {"two nodes", {1, 2}, 0, {2}},
        {"three nodes", {1, 2, 3}, 0, {2, 3}},
        {"negative values", {1, -2, 3, -4, 5}, 0, {3, -4, 5}},
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  876. Middle of the Linked List\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n; i++) {
        ListNode *head = build_list(tests[i].input_arr);
        std::vector<int> got = solve(head);
        free_list(head);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
            printf("    Expected: "); print_arr(tests[i].expected); printf("\n");
            printf("    Got:      "); print_arr(got); printf("\n");
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
