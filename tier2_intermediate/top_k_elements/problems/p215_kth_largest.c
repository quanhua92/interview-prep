/*
 * P215: Kth Largest Element in an Array (Medium)
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Quickselect
 * 
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * Can you solve it without sorting?
 * 
 * Example 1:
 *     Input: nums = [3,2,1,5,6,4], k = 2
 *     Output: 5
 * 
 * Example 2:
 *     Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 *     Output: 4
 * 
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 * 
 * Template (python3):
 *     class Solution:
 *         def findKthLargest(self, nums: List[int], k: int) -> int:
 * 
 * Hint: Use a min-heap of size k to efficiently find the kth largest element.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap(int *a, int *b) {
    abort();
}

static int partition(int *a, int lo, int hi)
{
    abort();
}

int findKthLargest(int *nums, int numsSize, int k)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        int input[100];
        int n;
        int k;
        int expected;
    } tests[] = {
        {"example 1",                 {3, 2, 1, 5, 6, 4},                    6,  2, 5},
        {"example 2",                 {3, 2, 3, 1, 2, 4, 5, 5, 6},          9,  4, 4},
        {"single element",            {1},                                   1,  1, 1},
        {"negative numbers",          {-1, -2, -3},                          3,  1, -1},
        {"all duplicates",            {5, 5, 5, 5},                          4,  2, 5},
        {"k equals length",           {1, 2, 3},                             3,  3, 1},
        {"mixed negatives and zero",  {-100, 0, 100},                        3,  2, 0},
        {"all negative duplicates",   {-1, -1, -1, -1},                      4,  3, -1},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  215. Kth Largest Element in an Array\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int buf[100];
        memcpy(buf, tests[i].input, tests[i].n * sizeof(int));
        int got = findKthLargest(buf, tests[i].n, tests[i].k);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }

    int input_100[100];
    for (int i = 0; i < 100; i++) input_100[i] = i + 1;
    int buf_100[100];
    memcpy(buf_100, input_100, 100 * sizeof(int));
    int got_100 = findKthLargest(buf_100, 100, 50);
    int total = n_tests + 1;
    if (got_100 == 51) {
        passed++;
        printf("  Test %d (100 elements k=50): PASS\n", n_tests + 1);
    } else {
        printf("  Test %d (100 elements k=50): FAIL\n", n_tests + 1);
        printf("    Expected: 51\n    Got:      %d\n", got_100);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
