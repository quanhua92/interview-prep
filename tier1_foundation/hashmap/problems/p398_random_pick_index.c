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
 *     - 1 <= nums.length <= 2 * 10^4
 *     - -2^31 <= nums[i] <= 2^31 - 1
 *     - target is an integer from nums.
 *     - At most 10^4 calls will be made to pick.
 */

#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UNIQUE 20005

typedef struct {
    int key;
    int *indices;
    int count;
    int cap;
} Entry;

typedef struct {
    Entry *entries;
    int size;
    int cap;
} Solution;

static void solution_init(Solution *sol, const int *nums, int n) {
    sol->cap = 64;
    sol->entries = malloc(sol->cap * sizeof(Entry));
    sol->size = 0;
    for (int i = 0; i < n; i++) {
        int key = nums[i];
        int j;
        for (j = 0; j < sol->size; j++) {
            if (sol->entries[j].key == key) break;
        }
        if (j == sol->size) {
            if (sol->size >= sol->cap) {
                sol->cap *= 2;
                sol->entries = realloc(sol->entries, sol->cap * sizeof(Entry));
            }
            sol->entries[j].key = key;
            sol->entries[j].count = 0;
            sol->entries[j].cap = 8;
            sol->entries[j].indices = malloc(8 * sizeof(int));
            sol->size++;
        }
        Entry *e = &sol->entries[j];
        if (e->count >= e->cap) {
            e->cap *= 2;
            e->indices = realloc(e->indices, e->cap * sizeof(int));
        }
        e->indices[e->count++] = i;
    }
}

static int solution_pick(Solution *sol, int target) {
    abort();
}

static void solution_free(Solution *sol) {
    for (int i = 0; i < sol->size; i++)
        free(sol->entries[i].indices);
}

int main(void)
{
    srand(42);
    int n;
    int *nums = read_ints(&n);
    int target = read_int();

    Solution sol;
    solution_init(&sol, nums, n);
    int result = solution_pick(&sol, target);
    write_int(result);

    solution_free(&sol);
    free(nums);
    return 0;
}
