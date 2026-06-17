/*
 * P497: Random Point in Non-overlapping Rectangles [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/
 * Topics: Array, Math, Binary Search, Reservoir Sampling, Prefix Sum, Ordered Set, Randomized
 *
 * You are given an array of non-overlapping axis-aligned rectangles rects where rects[i] = [ai, bi, xi, yi] indicates that (ai, bi) is the bottom-left corner point of the ith rectangle and (xi, yi) is the top-right corner point of the ith rectangle. Design an algorithm to pick a random integer point inside the space covered by one of the given rectangles. A point on the perimeter of a rectangle is included in the space covered by the rectangle.
 * Any integer point inside the space covered by one of the given rectangles should be equally likely to be returned.
 * Note that an integer point is a point that has integer coordinates.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "pick", "pick", "pick", "pick", "pick"]
 *     [[[[-2, -2, 1, 1], [2, 2, 4, 6]]], [], [], [], [], []]
 *     Output
 *     [null, [1, -2], [1, -1], [-1, -2], [-2, -2], [0, 0]]
 *
 *     Explanation
 *     Solution solution = new Solution([[-2, -2, 1, 1], [2, 2, 4, 6]]);
 *     solution.pick(); // return [1, -2]
 *     solution.pick(); // return [1, -1]
 *     solution.pick(); // return [-1, -2]
 *     solution.pick(); // return [-2, -2]
 *     solution.pick(); // return [0, 0]
 *
 * Constraints:
 *     - 1 <= rects.length <= 100
 *     - rects[i].length == 4
 *     - -10^9 <= ai < xi <= 10^9
 *     - -10^9 <= bi < yi <= 10^9
 *     - xi - ai <= 2000
 *     - yi - bi <= 2000
 *     - All the rectangles do not overlap.
 *     - At most 10^4 calls will be made to pick.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, rects: List[List[int]]):
 *
 *
 *         def pick(self) -> List[int]:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(rects)
 *     # param_1 = obj.pick()
 */

#include "io.h"
#include <stdlib.h>

typedef struct {
    int n;       /* number of rectangles */
    int *rects;  /* flattened: 4*n ints (x1,y1,x2,y2 per rect) */
    int *prefix; /* cumulative point counts, length n */
    int total;   /* grand total point count */
} Solution;

static void solution_init(Solution *sol, int *rects, int n) {
    (void)sol; (void)rects; (void)n;
    abort();
}

static void solution_pick(Solution *sol, int *out_x, int *out_y) {
    (void)sol; (void)out_x; (void)out_y;
    abort();
}

int main(void)
{
    srand(42);
    int n = read_int();
    int *rects = (int *)malloc(4 * n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int rc;
        int *row = read_ints(&rc);
        rects[4 * i]     = row[0];
        rects[4 * i + 1] = row[1];
        rects[4 * i + 2] = row[2];
        rects[4 * i + 3] = row[3];
        free(row);
    }
    Solution sol;
    solution_init(&sol, rects, n);
    int x, y;
    solution_pick(&sol, &x, &y);
    int pt[2] = {x, y};
    write_ints(pt, 2);
    free(rects);
    return 0;
}
