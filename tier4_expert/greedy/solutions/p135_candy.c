/*
 * P135: Candy (Hard)
 * https://leetcode.com/problems/candy/
 * Topics: Array, Greedy
 *
 * There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
 * You are giving candies to these children subjected to the following requirements:
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 *
 * Example 1:
 *     Input: ratings = [1,0,2]
 *     Output: 5
 *
 * Example 2:
 *     Input: ratings = [1,2,2]
 *     Output: 4
 *
 * Constraints:
 *     - n == ratings.length
 *     - 1 <= n <= 2 * 104
 *     - 0 <= ratings[i] <= 2 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def candy(self, ratings: List[int]) -> int:
 *
 * Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
 */


#include "ctest.h"
#include <stdlib.h>

int candy(int *ratings, int ratingsSize) {
    if (ratingsSize == 1) return 1;
    int *candies = (int *)malloc((size_t)ratingsSize * sizeof(int));
    for (int i = 0; i < ratingsSize; i++) candies[i] = 1;
    for (int i = 1; i < ratingsSize; i++) {
        if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
    }
    for (int i = ratingsSize - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1])
            candies[i] = candies[i + 1] + 1;
    }
    int total = 0;
    for (int i = 0; i < ratingsSize; i++) total += candies[i];
    free(candies);
    return total;
}

int main(void) {
    int n;
    int *ratings = read_ints(&n);
    int result = candy(ratings, n);
    write_int(result);
    free(ratings);
    return 0;
}
