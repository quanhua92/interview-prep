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
#include "cpptest.h"
#include <cstdio>
#include <cstdlib>

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

static int solve(ListNode *head) {
    /* TODO: Implement */
    return 0;
}

int main() {
    TestCase tests[] = {
        {"middle of odd-length list", {1, 2, 3}, 0, {2}},
        {"middle of even-length list", {1, 2, 3, 4}, 0, {3}},
        {"single node", {4}, 0, {4}},
        {"two nodes", {1, 2}, 0, {2}},
        {"three nodes", {5, 6, 7}, 0, {6}},
        {"five nodes", {1, 2, 3, 4, 5}, 0, {3}},
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  382. Linked List Random Node\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n; i++) {
        ListNode *head = build_list(tests[i].input_arr);
        int got = solve(head);
        free_list(head);
        if (got == tests[i].expected[0]) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
            printf("    Expected: "); print_arr(tests[i].expected); printf("\n");
            printf("    Got:      [%d]\n", got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
