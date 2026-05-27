/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 */


#include "ctest.h"
#include <stdlib.h>

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
