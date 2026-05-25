/*
 * P704: Binary Search (Easy)
 * https://leetcode.com/problems/binary-search/
 * Topics: Array, Binary Search
 * 
 * Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * Example 1:
 *     Input: nums = [-1,0,3,5,9,12], target = 9
 *     Output: 4
 *     Explanation: 9 exists in nums and its index is 4
 * 
 * Example 2:
 *     Input: nums = [-1,0,3,5,9,12], target = 2
 *     Output: -1
 *     Explanation: 2 does not exist in nums so return -1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -104 < nums[i], target < 104
 *     - All the integers in nums are unique.
 *     - nums is sorted in ascending order.
 * 
 * Template (python3):
 *     class Solution:
 *         def search(self, nums: List[int], target: int) -> int:
 * 
 * Hint: Use the classic binary search pattern with left and right pointers.
 */
#include <cstdio>
#include <cstdlib>
#include <vector>

int search(const std::vector<int> &nums, int target)
{
    abort();
}

int main(void)
{
    struct Tc { const char *label; std::vector<int> nums; int target; int expected; bool pass; };
    std::vector<Tc> tests;
    tests.push_back({"example 1", {-1,0,3,5,9,12}, 9, 4, false});
    tests.push_back({"example 2", {-1,0,3,5,9,12}, 2, -1, false});
    tests.push_back({"single element", {5}, 5, 0, false});
    tests.push_back({"below range", {-1,0,3,5,9,12}, -2, -1, false});
    tests.push_back({"last element", {-1,0,3,5,9,12}, 12, 5, false});
    tests.push_back({"two elements first", {1,2}, 1, 0, false});
    tests.push_back({"two elements last", {1,2}, 2, 1, false});
    std::vector<int> large;
    for (int i = -5000; i <= 5000; i++) large.push_back(i);
    tests.push_back({"large array middle target", large, 0, 5000, false});
    tests.push_back({"target between elements", {2,4,6,8,10}, 5, -1, false});
    tests.push_back({"all negative found last", {-3,-2,-1}, -1, 2, false});

    int passed = 0;
    for (auto &tc : tests) {
        int got = search(tc.nums, tc.target);
        tc.pass = (got == tc.expected);
        if (tc.pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  704. Binary Search\n");
    printf("============================================================\n");
    for (int i = 0; i < (int)tests.size(); i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n");
    return passed == (int)tests.size() ? 0 : 1;
}
