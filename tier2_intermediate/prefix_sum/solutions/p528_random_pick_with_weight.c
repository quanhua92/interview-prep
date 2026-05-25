/*
 * P528: Random Pick with Weight [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-pick-with-weight/
 * Topics: Array, Math, Binary Search, Prefix Sum, Randomized
 *
 * You are given a 0-indexed array of positive integers w where w[i] describes the weight of the ith index.
 * You need to implement the function pickIndex(), which randomly picks an index in the range [0, w.length - 1] (inclusive) and returns it. The probability of picking an index i is w[i] / sum(w).
 * Example 2:
 *     Input
 * Example 1:
 *     ["Solution","pickIndex"]
 *     [[[1]],[]]
 *     Output
 *     [null,0]
 *
 *     Explanation
 *     Solution solution = new Solution([1]);
 *     solution.pickIndex(); // return 0. The only option is to return 0 since there is only one element in w.
 *
 *     Input
 * Example 2:
 *     ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
 *     [[[1,3]],[],[],[],[],[]]
 *     Output
 *     [null,1,1,1,1,0]
 *
 *     Explanation
 *     Solution solution = new Solution([1, 3]);
 *     solution.pickIndex(); // return 1. It is returning the second element (index = 1) that has a probability of 3/4.
 *     solution.pickIndex(); // return 1
 *     solution.pickIndex(); // return 1
 *     solution.pickIndex(); // return 1
 *     solution.pickIndex(); // return 0. It is returning the first element (index = 0) that has a probability of 1/4.
 *
 *     Since this is a randomization problem, multiple answers are allowed.
 *     All of the following outputs can be considered correct:
 *     [null,1,1,1,1,0]
 *     [null,1,1,1,1,1]
 *     [null,1,1,1,0,0]
 *     [null,1,1,1,0,1]
 *     [null,1,0,1,0,0]
 *     ......
 *     and so on.
 *
 * Constraints:
 *     - 1 <= w.length <= 104
 *     - 1 <= w[i] <= 105
 *     - pickIndex will be called at most 104 times.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, w: List[int]):
 *
 *
 *         def pickIndex(self) -> int:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(w)
 *     # param_1 = obj.pickIndex()
 */

#include "ctest.h"
#include <stdlib.h>

int *random_pick_with_weight(int *w, int wSize, int target, int *retSize)
{
    (void)target;
    int *prefix = (int *)malloc(wSize * sizeof(int));
    prefix[0] = w[0];
    for (int i = 1; i < wSize; i++) {
        prefix[i] = prefix[i - 1] + w[i];
    }
    *retSize = wSize;
    return prefix;
}

int main(void)
{
    TestCase tests[] = {
        {"prefix sum for [1]", {1}, 1, 0, {1}, 1},
        {"prefix sum for [1, 3]", {1, 3}, 2, 0, {1, 4}, 2},
        {"prefix sum for [3, 14, 1, 7]", {3, 14, 1, 7}, 4, 0, {3, 17, 18, 25}, 4},
        {"single large weight", {5}, 1, 0, {5}, 1},
        {"equal weights", {10, 10, 10}, 3, 0, {10, 20, 30}, 3},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    RUN_TESTS("528. Random Pick with Weight", random_pick_with_weight, tests, n);
}
