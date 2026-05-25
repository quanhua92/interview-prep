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
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 *     - Each element in nums appears once or twice.
 * 
 * Template (python3):
 *     class Solution:
 *         def findDuplicates(self, nums: List[int]) -> List[int]:
 * 
 * Hint: Negate the value at index abs(num)-1 to mark seen numbers in-place.
 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

static std::vector<int> findDuplicates(std::vector<int> &nums) {
    abort();
}

int main(void) {
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  442. Find All Duplicates in an Array\n");
    printf("============================================================\n");

    {
        std::vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};
        auto got = findDuplicates(nums);
        std::vector<int> expected = {2, 3};
        if (got == expected) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        std::vector<int> nums = {1, 1, 2};
        auto got = findDuplicates(nums);
        std::vector<int> expected = {1};
        if (got == expected) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        std::vector<int> nums = {1};
        auto got = findDuplicates(nums);
        std::vector<int> expected = {};
        if (got == expected) { passed++; printf("  Test 3 (single): PASS\n"); }
        else { printf("  Test 3 (single): FAIL\n"); }
    }
    {
        std::vector<int> nums = {2, 2};
        auto got = findDuplicates(nums);
        std::vector<int> expected = {2};
        if (got == expected) { passed++; printf("  Test 4 (all same, n=2): PASS\n"); }
        else { printf("  Test 4 (all same, n=2): FAIL\n"); }
    }
    {
        std::vector<int> nums = {1, 2, 2, 1};
        auto got = findDuplicates(nums);
        std::vector<int> expected = {2, 1};
        if (got == expected) { passed++; printf("  Test 5 (all duplicates, n=4): PASS\n"); }
        else { printf("  Test 5 (all duplicates, n=4): FAIL\n"); }
    }
    {
        std::vector<int> nums = {1, 2};
        auto got = findDuplicates(nums);
        std::vector<int> expected = {};
        if (got == expected) { passed++; printf("  Test 6 (no duplicates): PASS\n"); }
        else { printf("  Test 6 (no duplicates): FAIL\n"); }
    }
    {
        std::vector<int> nums = {10, 2, 5, 10, 9, 1, 1, 7, 9, 6};
        auto got = findDuplicates(nums);
        std::vector<int> expected = {10, 1, 9};
        if (got == expected) { passed++; printf("  Test 7 (large, multiple duplicates): PASS\n"); }
        else { printf("  Test 7 (large, multiple duplicates): FAIL\n"); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
