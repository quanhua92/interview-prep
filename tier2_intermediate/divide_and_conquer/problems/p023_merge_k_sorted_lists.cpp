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
 * Constraints:
 *     - k == lists.length
 *     - 0 <= k <= 104
 *     - 0 <= lists[i].length <= 500
 *
 * Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
 */


#include "io.h"
#include <vector>

static std::vector<int> merge_two(const std::vector<int> &a, const std::vector<int> &b)
{
    abort();
}

static std::vector<int> divide_merge(const std::vector<std::vector<int>> &lists, int left, int right)
{
    abort();
}

int main(void)
{
    int k = read_ints()[0];
    std::vector<std::vector<int>> lists(k);
    for (int i = 0; i < k; i++) {
        lists[i] = read_ints();
    }
    auto result = divide_merge(lists, 0, (int)lists.size() - 1);
    write_ints(result);
    return 0;
}
