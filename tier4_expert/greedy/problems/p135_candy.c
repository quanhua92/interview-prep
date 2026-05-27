/*
 * P135: Candy (Hard)
 * https://leetcode.com/problems/candy/
 * Topics: Array, Greedy
 *
 * Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
 */


#include "ctest.h"

int candy(int *ratings, int ratingsSize) {
    abort();
}

int main(void) {
    int n;
    int *ratings = read_ints(&n);
    int result = candy(ratings, n);
    write_int(result);
    free(ratings);
    return 0;
}
