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
 *
 * Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
 */

#include "io.h"
#include <vector>

std::vector<int> mergeKLists(const std::vector<std::vector<int>> &lists)
{
    abort();
}

int main(void)
{
    int k = read_int();
    std::vector<std::vector<int>> lists(k);
    for (int i = 0; i < k; i++) {
        lists[i] = read_ints();
    }
    auto result = mergeKLists(lists);
    write_ints(result);
    return 0;
}
