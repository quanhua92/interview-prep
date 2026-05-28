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
 * Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
 */


#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void merge_two(int *a, int an, int *b, int bn, int **out, int *on)
{
    abort();
}

static void divide_merge(int **lists, int *sizes, int left, int right, int **out, int *on)
{
    abort();
}

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

    int *result; int rn;
    divide_merge(lists, sizes, 0, k - 1, &result, &rn);

    if (rn > 0) write_ints(result, rn);
    else { printf("\n"); }

    for (int i = 0; i < k; i++) free(lists[i]);
    free(lists);
    free(sizes);
    free(result);
    return 0;
}
