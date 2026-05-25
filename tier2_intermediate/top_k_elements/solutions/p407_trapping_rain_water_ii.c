/*
 * P407: Trapping Rain Water II [PREMIUM] (Hard)
 * https://leetcode.com/problems/trapping-rain-water-ii/
 * Topics: Array, Breadth-First Search, Heap (Priority Queue), Matrix
 *
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
 * Example 1:
 *     Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
 *     Output: 4
 *     Explanation: After the rain, water is trapped between the blocks.
 *     We have two small ponds 1 and 3 units trapped.
 *     The total volume of water trapped is 4.
 *
 * Example 2:
 *     Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
 *     Output: 10
 *
 * Constraints:
 *     - m == heightMap.length
 *     - n == heightMap[i].length
 *     - 1 <= m, n <= 200
 *     - 0 <= heightMap[i][j] <= 2 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def trapRainWater(self, heightMap: List[List[int]]) -> int:
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct { int h, r, c; } Cell;

static void heap_push(Cell *heap, int *sz, Cell val)
{
    int i = (*sz)++;
    heap[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].h <= heap[i].h) break;
        Cell tmp = heap[p];
        heap[p] = heap[i];
        heap[i] = tmp;
        i = p;
    }
}

static Cell heap_pop(Cell *heap, int *sz)
{
    Cell top = heap[0];
    heap[0] = heap[--(*sz)];
    int i = 0;
    while (1) {
        int s = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < *sz && heap[l].h < heap[s].h) s = l;
        if (r < *sz && heap[r].h < heap[s].h) s = r;
        if (s == i) break;
        Cell tmp = heap[s];
        heap[s] = heap[i];
        heap[i] = tmp;
        i = s;
    }
    return top;
}

int trapRainWater(int *heightMap, int m, int n)
{
    if (m < 3 || n < 3) return 0;

    char *visited = calloc(m * n, 1);
    Cell *heap = malloc(m * n * sizeof(Cell));
    int hsz = 0;

    for (int r = 0; r < m; r++) {
        heap_push(heap, &hsz, (Cell){heightMap[r * n], r, 0});
        visited[r * n] = 1;
        heap_push(heap, &hsz, (Cell){heightMap[r * n + n - 1], r, n - 1});
        visited[r * n + n - 1] = 1;
    }
    for (int c = 1; c < n - 1; c++) {
        heap_push(heap, &hsz, (Cell){heightMap[c], 0, c});
        visited[c] = 1;
        heap_push(heap, &hsz, (Cell){heightMap[(m - 1) * n + c], m - 1, c});
        visited[(m - 1) * n + c] = 1;
    }

    static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int water = 0;

    while (hsz > 0) {
        Cell cur = heap_pop(heap, &hsz);
        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dirs[d][0], nc = cur.c + dirs[d][1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr * n + nc]) {
                visited[nr * n + nc] = 1;
                int nh = heightMap[nr * n + nc];
                if (cur.h > nh) water += cur.h - nh;
                heap_push(heap, &hsz, (Cell){cur.h > nh ? cur.h : nh, nr, nc});
            }
        }
    }

    free(visited);
    free(heap);
    return water;
}

int main(void)
{
    struct {
        const char *label;
        int *input;
        int m, n;
        int expected;
    } tests[] = {
        {"example 1",     (int[]){1,4,3,1,3,2, 3,2,1,3,2,4, 2,3,3,2,3,1},       3, 6, 4},
        {"example 2",     (int[]){3,3,3,3,3, 3,2,2,2,3, 3,2,1,2,3, 3,2,2,2,3, 3,3,3,3,3}, 5, 5, 10},
        {"1x1 no trap",   (int[]){1},                                         1, 1, 0},
        {"3x3 basin",     (int[]){5,5,5, 5,1,5, 5,5,5},                       3, 3, 4},
        {"2x4 no interior", (int[]){5,5,5,5, 5,5,5,5},                       2, 4, 0},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  407. Trapping Rain Water II\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = trapRainWater(tests[i].input, tests[i].m, tests[i].n);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }

    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
