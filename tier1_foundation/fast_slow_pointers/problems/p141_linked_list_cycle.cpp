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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

static ListNode *build_list(const std::vector<int> &vals)
{
    /* TODO: Implement */
    return 0;
}

static void create_cycle(ListNode *head, int n, int pos)
{
    /* TODO: Implement */
    return 0;
}

static bool hasCycle(ListNode *head, int n, int pos)
{
    /* TODO: Implement */
    return 0;
}

struct CycleTestCase {
    const char *label;
    std::vector<int> vals;
    int pos;
    bool expected;
};

int main()
{
    CycleTestCase tests[] = {
        {"example 1",            {3, 2, 0, -4},       1,  true},
        {"example 2",            {1, 2},               0,  true},
        {"example 3",            {1},                 -1,  false},
        {"empty list",           {},                  -1,  false},
        {"two nodes no cycle",   {1, 2},              -1,  false},
        {"self-loop at tail",    {1, 2, 3},            2,  true},
        {"long list no cycle",   {1, 2, 3, 4, 5},    -1,  false},
        {"cycle back to head",   {1, 2, 3},            0,  true},
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  141. Linked List Cycle\n");
    printf("============================================================\n");

    int passed = 0;
    for (int i = 0; i < num_tests; i++) {
        CycleTestCase &tc = tests[i];
        ListNode *head = build_list(tc.vals);
        bool got = hasCycle(head, (int)tc.vals.size(), tc.pos);
        if (got == tc.expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tc.label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tc.label);
            printf("    Expected: %s\n    Got:      %s\n",
                   tc.expected ? "true" : "false",
                   got ? "true" : "false");
        }
        delete head;
    }

    printf("\n  %d/%d passed\n", passed, num_tests);
    printf("============================================================\n\n");
    return passed == num_tests ? 0 : 1;
}
