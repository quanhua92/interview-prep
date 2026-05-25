/*
 * P480: Sliding Window Median (Hard)
 * https://leetcode.com/problems/sliding-window-median/
 * Topics: Array, Hash Table, Sliding Window, Heap (Priority Queue)
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
 * You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
 * Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
 *
 * Example 1:
 *     Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 *     Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
 *     Explanation:
 *     Window position                Median
 *     ---------------                -----
 *     [1  3  -1] -3  5  3  6  7        1
 *      1 [3  -1  -3] 5  3  6  7       -1
 *      1  3 [-1  -3  5] 3  6  7       -1
 *      1  3  -1 [-3  5  3] 6  7        3
 *      1  3  -1  -3 [5  3  6] 7        5
 *      1  3  -1  -3  5 [3  6  7]       6
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
 *     Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -231 <= nums[i] <= 231 - 1
 *
 * Hints:
 *     - The simplest of solutions comes from the basic idea of finding the median given a set of numbers. We know that by definition, a median is the center element (or an average of the two center elements). Given an unsorted list of numbers, how do we find the median element? If you know the answer to this question, can we extend this idea to every sliding window that we come across in the array?
 *     - Is there a better way to do what we are doing in the above hint? Don't you think there is duplication of calculation being done there? Is there some sort of optimization that we can do to achieve the same result? This approach is merely a modification of the basic approach except that it simply reduces duplication of calculations once done.
 *     - The third line of thought is also based on this same idea but achieving the result in a different way. We obviously need the window to be sorted for us to be able to find the median. Is there a data-structure out there that we can use (in one or more quantities) to obtain the median element extremely fast, say O(1) time while having the ability to perform the other operations fairly efficiently as well?
 *
 * Template (python3):
 *     class Solution:
 *         def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
 *
 * Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 100005

typedef long long ll;

typedef struct { ll val; int idx; } HEntry;

static HEntry small[MAX_N], large[MAX_N];
static int sn, ln;
static int delayed[MAX_N];
static int in_small_flag[MAX_N];
static int small_sz, large_sz;

static void sift_up_small(int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (small[p].val < small[i].val) { HEntry t = small[p]; small[p] = small[i]; small[i] = t; i = p; }
        else break;
    }
}

static void sift_down_small(int i)
{
    while (1) {
        int s = i, l = 2*i+1, r = 2*i+2;
        if (l < sn && small[l].val > small[s].val) s = l;
        if (r < sn && small[r].val > small[s].val) s = r;
        if (s != i) { HEntry t = small[s]; small[s] = small[i]; small[i] = t; i = s; }
        else break;
    }
}

static void sift_up_large(int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (large[p].val > large[i].val) { HEntry t = large[p]; large[p] = large[i]; large[i] = t; i = p; }
        else break;
    }
}

static void sift_down_large(int i)
{
    while (1) {
        int s = i, l = 2*i+1, r = 2*i+2;
        if (l < ln && large[l].val < large[s].val) s = l;
        if (r < ln && large[r].val < large[s].val) s = r;
        if (s != i) { HEntry t = large[s]; large[s] = large[i]; large[i] = t; i = s; }
        else break;
    }
}

static void prune_small(void)
{
    while (sn > 0 && delayed[small[0].idx] > 0) {
        delayed[small[0].idx]--;
        small[0] = small[--sn];
        if (sn > 0) sift_down_small(0);
    }
}

static void prune_large(void)
{
    while (ln > 0 && delayed[large[0].idx] > 0) {
        delayed[large[0].idx]--;
        large[0] = large[--ln];
        if (ln > 0) sift_down_large(0);
    }
}

static void make_balanced(void)
{
    if (small_sz > large_sz + 1) {
        prune_small();
        HEntry e = small[0];
        small[0] = small[--sn]; if (sn > 0) sift_down_small(0);
        in_small_flag[e.idx] = 0;
        small_sz--; large_sz++;
        large[ln] = (HEntry){e.val, e.idx}; ln++;
        sift_up_large(ln - 1);
        prune_small();
    } else if (small_sz < large_sz) {
        prune_large();
        HEntry e = large[0];
        large[0] = large[--ln]; if (ln > 0) sift_down_large(0);
        in_small_flag[e.idx] = 1;
        large_sz--; small_sz++;
        small[sn] = (HEntry){e.val, e.idx}; sn++;
        sift_up_small(sn - 1);
        prune_large();
    }
}

static double get_median(int k)
{
    if (k % 2 == 1) return (double)small[0].val;
    return (double)(small[0].val + large[0].val) / 2.0;
}

double *solve(int *nums, int n, int k, int *ret_size)
{
    sn = ln = small_sz = large_sz = 0;
    memset(delayed, 0, sizeof(delayed));
    memset(in_small_flag, 0, sizeof(in_small_flag));

    double *res = malloc((n - k + 1) * sizeof(double));
    *ret_size = 0;

    for (int i = 0; i < n; i++) {
        prune_small();
        prune_large();

        if (sn == 0 || nums[i] <= (int)small[0].val) {
            small[sn] = (HEntry){nums[i], i}; sn++;
            sift_up_small(sn - 1);
            in_small_flag[i] = 1;
            small_sz++;
        } else {
            large[ln] = (HEntry){nums[i], i}; ln++;
            sift_up_large(ln - 1);
            in_small_flag[i] = 0;
            large_sz++;
        }

        make_balanced();

        if (i >= k) {
            int out_idx = i - k;
            delayed[out_idx]++;
            if (in_small_flag[out_idx]) small_sz--;
            else large_sz--;
            make_balanced();
        }

        if (i >= k - 1) {
            prune_small();
            prune_large();
            res[(*ret_size)++] = get_median(k);
        }
    }
    return res;
}

static int feq(double a, double b) { return fabs(a - b) < 1e-5; }

int main(void)
{
    struct {
        const char *label;
        int input[10];
        int n;
        int k;
        double expected[10];
        int en;
    } tests[] = {
        {"example 1", {1, 3, -1, -3, 5, 3, 6, 7}, 8, 3, {1.0, -1.0, -1.0, 3.0, 5.0, 6.0}, 6},
        {"window size 1", {1, 2}, 2, 1, {1.0, 2.0}, 2},
        {"example 2", {1, 2, 3, 4, 2, 3, 1, 4, 2}, 9, 3, {2.0, 3.0, 3.0, 3.0, 2.0, 3.0, 2.0}, 7},
        {"large int boundary", {2147483647, -2147483648}, 2, 2, {-0.5}, 1},
        {"all same values", {1, 1, 1, 1}, 4, 2, {1.0, 1.0, 1.0}, 3},
        {"window equals array", {5, 5, 5, 5, 5}, 5, 5, {5.0}, 1},
        {"all negative ascending", {-5, -4, -3, -2, -1}, 5, 3, {-4.0, -3.0, -2.0}, 3},
        {"descending order", {10, 9, 8, 7, 6}, 5, 3, {9.0, 8.0, 7.0}, 3},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  480. Sliding Window Median\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int ret_size = 0;
        double *got = solve(tests[i].input, tests[i].n, tests[i].k, &ret_size);
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
