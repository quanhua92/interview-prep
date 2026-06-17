/*
 * P519: Random Flip Matrix [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-flip-matrix/
 * Topics: Hash Table, Math, Reservoir Sampling, Randomized
 *
 * There is an m x n binary grid matrix with all the values set 0 initially. Design an algorithm to randomly pick an index (i, j) where matrix[i][j] == 0 and flips it to 1. All the indices (i, j) where matrix[i][j] == 0 should be equally likely to be returned.
 * Optimize your algorithm to minimize the number of calls made to the built-in random function of your language and optimize the time and space complexity.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "flip", "flip", "flip", "reset", "flip"]
 *     [[3, 1], [], [], [], [], []]
 *     Output
 *     [null, [1, 0], [2, 0], [0, 0], null, [2, 0]]
 *
 *     Explanation
 *     Solution solution = new Solution(3, 1);
 *     solution.flip();  // return [1, 0], [0,0], [1,0], and [2,0] should be equally likely to be returned.
 *     solution.flip();  // return [2, 0], Since [1,0] was returned, [2,0] and [0,0]
 *     solution.flip();  // return [0, 0], Based on the previously returned indices, only [0,0] can be returned.
 *     solution.reset(); // All the values are reset to 0 and can be returned.
 *     solution.flip();  // return [2, 0], [0,0], [1,0], and [2,0] should be equally likely to be returned.
 *
 * Constraints:
 *     - 1 <= m, n <= 10^4
 *     - There will be at least one free cell for each call to flip.
 *     - At most 1000 calls will be made to flip and reset.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, m: int, n: int):
 *
 *
 *         def flip(self) -> List[int]:
 *
 *
 *         def reset(self) -> None:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(m, n)
 *     # param_1 = obj.flip()
 *     # obj.reset()
 */

#include "io.h"
#include <stdlib.h>

typedef struct {
    int m, n, total;
    int cap, count;
    int *keys;  /* -1 = empty slot */
    int *vals;
} Solution;

static int map_get(Solution *s, int key, int def) {
    if (s->cap == 0) return def;
    int mask = s->cap - 1;
    int i = (unsigned)key * 2654435761u & mask;
    while (s->keys[i] != -1) {
        if (s->keys[i] == key) return s->vals[i];
        i = (i + 1) & mask;
    }
    return def;
}

static void map_set(Solution *s, int key, int val) {
    if (s->cap == 0 || s->count * 4 >= s->cap * 3) {
        int newcap = s->cap == 0 ? 16 : s->cap * 2;
        int *oldk = s->keys, *oldv = s->vals;
        int oldcap = s->cap;
        s->cap = newcap;
        s->keys = (int *)malloc(newcap * sizeof(int));
        s->vals = (int *)malloc(newcap * sizeof(int));
        for (int i = 0; i < newcap; i++) s->keys[i] = -1;
        s->count = 0;
        for (int i = 0; i < oldcap; i++) {
            if (oldk[i] != -1) {
                int mask = newcap - 1;
                int j = (unsigned)oldk[i] * 2654435761u & mask;
                while (s->keys[j] != -1) j = (j + 1) & mask;
                s->keys[j] = oldk[i];
                s->vals[j] = oldv[i];
                s->count++;
            }
        }
        free(oldk);
        free(oldv);
    }
    int mask = s->cap - 1;
    int i = (unsigned)key * 2654435761u & mask;
    while (s->keys[i] != -1 && s->keys[i] != key) {
        i = (i + 1) & mask;
    }
    if (s->keys[i] == -1) {
        s->count++;
        s->keys[i] = key;
    }
    s->vals[i] = val;
}

static void solution_init(Solution *s, int m, int n) {
    s->m = m;
    s->n = n;
    s->total = m * n;
    s->cap = 0;
    s->count = 0;
    s->keys = NULL;
    s->vals = NULL;
}

static void solution_flip(Solution *s, int *out_r, int *out_c) {
    int r = rand() % s->total;
    int x = map_get(s, r, r);
    int last = s->total - 1;
    int last_val = map_get(s, last, last);
    map_set(s, r, last_val);
    s->total--;
    *out_r = x / s->n;
    *out_c = x % s->n;
}

static void solution_reset(Solution *s) {
    s->total = s->m * s->n;
    if (s->keys) {
        for (int i = 0; i < s->cap; i++) s->keys[i] = -1;
    }
    s->count = 0;
}

int main(void)
{
    srand(42);
    int m = read_int();
    int n = read_int();
    int num_flips = read_int();
    Solution sol;
    solution_init(&sol, m, n);
    for (int i = 0; i < num_flips; i++) {
        int r, c;
        solution_flip(&sol, &r, &c);
        int pt[2] = {r, c};
        write_ints(pt, 2);
    }
    return 0;
}
