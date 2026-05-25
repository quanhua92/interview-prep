/*
 * P153: Find Minimum in Rotated Sorted Array (Medium)
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 * Topics: Array, Binary Search
 * 
 * Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 * Given the sorted rotated array nums of unique elements, return the minimum element of this array.
 * You must write an algorithm that runs in O(log n) time.
 * 
 * Example 1:
 *     Input: nums = [3,4,5,1,2]
 *     Output: 1
 *     Explanation: The original array was [1,2,3,4,5] rotated 3 times.
 * 
 * Example 2:
 *     Input: nums = [4,5,6,7,0,1,2]
 *     Output: 0
 *     Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
 * 
 * Example 3:
 *     Input: nums = [11,13,15,17]
 *     Output: 11
 *     Explanation: The original array was [11,13,15,17] and it was rotated 4 times.
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 5000
 *     - -5000 <= nums[i] <= 5000
 *     - All the integers of nums are unique.
 *     - nums is sorted and rotated between 1 and n times.
 * 
 * Hints:
 *     - Array was originally in ascending order. Now that the array is rotated, there would be a point in the array where there is a small deflection from the increasing sequence. eg. The array would be something like [4, 5, 6, 7, 0, 1, 2].
 *     - You can divide the search space into two and see which direction to go.
 * Can you think of an algorithm which has O(logN) search complexity?
 *     - <ol>
 * <li>All the elements to the left of inflection point > first element of the array.</li>
 * <li>All the elements to the right of inflection point < first element of the array.</li>
 * <ol>
 * 
 * Template (python3):
 *     class Solution:
 *         def findMin(self, nums: List[int]) -> int:
 * 
 * Hint: Compare mid element with the rightmost to decide which half contains the minimum.
 */
#include <cstdio>
#include <vector>

int findMin(const std::vector<int> &nums)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct Tc { const char *label; std::vector<int> nums; int expected; bool pass; };
    std::vector<Tc> tests = {
        {"example 1", {3,4,5,1,2}, 1, false},
        {"example 2", {4,5,6,7,0,1,2}, 0, false},
        {"single element", {1}, 1, false},
        {"not rotated", {11,13,15,17}, 11, false},
        {"two elements rotated", {2,1}, 1, false},
        {"two elements not rotated", {1,2}, 1, false},
        {"negative numbers", {-3,-2,-1,-5,-4}, -5, false},
        {"rotated by 1", {2,3,4,5,1}, 1, false},
        {"rotated by n-1", {5,1,2,3,4}, 1, false},
        {"three elements rotated", {3,1,2}, 1, false},
    };

    int passed = 0;
    for (auto &tc : tests) {
        int got = findMin(tc.nums);
        tc.pass = (got == tc.expected);
        if (tc.pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  153. Find Minimum in Rotated Sorted Array\n");
    printf("============================================================\n");
    for (int i = 0; i < (int)tests.size(); i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n");
    return passed == (int)tests.size() ? 0 : 1;
}
