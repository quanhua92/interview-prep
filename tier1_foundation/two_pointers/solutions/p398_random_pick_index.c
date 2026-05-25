/*
 * P398: Random Pick Index [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-pick-index/
 * Topics: Hash Table, Math, Reservoir Sampling, Randomized
 *
 * Given an integer array nums with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "pick", "pick", "pick"]
 *     [[[1, 2, 3, 3, 3]], [3], [1], [3]]
 *     Output
 *     [null, 4, 0, 2]
 *
 *     Explanation
 *     Solution solution = new Solution([1, 2, 3, 3, 3]);
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 *     solution.pick(1); // It should return 0. Since in the array only nums[0] is equal to 1.
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 *
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -231 <= nums[i] <= 231 - 1
 *     - target is an integer from nums.
 *     - At most 104 calls will be made to pick.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, nums: List[int]):
 *
 *
 *         def pick(self, target: int) -> int:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(nums)
 *     # param_1 = obj.pick(target)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmp_int(const void *a, const void *b) { return *(const int *)a - *(const int *)b; }

int *pickIndex(const int *nums, int n, int target, int *return_size)
{
    int *indices = malloc(n * sizeof(int));
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == target) indices[count++] = i;
    }
    *return_size = count;
    return indices;
}

int main(void)
{
    struct {
        const char *label;
        int input[10];
        int n;
        int target;
        int expected[10];
        int expected_n;
    } tests[] = {
        {"returns valid indices for target 3", {1, 2, 3, 3, 3}, 5, 3, {2, 3, 4}, 3},
        {"returns valid indices for target 1", {1, 2, 3, 3, 3}, 5, 1, {0}, 1},
        {"single element array",              {5},              1, 5, {0}, 1},
        {"non-contiguous duplicates",         {1, 2, 1, 2, 1}, 5, 1, {0, 2, 4}, 3},
        {"negative numbers with duplicates",  {-1, -2, -1, -3, -1}, 5, -1, {0, 2, 4}, 3},
        {"all same elements",                 {1, 1, 1, 1, 1}, 5, 1, {0, 1, 2, 3, 4}, 5},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  398. Random Pick Index\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got_n = 0;
        int *got = pickIndex(tests[i].input, tests[i].n, tests[i].target, &got_n);
        if (got_n == tests[i].expected_n) {
            int *sorted_got = malloc(got_n * sizeof(int));
            int *sorted_exp = malloc(tests[i].expected_n * sizeof(int));
            memcpy(sorted_got, got, got_n * sizeof(int));
            memcpy(sorted_exp, tests[i].expected, tests[i].expected_n * sizeof(int));
            qsort(sorted_got, got_n, sizeof(int), cmp_int);
            qsort(sorted_exp, tests[i].expected_n, sizeof(int), cmp_int);
            int ok = memcmp(sorted_got, sorted_exp, got_n * sizeof(int)) == 0;
            free(sorted_got);
            free(sorted_exp);
            if (ok) {
                passed++;
                printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
            } else {
                printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            }
        } else {
            printf("  Test %d (%s): FAIL (size mismatch)\n", i + 1, tests[i].label);
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
