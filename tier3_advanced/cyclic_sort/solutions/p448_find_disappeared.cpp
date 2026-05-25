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
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 *
 * Follow up:
 *     - Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
 *
 * Hints:
 *     - This is a really easy problem if you decide to use additional memory. For those trying to write an initial solution using additional memory, think <b>counters!</b>
 *     - However, the trick really is to not use any additional space than what is already available to use. Sometimes, multiple passes over the input array help find the solution. However, there's an interesting piece of information in this problem that makes it easy to re-use the input array itself for the solution.
 *     - The problem specifies that the numbers in the array will be in the range [1, n] where n is the number of elements in the array. Can we use this information and modify the array in-place somehow to find what we need?
 *
 * Template (python3):
 *     class Solution:
 *         def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
 *
 * Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
 */


#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

static std::vector<int> findDisappearedNumbers(std::vector<int> &nums) {
    for (int num : nums) {
        int index = std::abs(num) - 1;
        if (nums[index] > 0) {
            nums[index] = -nums[index];
        }
    }
    std::vector<int> result;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] > 0) {
            result.push_back(i + 1);
        }
    }
    return result;
}

int main(void) {
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  448. Find All Numbers Disappeared in an Array\n");
    printf("============================================================\n");

    {
        std::vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};
        auto got = findDisappearedNumbers(nums);
        std::vector<int> expected = {5, 6};
        if (got == expected) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        std::vector<int> nums = {1, 1};
        auto got = findDisappearedNumbers(nums);
        std::vector<int> expected = {2};
        if (got == expected) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        std::vector<int> nums = {2, 2};
        auto got = findDisappearedNumbers(nums);
        std::vector<int> expected = {1};
        if (got == expected) { passed++; printf("  Test 3 (example 3): PASS\n"); }
        else { printf("  Test 3 (example 3): FAIL\n"); }
    }
    {
        std::vector<int> nums = {1};
        auto got = findDisappearedNumbers(nums);
        std::vector<int> expected = {};
        if (got == expected) { passed++; printf("  Test 4 (single element, none missing): PASS\n"); }
        else { printf("  Test 4 (single element, none missing): FAIL\n"); }
    }
    {
        std::vector<int> nums = {1, 1, 1, 1};
        auto got = findDisappearedNumbers(nums);
        std::vector<int> expected = {2, 3, 4};
        if (got == expected) { passed++; printf("  Test 5 (all same value): PASS\n"); }
        else { printf("  Test 5 (all same value): FAIL\n"); }
    }
    {
        std::vector<int> nums = {1, 2, 3, 4, 5};
        auto got = findDisappearedNumbers(nums);
        std::vector<int> expected = {};
        if (got == expected) { passed++; printf("  Test 6 (identity permutation, none missing): PASS\n"); }
        else { printf("  Test 6 (identity permutation, none missing): FAIL\n"); }
    }
    {
        std::vector<int> nums = {5, 4, 6, 7, 9, 10, 9, 6, 5, 4};
        auto got = findDisappearedNumbers(nums);
        std::vector<int> expected = {1, 2, 3, 8};
        if (got == expected) { passed++; printf("  Test 7 (large, many disappeared): PASS\n"); }
        else { printf("  Test 7 (large, many disappeared): FAIL\n"); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
