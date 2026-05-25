/*
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 * 
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
 * 
 * Example 1:
 *     Input: arr = [3,1,2,4]
 *     Output: 17
 *     Explanation:
 *     Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
 *     Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
 *     Sum is 17.
 * 
 * Example 2:
 *     Input: arr = [11,81,94,43,3]
 *     Output: 444
 * 
 * Constraints:
 *     - 1 <= arr.length <= 3 * 104
 *     - 1 <= arr[i] <= 3 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def sumSubarrayMins(self, arr: List[int]) -> int:
 * 
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

static const long long MOD = 1000000007LL;

int sumSubarrayMins(const std::vector<int> &arr)
{
    abort();
}

int main(void)
{
    struct TC { const char *label; std::vector<int> input; int expected; };
    TC tests[] = {
        {"example 1", {3, 1, 2, 4}, 17},
        {"example 2", {11, 81, 94, 43, 3}, 444},
        {"single element", {1}, 1},
        {"two elements", {2, 1}, 4},
        {"all same", {3, 3, 3}, 18},
        {"strictly increasing", {1, 2, 3}, 10},
        {"strictly decreasing", {3, 2, 1}, 10},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  907. Sum of Subarray Minimums\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = sumSubarrayMins(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d, Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
