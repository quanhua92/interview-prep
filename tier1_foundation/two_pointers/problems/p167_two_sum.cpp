/*
 * P167: Two Sum II - Input Array Is Sorted (Medium)
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 * Topics: Array, Two Pointers, Binary Search
 * 
 * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
 * Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
 * The tests are generated such that there is exactly one solution. You may not use the same element twice.
 * Your solution must use only constant extra space.
 * 
 * Example 1:
 *     Input: numbers = [2,7,11,15], target = 9
 *     Output: [1,2]
 *     Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
 * 
 * Example 2:
 *     Input: numbers = [2,3,4], target = 6
 *     Output: [1,3]
 *     Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].
 * 
 * Example 3:
 *     Input: numbers = [-1,0], target = -1
 *     Output: [1,2]
 *     Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
 * 
 * Constraints:
 *     - 2 <= numbers.length <= 3 * 104
 *     - -1000 <= numbers[i] <= 1000
 *     - numbers is sorted in non-decreasing order.
 *     - -1000 <= target <= 1000
 *     - The tests are generated such that there is exactly one solution.
 * 
 * Template (python3):
 *     class Solution:
 *         def twoSum(self, numbers: List[int], target: int) -> List[int]:
 * 
 * Hint: Use two pointers from both ends of the sorted array.
 */
#include "cpptest.h"

std::vector<int> twoSum(const std::vector<int> &numbers, int target)
{
    abort();
}

int main(void)
{
    TestCase tests[] = {
        {"example 1",              {2, 7, 11, 15},        9,   {1, 2}},
        {"example 2",              {2, 3, 4},             6,   {1, 3}},
        {"example 3",              {-1, 0},               -1,  {1, 2}},
        {"all negatives",          {-10, -6, -4, -2},     -10, {2, 3}},
        {"exactly two elements",   {1, 2},                3,   {1, 2}},
        {"negative positive cross", {-5, -3, 0, 2, 4, 6}, 1,   {1, 6}},
        {"middle elements",        {1, 3, 4, 5, 7, 10, 11}, 9, {3, 4}},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);
    RUN_TESTS("167. Two Sum II - Input Array Is Sorted", twoSum, tests, n_tests);
}
