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
    ListNode dummy;
    ListNode *cur = &dummy;
    while (a && b) {
        if (a->val <= b->val) { cur->next = a; a = a->next; }
        else { cur->next = b; b = b->next; }
        cur = cur->next;
    }
    cur->next = a ? a : b;
    *out = dummy.next;
}

static void divide_merge(std::vector<ListNode*> &lists, int left, int right, ListNode **out)
{
    if (left > right) { *out = nullptr; return; }
    if (left == right) { *out = lists[left]; return; }
    int mid = left + (right - left) / 2;
    ListNode *lh, *rh;
    divide_merge(lists, left, mid, &lh);
    divide_merge(lists, mid + 1, right, &rh);
    merge_two(lh, rh, out);
}

static ListNode* make_list(const std::vector<int> &v)
{
    if (v.empty()) return nullptr;
    ListNode *head = new ListNode(v[0]);
    ListNode *cur = head;
    for (size_t i = 1; i < v.size(); i++) { cur->next = new ListNode(v[i]); cur = cur->next; }
    return head;
}

static std::vector<int> to_vec(ListNode *h)
{
    std::vector<int> v;
    while (h) { v.push_back(h->val); h = h->next; }
    return v;
}

static void free_list(ListNode *h) { while (h) { auto *n = h->next; delete h; h = n; } }

std::vector<int> mergeKLists(const std::vector<std::vector<int>> &lists_input)
{
    if (lists_input.empty()) return {};
    std::vector<ListNode*> lists;
    for (auto &l : lists_input) lists.push_back(make_list(l));
    ListNode *merged;
    divide_merge(lists, 0, (int)lists.size() - 1, &merged);
    auto result = to_vec(merged);
    free_list(merged);
    return result;
}

static void print_arr(const std::vector<int> &a)
{
    printf("["); for (size_t i = 0; i < a.size(); i++) { if (i) printf(","); printf("%d", a[i]); } printf("]");
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
