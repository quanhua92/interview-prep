/*
 * P268: Missing Number (Easy)
 * https://leetcode.com/problems/missing-number/
 * Topics: Array, Hash Table, Math, Binary Search, Bit Manipulation, Sorting
 *
 * Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.
 *
 * Example 1:
 *     Input: nums = [3,0,1]
 *     Output: 2
 *
 * Example 2:
 *     Input: nums = [0,1]
 *     Output: 2
 *
 * Example 3:
 *     Input: nums = [9,6,4,2,3,5,7,0,1]
 *     Output: 8
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 104
 *     - 0 <= nums[i] <= n
 *     - All the numbers of nums are unique.
 *
 * Hint: Use cyclic sort to place each number at its correct index.
 */

#include "io.h"
#include <stdlib.h>

int missingNumber(int *nums, int n)
{
    int i = 0;
    while (i < n) {
        int correct = nums[i];
        if (correct < n && nums[i] != nums[correct]) {
            int tmp = nums[i];
            nums[i] = nums[correct];
            nums[correct] = tmp;
        } else {
            i++;
        }
    }
    for (i = 0; i < n; i++) {
        if (nums[i] != i) return i;
    }
    return n;
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    write_int(missingNumber(nums, n));
    free(nums);
    return 0;
}
