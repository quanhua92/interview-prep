/*
 * P448: Find All Numbers Disappeared in an Array (Easy)
 * https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 * Topics: Array, Hash Table
 *
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
 *
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [5,6]
 *
 * Example 2:
 *     Input: nums = [1,1]
 *     Output: [2]
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 10^5
 *     - 1 <= nums[i] <= n
 *
 * Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
 */

#include "io.h"
#include <stdlib.h>

int *findDisappearedNumbers(int *nums, int n, int *return_size) {
    abort();
}

int main(void)
{
    int n, ret_size;
    int *nums = read_ints(&n);
    int *result = findDisappearedNumbers(nums, n, &ret_size);
    write_ints(result, ret_size);
    free(result);
    free(nums);
    return 0;
}
