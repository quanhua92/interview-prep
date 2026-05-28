/*
 * P338: Counting Bits (Easy)
 * https://leetcode.com/problems/counting-bits/
 * Topics: Dynamic Programming, Bit Manipulation
 *
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 *
 * Example 1:
 *     Input: n = 2
 *     Output: [0,1,1]
 *     Explanation:
 *     0 --> 0
 *     1 --> 1
 *     2 --> 10
 *
 * Example 2:
 *     Input: n = 5
 *     Output: [0,1,1,2,1,2]
 *     Explanation:
 *     0 --> 0
 *     1 --> 1
 *     2 --> 10
 *     3 --> 11
 *     4 --> 100
 *     5 --> 101
 *
 * Constraints:
 *     - 0 <= n <= 105
 *
 * Hints:
 *     - You should make use of what you have produced already.
 *     - Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
 *     - Or does the odd/even status of the number help you in calculating the number of 1s?
 *
 * Template (python3):
 *     class Solution:
 *         def countBits(self, n: int) -> List[int]:
 *
 * Hint: DP approach: ans[i] = ans[i >> 1] + (i & 1).
 */

#include "io.h"
#include <stdlib.h>

static int *countBits(int n, int *returnSize) {
    int *ans = (int *)malloc(((size_t)n + 1) * sizeof(int));
    ans[0] = 0;
    for (int i = 1; i <= n; i++) {
        ans[i] = ans[i >> 1] + (i & 1);
    }
    *returnSize = n + 1;
    return ans;
}

int main(void) {
    int c; int *a = read_ints(&c); int n = a[0]; free(a);
    int retSize = 0;
    int *result = countBits(n, &retSize);
    write_ints(result, retSize);
    free(result);
    return 0;
}
