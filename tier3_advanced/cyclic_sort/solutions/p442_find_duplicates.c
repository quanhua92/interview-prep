/*
 * P442: Find All Duplicates in an Array (Medium)
 * https://leetcode.com/problems/find-all-duplicates-in-an-array/
 * Topics: Array, Hash Table
 *
 * Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.
 * You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output
 *
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [2,3]
 *
 * Example 2:
 *     Input: nums = [1,1,2]
 *     Output: [1]
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: []
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 10^5
 *     - 1 <= nums[i] <= n
 *     - Each element in nums appears once or twice.
 *
 * Hint: Negate the value at index abs(num)-1 to mark seen numbers in-place.
 */

#include "io.h"
#include <stdlib.h>

int *findDuplicates(int *nums, int n, int *return_size) {
    int *result = malloc(n * sizeof(int));
    *return_size = 0;
    for (int i = 0; i < n; i++) {
        int idx = abs(nums[i]) - 1;
        if (nums[idx] < 0) {
            result[(*return_size)++] = abs(nums[i]);
        } else {
            nums[idx] = -nums[idx];
        }
    }
    return result;
}

int main(void)
{
    int n, ret_size;
    int *nums = read_ints(&n);
    int *result = findDuplicates(nums, n, &ret_size);
    write_ints(result, ret_size);
    free(result);
    free(nums);
    return 0;
}
