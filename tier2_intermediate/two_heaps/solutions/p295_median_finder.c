/*
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
 * Implement the MedianFinder class:
 *
 * Example 1:
 *     Input
 *     ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
 *     [[], [1], [2], [], [3], []]
 *     Output
 *     [null, null, null, 1.5, null, 2.0]
 *
 *     Explanation
 *     MedianFinder medianFinder = new MedianFinder();
 *     medianFinder.addNum(1);    // arr = [1]
 *     medianFinder.addNum(2);    // arr = [1, 2]
 *     medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
 *     medianFinder.addNum(3);    // arr[1, 2, 3]
 *     medianFinder.findMedian(); // return 2.0
 *
 * Constraints:
 *     - -105 <= num <= 105
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 104 calls will be made to addNum and findMedian.
 *
 * Template (python3):
 *     class MedianFinder:
 *
 *         def __init__(self):
 *
 *
 *         def addNum(self, num: int) -> None:
 *
 *
 *         def findMedian(self) -> float:
 *
 *
 *
 *     # Your MedianFinder object will be instantiated and called as such:
 *     # obj = MedianFinder()
 *     # obj.addNum(num)
 *     # param_2 = obj.findMedian()
 *
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100005

static int small[MAX_N], large[MAX_N];
static int sn, ln;

static void push_small(int v) { small[sn++] = v; }
static void push_large(int v) { large[ln++] = v; }

static void sift_up_small(int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (small[p] < small[i]) { int t = small[p]; small[p] = small[i]; small[i] = t; i = p; }
        else break;
    }
}

static void sift_down_small(int i)
{
    while (1) {
        int s = i, l = 2*i+1, r = 2*i+2;
        if (l < sn && small[l] > small[s]) s = l;
        if (r < sn && small[r] > small[s]) s = r;
        if (s != i) { int t = small[s]; small[s] = small[i]; small[i] = t; i = s; }
        else break;
    }
}

static void sift_up_large(int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (large[p] > large[i]) { int t = large[p]; large[p] = large[i]; large[i] = t; i = p; }
        else break;
    }
}

static void sift_down_large(int i)
{
    while (1) {
        int s = i, l = 2*i+1, r = 2*i+2;
        if (l < ln && large[l] < large[s]) s = l;
        if (r < ln && large[r] < large[s]) s = r;
        if (s != i) { int t = large[s]; large[s] = large[i]; large[i] = t; i = s; }
        else break;
    }
}

static void add_num(int num)
{
    push_small(num);
    sift_up_small(sn - 1);
    push_large(small[0]);
    small[0] = small[--sn]; sift_down_small(0);
    sift_up_large(ln - 1);
    if (ln > sn) {
        push_small(large[0]);
        sift_up_small(sn - 1);
        large[0] = large[--ln]; sift_down_large(0);
    }
}

static double find_median(void)
{
    if (sn > ln) return (double)small[0];
    if (ln > sn) return (double)large[0];
    return (small[0] + large[0]) / 2.0;
}

double *solve(int *stream, int n, int *ret_size)
{
    sn = ln = 0;
    double *res = malloc(n * sizeof(double));
    *ret_size = n;
    for (int i = 0; i < n; i++) {
        add_num(stream[i]);
        res[i] = find_median();
    }
    return res;
}

static int feq(double a, double b)
{
    return fabs(a - b) < 1e-9;
}

int main(void)
{
    struct {
        const char *label;
        int input[10];
        int n;
        double expected[10];
        int en;
    } tests[] = {
        {"stream median", {5, 15, 1, 3}, 4, {5.0, 10.0, 5.0, 4.0}, 4},
        {"two elements", {1, 2}, 2, {1.0, 1.5}, 2},
        {"single element", {42}, 1, {42.0}, 1},
        {"all same", {3, 3, 3, 3}, 4, {3.0, 3.0, 3.0, 3.0}, 4},
        {"negative numbers", {-5, -3, -1, 0}, 4, {-5.0, -4.0, -3.0, -2.0}, 4},
        {"alternating high low", {100, 0, 100, 0, 100, 0}, 6, {100.0, 50.0, 100.0, 50.0, 100.0, 50.0}, 6},
        {"descending order", {10, 9, 8, 7, 6, 5}, 6, {10.0, 9.5, 9.0, 8.5, 8.0, 7.5}, 6},
        {"extreme values", {-100000, 100000}, 2, {-100000.0, 0.0}, 2},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  295. Find Median from Data Stream\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int ret_size = 0;
        double *got = solve(tests[i].input, tests[i].n, &ret_size);
        int ok = ret_size == tests[i].en;
        if (ok) {
            for (int j = 0; j < ret_size; j++) {
                if (!feq(got[j], tests[i].expected[j])) { ok = 0; break; }
            }
        }
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: [");
            for (int j = 0; j < tests[i].en; j++) { if (j) printf(","); printf("%.1f", tests[i].expected[j]); }
            printf("]\n    Got:      [");
            if (got) for (int j = 0; j < ret_size; j++) { if (j) printf(","); printf("%.1f", got[j]); }
            printf("]\n");
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
