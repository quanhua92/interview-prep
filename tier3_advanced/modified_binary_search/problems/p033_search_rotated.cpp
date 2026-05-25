/*
 * P33: Search in Rotated Sorted Array (Medium)
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 * Topics: Array, Binary Search
 * 
 * There is an integer array nums sorted in ascending order (with distinct values).
 * Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
 * Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * Example 1:
 *     Input: nums = [4,5,6,7,0,1,2], target = 0
 *     Output: 4
 * 
 * Example 2:
 *     Input: nums = [4,5,6,7,0,1,2], target = 3
 *     Output: -1
 * 
 * Example 3:
 *     Input: nums = [1], target = 0
 *     Output: -1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 5000
 *     - -104 <= nums[i] <= 104
 *     - All values of nums are unique.
 *     - nums is an ascending array that is possibly rotated.
 *     - -104 <= target <= 104
 * 
 * Template (python3):
 *     class Solution:
 *         def search(self, nums: List[int], target: int) -> int:
 * 
 * Hint: Determine which half is sorted, then check if target lies in that half.
 */
#include <cstdio>
#include <vector>
#include <string>

struct TestCase {
    std::string label;
    std::vector<int> nums;
    int target;
    int expected;
};

int search(const std::vector<int> &nums, int target)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    TestCase tests[] = {
        {"example 1", {4,5,6,7,0,1,2}, 0, 4},
        {"example 2", {4,5,6,7,0,1,2}, 3, -1},
        {"single element", {1}, 0, -1},
        {"single element found", {1}, 1, 0},
        {"two elements rotated at pivot", {1,3}, 3, 1},
        {"two elements no rotation", {1,3}, 1, 0},
        {"target at first index", {5,1,3}, 5, 0},
        {"target at last index", {5,1,3}, 3, 2},
        {"large rotated target at start", {6,7,0,1,2,3,4,5}, 6, 0},
        {"large rotated target at end", {6,7,0,1,2,3,4,5}, 5, 7},
        {"no rotation sorted", {1,2,3,4,5}, 3, 2},
        {"negative values target at start", {-10,-5,0,1,2,3,-9}, -10, 0},
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  33. Search in Rotated Sorted Array\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = search(tests[i].nums, tests[i].target);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label.c_str());
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label.c_str());
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
