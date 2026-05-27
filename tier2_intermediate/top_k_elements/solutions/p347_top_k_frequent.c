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

#include "io.h"
#include <stdlib.h>
#include <string.h>

typedef struct { int val, freq; } Freq;

static int cmp_freq(const void *a, const void *b)
{
    const Freq *fa = a, *fb = b;
    if (fb->freq != fa->freq) return fb->freq - fa->freq;
    return fb->val - fa->val;
}

static void topKFrequent(int *nums, int numsSize, int k, int *result)
{
    int freq[20001] = {0};
    for (int i = 0; i < numsSize; i++) freq[nums[i] + 10000]++;

    int n_items = 0;
    for (int i = 0; i < 20001; i++) {
        if (freq[i] > 0) n_items++;
    }

    Freq *items = malloc(n_items * sizeof(Freq));
    int idx = 0;
    for (int v = -10000; v <= 10000; v++) {
        if (freq[v + 10000] > 0) {
            items[idx].val = v;
            items[idx].freq = freq[v + 10000];
            idx++;
        }
    }

    qsort(items, n_items, sizeof(Freq), cmp_freq);

    for (int i = 0; i < k; i++) result[i] = items[i].val;
    free(items);
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    int k_len;
    int *k_arr = read_ints(&k_len);
    int k = k_arr[0];
    free(k_arr);
    int *result = malloc(k * sizeof(int));
    topKFrequent(nums, n, k, result);
    write_ints(result, k);
    free(result);
    free(nums);
    return 0;
}
