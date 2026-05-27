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
 *     - 1 <= m, n <= 104
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
#include <string.h>

typedef struct { long long key; long long val; } MapEntry;

static long long map_get(MapEntry *map, int n, long long key, long long default_val)
{
    for (int i = 0; i < n; i++)
        if (map[i].key == key) return map[i].val;
    return default_val;
}

static void map_set(MapEntry *map, int *n, long long key, long long val)
{
    for (int i = 0; i < *n; i++) {
        if (map[i].key == key) { map[i].val = val; return; }
    }
    map[*n].key = key;
    map[*n].val = val;
    (*n)++;
}

static int solve(int m, int n, int num_flips)
{
    long long total = (long long)m * n;
    MapEntry mapping[10001];
    int map_n = 0;
    long long results[10001];
    int result_n = 0;

    for (int f = 0; f < num_flips; f++) {
        int r = f;
        total--;
        long long idx = map_get(mapping, map_n, r, r);
        long long last_val = map_get(mapping, map_n, total, total);
        map_set(mapping, &map_n, r, last_val);
        map_set(mapping, &map_n, total, last_val);
        results[result_n++] = idx;
    }

    int unique = 0;
    for (int i = 0; i < result_n; i++) {
        int is_dup = 0;
        for (int j = 0; j < i; j++)
            if (results[j] == results[i]) { is_dup = 1; break; }
        if (!is_dup) unique++;
    }
    return unique;
}

int main(void)
{
    int m = read_int();
    int n = read_int();
    int num_flips = read_int();
    write_int(solve(m, n, num_flips));
    return 0;
}
