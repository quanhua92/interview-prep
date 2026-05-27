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
#include <stdlib.h>

int main(void)
{
    int kn;
    int *kdata = read_ints(&kn);
    int k = kdata[0];
    free(kdata);

    int *sizes = malloc(k * sizeof(int));
    int **lists = malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        lists[i] = read_ints(&sizes[i]);
    }

    abort();

    free(lists);
    free(sizes);
    return 0;
}
