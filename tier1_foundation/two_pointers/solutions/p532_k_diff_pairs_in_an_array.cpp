/*
 * P532: K-diff Pairs in an Array [PREMIUM] (Medium)
 * https://leetcode.com/problems/k-diff-pairs-in-an-array/
 * Topics: Array, Hash Table, Two Pointers, Binary Search, Sorting
 *
 * Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
 * A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
 * Notice that |val| denotes the absolute value of val.
 * Example 1:
 *     Input: nums = [3,1,4,1,5], k = 2
 *     Output: 2
 *     Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
 *     Although we have two 1s in the input, we should only return the number of unique pairs.
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,5], k = 1
 *     Output: 4
 *     Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
 *
 * Example 3:
 *     Input: nums = [1,3,1,5,4], k = 0
 *     Output: 1
 *     Explanation: There is one 0-diff pair in the array, (1, 1).
 *
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -107 <= nums[i] <= 107
 *     - 0 <= k <= 107
 *
 * Template (python3):
 *     class Solution:
 *         def findPairs(self, nums: List[int], k: int) -> int:
 */


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

static int findPairs(const std::vector<int> &nums, int k) {
    if (k < 0) return 0;
    std::vector<int> arr = nums;
    std::sort(arr.begin(), arr.end());
    int count = 0;
    int left = 0, right = 1;
    int n = (int)arr.size();
    while (right < n) {
        int diff = arr[right] - arr[left];
        if (diff < k) {
            right++;
        } else if (diff > k) {
            left++;
        } else {
            count++;
            int lv = arr[left], rv = arr[right];
            while (left < n && arr[left] == lv) left++;
            while (right < n && arr[right] == rv) right++;
        }
        if (left == right) right++;
    }
    return count;
}

int main(void) {
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  532. K-diff Pairs in an Array\n");
    printf("============================================================\n");

    {
        int got = findPairs({3, 1, 4, 1, 5}, 2);
        if (got == 2) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: 2, Got: %d\n", got); }
    }
    {
        int got = findPairs({1, 2, 3, 4, 5}, 1);
        if (got == 4) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: 4, Got: %d\n", got); }
    }
    {
        int got = findPairs({1, 3, 1, 5, 4}, 0);
        if (got == 1) { passed++; printf("  Test 3 (example 3): PASS\n"); }
        else { printf("  Test 3 (example 3): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int got = findPairs({1}, 1);
        if (got == 0) { passed++; printf("  Test 4 (single element): PASS\n"); }
        else { printf("  Test 4 (single element): FAIL\n  Expected: 0, Got: %d\n", got); }
    }
    {
        int got = findPairs({1, 1, 1, 1}, 0);
        if (got == 1) { passed++; printf("  Test 5 (all same k=0): PASS\n"); }
        else { printf("  Test 5 (all same k=0): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int got = findPairs({1, 2, 3, 4, 5}, 100);
        if (got == 0) { passed++; printf("  Test 6 (k larger than range): PASS\n"); }
        else { printf("  Test 6 (k larger than range): FAIL\n  Expected: 0, Got: %d\n", got); }
    }
    {
        int got = findPairs({-1, -2, -3, -4, -5}, 1);
        if (got == 4) { passed++; printf("  Test 7 (all negatives): PASS\n"); }
        else { printf("  Test 7 (all negatives): FAIL\n  Expected: 4, Got: %d\n", got); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
