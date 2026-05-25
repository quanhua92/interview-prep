/*
 * P347: Top K Frequent Elements (Medium)
 * https://leetcode.com/problems/top-k-frequent-elements/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect
 * 
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
 * 
 * Example 1:
 *     Input: nums = [1,1,1,2,2,3], k = 2
 *     Output: [1,2]
 * 
 * Example 2:
 *     Input: nums = [1], k = 1
 *     Output: [1]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 *     - k is in the range [1, the number of unique elements in the array].
 *     - It is guaranteed that the answer is unique.
 * 
 * Follow up:
 *     - Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 * 
 * Template (python3):
 *     class Solution:
 *         def topKFrequent(self, nums: List[int], k: int) -> List[int]:
 * 
 * Hint: Use a frequency counter and a min-heap of size k.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <unordered_map>
#include <vector>

std::vector<int> topKFrequent(const std::vector<int> &nums, int k)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct TC {
        const char *label;
        std::vector<int> input;
        int k;
        std::vector<int> expected;
    };
    TC tests[] = {
        {"example 1",               {1, 1, 1, 2, 2, 3},              2, {1, 2}},
        {"example 2",               {1},                             1, {1}},
        {"distinct frequencies",    {7, 7, 7, 7, 1, 2, 2, 2},       2, {7, 2}},
        {"all freq 1",              {1, 2, 3, 4, 5, 6},             3, {6, 5, 4}},
        {"all same element",        {1, 1, 1, 1},                    1, {1}},
        {"clear frequency ranking", {1, 1, 2, 2, 2, 3, 3, 3, 3},    2, {3, 2}},
        {"negative numbers",        {-1, -1, -1, 2, 2},              1, {-1}},
        {"zero values",             {0, 0, 0, 0, 1, 1, 2},           2, {0, 1}},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  347. Top K Frequent Elements\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        auto got = topKFrequent(tests[i].input, tests[i].k);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: ");
            print_arr(tests[i].expected);
            printf("\n    Got:      ");
            print_arr(got);
            printf("\n");
        }
    }

    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
