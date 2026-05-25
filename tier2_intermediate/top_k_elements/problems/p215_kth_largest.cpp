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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <vector>

int findKthLargest(std::vector<int> nums, int k)
{
    abort();
}

int main(void)
{
    struct TC {
        const char *label;
        std::vector<int> input;
        int k;
        int expected;
    };
    TC tests[] = {
        {"example 1",                 {3, 2, 1, 5, 6, 4},                    2, 5},
        {"example 2",                 {3, 2, 3, 1, 2, 4, 5, 5, 6},          4, 4},
        {"single element",            {1},                                   1, 1},
        {"negative numbers",          {-1, -2, -3},                          1, -1},
        {"all duplicates",            {5, 5, 5, 5},                          2, 5},
        {"k equals length",           {1, 2, 3},                             3, 1},
        {"mixed negatives and zero",  {-100, 0, 100},                        2, 0},
        {"all negative duplicates",   {-1, -1, -1, -1},                      3, -1},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  215. Kth Largest Element in an Array\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = findKthLargest(tests[i].input, tests[i].k);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }

    std::vector<int> input_100;
    for (int i = 1; i <= 100; i++) input_100.push_back(i);
    int got_100 = findKthLargest(input_100, 50);
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
