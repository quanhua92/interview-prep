/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 *
 * Constraints:
 *     - 1 <= k <= 105
 *     - 0 <= w <= 109
 *     - 1 <= n <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
 */


#include "io.h"
#include <stdlib.h>

typedef struct { int capital, profit; } Project;

int cmp_project(const void *a, const void *b) {
    return ((const Project *)a)->capital - ((const Project *)b)->capital;
}

static void heap_push(int *heap, int *sz, int val) {
    int i = (*sz)++;
    heap[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] >= heap[i]) break;
        int tmp = heap[p]; heap[p] = heap[i]; heap[i] = tmp;
        i = p;
    }
}

static int heap_pop(int *heap, int *sz) {
    int top = heap[0];
    heap[0] = heap[--(*sz)];
    int i = 0;
    while (1) {
        int largest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < *sz && heap[l] > heap[largest]) largest = l;
        if (r < *sz && heap[r] > heap[largest]) largest = r;
        if (largest == i) break;
        int tmp = heap[i]; heap[i] = heap[largest]; heap[largest] = tmp;
        i = largest;
    }
    return top;
}

int findMaximizedCapital(int k, int w, int *profits, int *capital, int n) {
    abort();
}

int main(void) {
    int k_n, w_n, p_n, c_n;
    int *k_arr = read_ints(&k_n);
    int *w_arr = read_ints(&w_n);
    int *profits = read_ints(&p_n);
    int *capital = read_ints(&c_n);
    int k = k_arr[0], w = w_arr[0];
    int result = findMaximizedCapital(k, w, profits, capital, p_n);
    write_int(result);
    free(k_arr); free(w_arr); free(profits); free(capital);
    return 0;
}
