/*
 * P525: Contiguous Array [PREMIUM] (Medium)
 * https://leetcode.com/problems/contiguous-array/
 * Topics: Array, Hash Table, Prefix Sum
 *
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
 * Example 1:
 *     Input: nums = [0,1]
 *     Output: 2
 *     Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
 *
 * Example 2:
 *     Input: nums = [0,1,0]
 *     Output: 2
 *     Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
 *
 * Example 3:
 *     Input: nums = [0,1,1,1,1,1,0,0,0]
 *     Output: 6
 *     Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal number of 0 and 1.
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - nums[i] is either 0 or 1.
 *
 * Template (python3):
 *     class Solution:
 *         def findMaxLength(self, nums: List[int]) -> int:
 */

#include "io.h"
#include <stdlib.h>

typedef struct Entry {
    int key;
    int value;
    struct Entry *next;
} Entry;

#define HM_SIZE 20003

static Entry *hm[HM_SIZE];

static void hm_init(void)
{
    for (int i = 0; i < HM_SIZE; i++) hm[i] = NULL;
}

static void hm_set(int key, int val)
{
    unsigned idx = ((unsigned)(key + 100000) % HM_SIZE);
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

static int hm_get(int key, int *found)
{
    unsigned idx = ((unsigned)(key + 100000) % HM_SIZE);
    Entry *e = hm[idx];
    while (e) {
        if (e->key == key) { *found = 1; return e->value; }
        e = e->next;
    }
    *found = 0;
    return 0;
}

static void hm_clear(void)
{
    for (int i = 0; i < HM_SIZE; i++) {
        Entry *e = hm[i];
        while (e) {
            Entry *next = e->next;
            free(e);
            e = next;
        }
        hm[i] = NULL;
    }
}

int find_max_length(int *nums, int numsSize)
{
    hm_init();
    hm_set(0, -1);
    int max_len = 0;
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        count += nums[i] == 1 ? 1 : -1;
        int found;
        int idx = hm_get(count, &found);
        if (found) {
            int len = i - idx;
            if (len > max_len) max_len = len;
        } else {
            hm_set(count, i);
        }
    }
    hm_clear();
    return max_len;
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    write_int(find_max_length(nums, n));
    free(nums);
    return 0;
}
