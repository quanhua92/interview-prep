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
#include <cstdio>
#include <cstring>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x = 0, ListNode *n = nullptr) : val(x), next(n) {}
};

static void merge_two(ListNode *a, ListNode *b, ListNode **out)
{
    abort();
}

static void divide_merge(std::vector<ListNode*> &lists, int left, int right, ListNode **out)
{
    abort();
}

static ListNode* make_list(const std::vector<int> &v)
{
    abort();
}

static std::vector<int> to_vec(ListNode *h)
{
    abort();
}

static void free_list(ListNode *h) {
    abort();
}

std::vector<int> mergeKLists(const std::vector<std::vector<int>> &lists_input)
{
    abort();
}

static void print_arr(const std::vector<int> &a)
{
    abort();
}

int main(void)
{
    printf("\n============================================================\n");
    printf("  23. Merge k Sorted Lists\n");
    printf("============================================================\n");
    int passed = 0, total = 8;

    {
        std::vector<int> exp = {1,1,2,3,4,4,5,6};
        auto got = mergeKLists({{1,4,5},{1,3,4},{2,6}});
        if (got == exp) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: "); print_arr(exp); printf("\n  Got:      "); print_arr(got); printf("\n"); }
    }
    {
        auto got = mergeKLists({});
        if (got.empty()) { passed++; printf("  Test 2 (empty input): PASS\n"); }
        else printf("  Test 2 (empty input): FAIL\n");
    }
    {
        auto got = mergeKLists({{}});
        if (got.empty()) { passed++; printf("  Test 3 (single empty list): PASS\n"); }
        else printf("  Test 3 (single empty list): FAIL\n");
    }
    {
        std::vector<int> exp = {1,2,3};
        auto got = mergeKLists({{1,2,3}});
        if (got == exp) { passed++; printf("  Test 4 (single list): PASS\n"); }
        else printf("  Test 4 (single list): FAIL\n");
    }
    {
        std::vector<int> exp = {1,1,1,1,1,1};
        auto got = mergeKLists({{1,1},{1,1},{1,1}});
        if (got == exp) { passed++; printf("  Test 5 (all same values): PASS\n"); }
        else printf("  Test 5 (all same values): FAIL\n");
    }
    {
        std::vector<int> exp = {-6,-5,-4,-3,-2,0};
        auto got = mergeKLists({{-5,-3},{-4,-2},{-6,0}});
        if (got == exp) { passed++; printf("  Test 6 (negative values): PASS\n"); }
        else printf("  Test 6 (negative values): FAIL\n");
    }
    {
        std::vector<int> exp = {1,2,3,4};
        auto got = mergeKLists({{1,3},{2,4}});
        if (got == exp) { passed++; printf("  Test 7 (two lists): PASS\n"); }
        else printf("  Test 7 (two lists): FAIL\n");
    }
    {
        std::vector<int> exp = {1,2};
        auto got = mergeKLists({{},{},{1},{},{2}});
        if (got == exp) { passed++; printf("  Test 8 (mixed empty and non-empty): PASS\n"); }
        else printf("  Test 8 (mixed empty and non-empty): FAIL\n");
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
