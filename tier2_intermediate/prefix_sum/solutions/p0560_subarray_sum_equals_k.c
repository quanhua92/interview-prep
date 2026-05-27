/*
 * P560: Subarray Sum Equals K (Medium)
 * https://leetcode.com/problems/subarray-sum-equals-k/
 * Topics: Array, Hash Table, Prefix Sum
 *
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * Example 1:
 *     Input: nums = [1,1,1], k = 2
 *     Output: 2
 *
 * Example 2:
 *     Input: nums = [1,2,3], k = 3
 *     Output: 2
 *
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -1000 <= nums[i] <= 1000
 *     - -107 <= k <= 107
 *
 * Hints:
 *     - Will Brute force work here? Try to optimize it.
 *     - Can we optimize it by using some extra space?
 *     - What about storing sum frequencies in a hash table? Will it be useful?
 *     - sum(i,j)=sum(0,j)-sum(0,i), where sum(i,j) represents the sum of all the elements from index i to j-1.
 *
 * Can we use this property to optimize it.
 *
 * Template (python3):
 *     class Solution:
 *         def subarraySum(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a hash map with prefix sums to count subarrays summing to k.
 */

#include "io.h"
#include <stdlib.h>

typedef struct Entry {
    long long key;
    int value;
    struct Entry *next;
} Entry;

static Entry *hm[40007];

static unsigned hm_hash(long long key)
{
    unsigned h = (unsigned)(key ^ (key >> 32));
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = (h >> 16) ^ h;
    return h % 40007;
}

static void hm_set(long long key, int val)
{
    unsigned idx = hm_hash(key);
    Entry *e = hm[idx];
    while (e) {
        if (e->key == key) { e->value = val; return; }
        e = e->next;
    }
    Entry *ne = (Entry *)malloc(sizeof(Entry));
    ne->key = key;
    ne->value = val;
    ne->next = hm[idx];
    hm[idx] = ne;
}

static int hm_get(long long key)
{
    unsigned idx = hm_hash(key);
    Entry *e = hm[idx];
    while (e) {
        if (e->key == key) return e->value;
        e = e->next;
    }
    return 0;
}

static void hm_clear(void)
{
    for (int i = 0; i < 40007; i++) {
        Entry *e = hm[i];
        while (e) {
            Entry *next = e->next;
            free(e);
            e = next;
        }
        hm[i] = NULL;
    }
}

int subarray_sum(int *nums, int numsSize, int k)
{
    hm_clear();
    hm_set(0, 1);
    int count = 0;
    long long curr = 0;
    for (int i = 0; i < numsSize; i++) {
        curr += nums[i];
        count += hm_get(curr - k);
        hm_set(curr, hm_get(curr) + 1);
    }
    hm_clear();
    return count;
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    int kl;
    int *target_line = read_ints(&kl);
    int k = target_line[0];
    free(target_line);
    write_int(subarray_sum(nums, n, k));
    free(nums);
    return 0;
}
