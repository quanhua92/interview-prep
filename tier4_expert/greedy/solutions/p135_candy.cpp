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


#include "cpptest.h"

int candy(const std::vector<int> &ratings) {
    int n = (int)ratings.size();
    if (n == 1) return 1;
    std::vector<int> c(n, 1);
    for (int i = 1; i < n; i++)
        if (ratings[i] > ratings[i - 1]) c[i] = c[i - 1] + 1;
    for (int i = n - 2; i >= 0; i--)
        if (ratings[i] > ratings[i + 1] && c[i] <= c[i + 1]) c[i] = c[i + 1] + 1;
    int total = 0;
    for (int i = 0; i < n; i++) total += c[i];
    return total;
}

int main() {
    std::vector<int> ratings = read_ints();
    int result = candy(ratings);
    write_int(result);
    return 0;
}
