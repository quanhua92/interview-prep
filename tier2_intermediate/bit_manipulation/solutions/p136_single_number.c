/*
 * P136: Single Number (Easy)
 * https://leetcode.com/problems/single-number/
 * Topics: Array, Bit Manipulation
 *
 * Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 *
 * Example 1:
 *     Input: nums = [2,2,1]
 *     Output: 1
 *
 * Example 2:
 *     Input: nums = [4,1,2,1,2]
 *     Output: 4
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= nums.length <= 3 * 10^4
 *     - -3 * 10^4 <= nums[i] <= 3 * 10^4
 *     - Each element in the array appears twice except for one element which appears only once.
 *
 * Hints:
 *     - Think about the XOR (^) operator's property.
 *
 * Template (python3):
 *     class Solution:
 *         def singleNumber(self, nums: List[int]) -> int:
 *
 * Hint: XOR all numbers — pairs cancel out, leaving the single number.
 */

#include "io.h"
#include <stdlib.h>

static int singleNumber(const int *nums, int numsSize) {
    int result = 0;
    for (int i = 0; i < numsSize; i++) {
        result ^= nums[i];
    }
    return result;
}

int main(void) {
    int count = 0;
    int *nums = read_ints(&count);
    write_int(singleNumber(nums, count));
    free(nums);
    return 0;
}
