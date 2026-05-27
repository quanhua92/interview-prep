/*
 * P169: Majority Element (Easy)
 * https://leetcode.com/problems/majority-element/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Counting
 *
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
 *
 * Example 1:
 *     Input: nums = [3,2,3]
 *     Output: 3
 *
 * Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
 */

#include "io.h"
#include <vector>

int majorityElement(const std::vector<int> &nums)
{
    abort();
}

int main(void)
{
    std::vector<int> nums = read_ints();
    write_int(majorityElement(nums));
    return 0;
}
