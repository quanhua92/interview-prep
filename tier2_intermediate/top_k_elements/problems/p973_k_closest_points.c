/*
 * P973: K Closest Points to Origin (Medium)
 * https://leetcode.com/problems/k-closest-points-to-origin/
 * Topics: Array, Math, Divide and Conquer, Geometry, Sorting, Heap (Priority Queue), Quickselect
 * 
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
 * The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
 * You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).
 * 
 * Example 1:
 *     Input: points = [[1,3],[-2,2]], k = 1
 *     Output: [[-2,2]]
 *     Explanation:
 *     The distance between (1, 3) and the origin is sqrt(10).
 *     The distance between (-2, 2) and the origin is sqrt(8).
 *     Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 *     We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
 * 
 * Example 2:
 *     Input: points = [[3,3],[5,-1],[-2,4]], k = 2
 *     Output: [[3,3],[-2,4]]
 *     Explanation: The answer [[-2,4],[3,3]] would also be accepted.
 * 
 * Constraints:
 *     - 1 <= k <= points.length <= 104
 *     - -104 <= xi, yi <= 104
 * 
 * Template (python3):
 *     class Solution:
 *         def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
 * 
 * Hint: Use a max-heap of size k keyed by negative distance squared.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int x, y; } Pt;

static int cmp_dist(const void *a, const void *b)
{
    /* TODO: Implement */
    return 0;
}

static int cmp_lex(const void *a, const void *b)
{
    /* TODO: Implement */
    return 0;
}

int *kClosest(int *points, int totalInts, int k, int *returnSize)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct {
        const char *label;
        int input[20];
        int n;
        int k;
        int expected[20];
        int expected_n;
    } tests[] = {
        {"example 1",       {1, 3, -2, 2},                  4, 1, {-2, 2},              2},
        {"example 2 (sorted)", {3, 3, 5, -1, -2, 4},       6, 2, {-2, 4, 3, 3},       4},
        {"origin itself",   {0, 0},                         2, 1, {0, 0},               2},
        {"tie on distance", {1, 0, 0, 1, 2, 0},             6, 2, {0, 1, 1, 0},        4},
        {"negative coords", {-1, -1, 2, 2, 3, 3},           6, 1, {-1, -1},            2},
        {"two tied closest", {1, 0, 0, 1, 2, 0},            6, 2, {0, 1, 1, 0},        4},
        {"all same point",  {1, 1, 1, 1, 1, 1},             6, 2, {1, 1, 1, 1},        4},
        {"origin is closest", {3, 4, 0, 0, 1, 1},           6, 1, {0, 0},               2},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  973. K Closest Points to Origin\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int ret_size = 0;
        int *got = kClosest(tests[i].input, tests[i].n, tests[i].k, &ret_size);
        if (got && ret_size == tests[i].expected_n &&
            memcmp(got, tests[i].expected, ret_size * sizeof(int)) == 0) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: [");
            for (int j = 0; j < tests[i].expected_n; j++) {
                if (j % 2 == 0 && j > 0) printf(",");
                if (j % 2 == 0) printf("[");
                printf("%d", tests[i].expected[j]);
                if (j % 2 == 1) printf("]");
            }
            printf("]\n    Got:      [");
            if (got) for (int j = 0; j < ret_size; j++) {
                if (j % 2 == 0 && j > 0) printf(",");
                if (j % 2 == 0) printf("[");
                printf("%d", got[j]);
                if (j % 2 == 1) printf("]");
            } else printf("NULL");
            printf("]\n");
        }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
