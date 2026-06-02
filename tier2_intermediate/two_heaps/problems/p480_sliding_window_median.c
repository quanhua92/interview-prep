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
 *     - 1 <= k <= nums.length <= 10^5
 *     - -2^31 <= nums[i] <= 2^31 - 1
 *
 * Hints:
 *     - The simplest of solutions comes from the basic idea of finding the median given a set of numbers.
 *     - Is there a better way to do what we are doing in the above hint?
 *     - Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
 *
 * Template (python3):
 *     class Solution:
 *         def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
 *
 * Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
 */


#include "io.h"
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
    abort();
}

static void sift_down_small(int i)
{
    abort();
}

static void sift_up_large(int i)
{
    abort();
}

static void sift_down_large(int i)
{
    abort();
}

static void prune_small(void)
{
    abort();
}

static void prune_large(void)
{
    abort();
}

static void make_balanced(void)
{
    abort();
}

static double get_median(int k)
{
    abort();
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    int k;
    {
        int ktmp;
        int *kp = read_ints(&ktmp);
        k = kp[0];
        free(kp);
    }

    sn = ln = small_sz = large_sz = 0;
    memset(delayed, 0, sizeof(delayed));
    memset(in_small_flag, 0, sizeof(in_small_flag));

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
            printf("%.6f\n", get_median(k));
        }
    }

    free(nums);
    return 0;
}
