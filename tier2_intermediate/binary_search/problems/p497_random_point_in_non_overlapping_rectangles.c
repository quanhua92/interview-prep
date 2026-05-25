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
 *     - -109 <= ai < xi <= 109
 *     - -109 <= bi < yi <= 109
 *     - xi - ai <= 2000
 *     - yi - bi <= 2000
 *     - All the rectangles do not overlap.
 *     - At most 104 calls will be made to pick.
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
#include <stdio.h>
#include <stdlib.h>

int *solve_prefix_sums(int **rects, int rectsSize, int *rectsColSize, int *ret_size)
{
    /* TODO: Implement */
    return 0;
}

static int arr_eq(const int *a, int an, const int *b, int bn)
{
    /* TODO: Implement */
    return 0;
}

static void print_arr(const int *a, int n)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct {
        const char *label;
        int rects[10][4];
        int n;
        int expected[10];
        int expected_n;
        int pass;
    } tests[] = {
        { "area sum for two rectangles", {{-2,-2,1,1},{2,2,4,6}}, 2, {16,31}, 2, 0 },
        { "area for single 3x3 rectangle", {{0,0,2,2}}, 1, {9}, 1, 0 },
        { "single point rectangle", {{0,0,0,0}}, 1, {1}, 1, 0 },
        { "negative and positive rects same size", {{-5,-5,-3,-3},{1,1,3,3}}, 2, {9,18}, 2, 0 },
        { "different sized rects", {{1,1,2,2},{3,3,5,5}}, 2, {4,13}, 2, 0 },
    };
    int tn = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    for (int i = 0; i < tn; i++) {
        int *env_ptrs[10];
        int colSizes[10];
        for (int j = 0; j < tests[i].n; j++) {
            env_ptrs[j] = tests[i].rects[j];
            colSizes[j] = 4;
        }
        int ret_size = 0;
        int *got = solve_prefix_sums(env_ptrs, tests[i].n, colSizes, &ret_size);
        tests[i].pass = arr_eq(got, ret_size, tests[i].expected, tests[i].expected_n);
        if (!tests[i].pass) {
            printf("    Expected: "); print_arr(tests[i].expected, tests[i].expected_n);
            printf("\n    Got:      "); print_arr(got, ret_size); printf("\n");
        }
        if (tests[i].pass) passed++;
        free(got);
    }

    printf("\n============================================================\n");
    printf("  497. Random Point in Non-overlapping Rectangles\n");
    printf("============================================================\n");
    for (int i = 0; i < tn; i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, tn);
    printf("============================================================\n");
    return passed == tn ? 0 : 1;
}
