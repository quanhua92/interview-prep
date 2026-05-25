/*
 * P23: Merge k Sorted Lists (Hard)
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * Topics: Linked List, Divide and Conquer, Heap (Priority Queue), Merge Sort
 * 
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 * 
 * Example 1:
 *     Input: lists = [[1,4,5],[1,3,4],[2,6]]
 *     Output: [1,1,2,3,4,4,5,6]
 *     Explanation: The linked-lists are:
 *     [
 *       1->4->5,
 *       1->3->4,
 *       2->6
 *     ]
 *     merging them into one sorted linked list:
 *     1->1->2->3->4->4->5->6
 * 
 * Example 2:
 *     Input: lists = []
 *     Output: []
 * 
 * Example 3:
 *     Input: lists = [[]]
 *     Output: []
 * 
 * Constraints:
 *     - k == lists.length
 *     - 0 <= k <= 104
 *     - 0 <= lists[i].length <= 500
 *     - -104 <= lists[i][j] <= 104
 *     - lists[i] is sorted in ascending order.
 *     - The sum of lists[i].length will not exceed 104.
 * 
 * Template (python3):
 *     # Definition for singly-linked list.
 *     # class ListNode:
 *     #     def __init__(self, val=0, next=None):
 *     #         self.val = val
 *     #         self.next = next
 *     class Solution:
 *         def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
 * 
 * Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

static ListNode *make_list(const int *arr, int n)
{
    /* TODO: Implement */
    return 0;
}

static int list_len(ListNode *h) {
    /* TODO: Implement */
    return 0;
}

static void merge_two(ListNode *a, ListNode *b, ListNode **out)
{
    /* TODO: Implement */
    return 0;
}

static void divide_merge(ListNode **lists, int left, int right, ListNode **out)
{
    /* TODO: Implement */
    return 0;
}

int *mergeKLists(ListNode **lists, int k, int *ret_size)
{
    /* TODO: Implement */
    return 0;
}

static void print_arr(const int *a, int n)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    printf("\n============================================================\n");
    printf("  23. Merge k Sorted Lists\n");
    printf("============================================================\n");
    int passed = 0, total = 8;

    {
        int a1[] = {1,4,5}, a2[] = {1,3,4}, a3[] = {2,6};
        ListNode *lists[3] = {make_list(a1,3), make_list(a2,3), make_list(a3,2)};
        int exp[] = {1,1,2,3,4,4,5,6}, rs = 0;
        int *got = mergeKLists(lists, 3, &rs);
        int ok = rs == 8 && memcmp(got, exp, 8*sizeof(int)) == 0;
        if (ok) passed++; else { printf("  Test 1 (example 1): FAIL\n  Expected: "); print_arr(exp,8); printf("\n  Got:      "); print_arr(got,rs); printf("\n"); }
        if (ok) printf("  Test 1 (example 1): PASS\n");
        free(got);
    }
    {
        int rs = 0; int *got = mergeKLists(NULL, 0, &rs);
        if (rs == 0) { passed++; printf("  Test 2 (empty input): PASS\n"); }
        else printf("  Test 2 (empty input): FAIL\n");
        free(got);
    }
    {
        ListNode *lists[1] = {NULL};
        int rs = 0; int *got = mergeKLists(lists, 1, &rs);
        if (rs == 0) { passed++; printf("  Test 3 (single empty list): PASS\n"); }
        else printf("  Test 3 (single empty list): FAIL\n");
        free(got);
    }
    {
        int a1[] = {1,2,3};
        ListNode *lists[1] = {make_list(a1,3)};
        int exp[] = {1,2,3}, rs = 0;
        int *got = mergeKLists(lists, 1, &rs);
        int ok = rs == 3 && memcmp(got, exp, 3*sizeof(int)) == 0;
        if (ok) passed++; else printf("  Test 4 (single list): FAIL\n");
        if (ok) printf("  Test 4 (single list): PASS\n");
        free(got);
    }
    {
        int a1[] = {1,1}, a2[] = {1,1}, a3[] = {1,1};
        ListNode *lists[3] = {make_list(a1,2), make_list(a2,2), make_list(a3,2)};
        int exp[] = {1,1,1,1,1,1}, rs = 0;
        int *got = mergeKLists(lists, 3, &rs);
        int ok = rs == 6 && memcmp(got, exp, 6*sizeof(int)) == 0;
        if (ok) passed++; else printf("  Test 5 (all same values): FAIL\n");
        if (ok) printf("  Test 5 (all same values): PASS\n");
        free(got);
    }
    {
        int a1[] = {-5,-3}, a2[] = {-4,-2}, a3[] = {-6,0};
        ListNode *lists[3] = {make_list(a1,2), make_list(a2,2), make_list(a3,2)};
        int exp[] = {-6,-5,-4,-3,-2,0}, rs = 0;
        int *got = mergeKLists(lists, 3, &rs);
        int ok = rs == 6 && memcmp(got, exp, 6*sizeof(int)) == 0;
        if (ok) passed++; else printf("  Test 6 (negative values): FAIL\n");
        if (ok) printf("  Test 6 (negative values): PASS\n");
        free(got);
    }
    {
        int a1[] = {1,3}, a2[] = {2,4};
        ListNode *lists[2] = {make_list(a1,2), make_list(a2,2)};
        int exp[] = {1,2,3,4}, rs = 0;
        int *got = mergeKLists(lists, 2, &rs);
        int ok = rs == 4 && memcmp(got, exp, 4*sizeof(int)) == 0;
        if (ok) passed++; else printf("  Test 7 (two lists): FAIL\n");
        if (ok) printf("  Test 7 (two lists): PASS\n");
        free(got);
    }
    {
        int a3[] = {1}, a5[] = {2};
        ListNode *lists[5] = {NULL, NULL, make_list(a3,1), NULL, make_list(a5,1)};
        int exp[] = {1,2}, rs = 0;
        int *got = mergeKLists(lists, 5, &rs);
        int ok = rs == 2 && memcmp(got, exp, 2*sizeof(int)) == 0;
        if (ok) passed++; else printf("  Test 8 (mixed empty and non-empty): FAIL\n");
        if (ok) printf("  Test 8 (mixed empty and non-empty): PASS\n");
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
