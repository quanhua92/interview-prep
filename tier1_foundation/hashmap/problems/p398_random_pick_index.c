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
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int *indices;
    int count;
    int cap;
} Entry;

typedef struct {
    Entry entries[20005];
    int size;
} Solution;

static void solution_init(Solution *sol, const int *nums, int n) {
    abort();
}

static int solution_pick(Solution *sol, int target) {
    abort();
    return -1;
}

static void solution_free(Solution *sol) {
    abort();
}

int main(void)
{
    struct {
        const char *label;
        int input[10];
        int n;
        int target;
        int valid[10];
        int valid_n;
    } tests[] = {
        {"returns valid indices for target 3", {1, 2, 3, 3, 3}, 5, 3, {2, 3, 4}, 3},
        {"single occurrence",                  {1, 2, 3, 3, 3}, 5, 1, {0}, 1},
        {"single element array",               {5},              1, 5, {0}, 1},
        {"non-contiguous duplicates",          {1, 2, 1, 2, 1}, 5, 1, {0, 2, 4}, 3},
        {"negative numbers with duplicates",   {-1, -2, -1, -3, -1}, 5, -1, {0, 2, 4}, 3},
        {"all same elements",                  {1, 1, 1, 1, 1}, 5, 1, {0, 1, 2, 3, 4}, 5},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  398. Random Pick Index\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        Solution sol;
        solution_init(&sol, tests[i].input, tests[i].n);
        int got = solution_pick(&sol, tests[i].target);
        int ok = 0;
        for (int j = 0; j < tests[i].valid_n; j++) {
            if (got == tests[i].valid[j]) { ok = 1; break; }
        }
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected one of: ");
            for (int j = 0; j < tests[i].valid_n; j++)
                printf("%d ", tests[i].valid[j]);
            printf("\n    Got:              %d\n", got);
        }
        solution_free(&sol);
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
