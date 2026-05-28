/*
 * P347: Top K Frequent Elements (Medium)
 * https://leetcode.com/problems/top-k-frequent-elements/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect
 *
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,1,1,2,2,3], k = 2
 *     Output: [1,2]
 *
 * Example 2:
 *     Input: nums = [1], k = 1
 *     Output: [1]
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 *     - k is in the range [1, the number of unique elements in the array].
 *     - It is guaranteed that the answer is unique.
 *
 * Follow up:
 *     - Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 *
 * Template (python3):
 *     class Solution:
 *         def topKFrequent(self, nums: List[int], k: int) -> List[int]:
 *
 * Hint: Use a frequency counter and a min-heap of size k.
 */

#include "io.h"
#include <algorithm>
#include <unordered_map>
#include <vector>

std::vector<int> topKFrequent(const std::vector<int> &nums, int k)
{
    std::unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    std::vector<std::pair<int, int>> items;
    items.reserve(freq.size());
    for (auto &[val, cnt] : freq) items.push_back({val, cnt});

    std::partial_sort(items.begin(), items.begin() + k, items.end(),
                      [](const auto &a, const auto &b) {
                          return a.second > b.second ||
                                 (a.second == b.second && a.first > b.first);
                      });

    std::vector<int> result;
    result.reserve(k);
    for (int i = 0; i < k; i++) result.push_back(items[i].first);
    return result;
}

int main(void)
{
    abort();
}
