/*
 * P480: Sliding Window Median (Hard)
 * https://leetcode.com/problems/sliding-window-median/
 * Topics: Array, Hash Table, Sliding Window, Heap (Priority Queue)
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
 * You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
 * Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
 *
 * Example 1:
 *     Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 *     Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
 *     Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -231 <= nums[i] <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
 *
 * Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
 */


#include "io.h"
#include <cmath>
#include <queue>
#include <vector>
#include <unordered_map>

using LL = long long;

struct Entry {
    LL val;
    int idx;
};

struct SmallCmp {
    bool operator()(const Entry &a, const Entry &b) const { return a.val < b.val; }
};

struct LargeCmp {
    bool operator()(const Entry &a, const Entry &b) const { return a.val > b.val; }
};

int main(void)
{
    std::vector<int> nums = read_ints();
    std::vector<int> kline = read_ints();
    int k = kline[0];

    std::priority_queue<Entry, std::vector<Entry>, SmallCmp> small;
    std::priority_queue<Entry, std::vector<Entry>, LargeCmp> large;
    std::unordered_map<int, int> delayed;
    std::unordered_map<int, bool> in_small;
    int small_sz = 0, large_sz = 0;

    auto prune_small = [&]() {
        while (!small.empty() && delayed.count(small.top().idx)) {
            auto [_, idx] = small.top();
            if (--delayed[idx] == 0) delayed.erase(idx);
            small.pop();
        }
    };

    auto prune_large = [&]() {
        while (!large.empty() && delayed.count(large.top().idx)) {
            auto [_, idx] = large.top();
            if (--delayed[idx] == 0) delayed.erase(idx);
            large.pop();
        }
    };

    auto make_balanced = [&]() {
        if (small_sz > large_sz + 1) {
            prune_small();
            auto [v, idx] = small.top(); small.pop();
            in_small[idx] = false;
            small_sz--; large_sz++;
            large.push({v, idx});
            prune_small();
        } else if (small_sz < large_sz) {
            prune_large();
            auto [v, idx] = large.top(); large.pop();
            in_small[idx] = true;
            large_sz--; small_sz++;
            small.push({v, idx});
            prune_large();
        }
    };

    int n = (int)nums.size();

    for (int i = 0; i < n; i++) {
        prune_small();
        prune_large();

        if (small.empty() || nums[i] <= (int)small.top().val) {
            small.push({(LL)nums[i], i});
            in_small[i] = true;
            small_sz++;
        } else {
            large.push({(LL)nums[i], i});
            in_small[i] = false;
            large_sz++;
        }

        make_balanced();

        if (i >= k) {
            int out_idx = i - k;
            delayed[out_idx]++;
            if (in_small.count(out_idx) && in_small[out_idx]) small_sz--;
            else large_sz--;
            make_balanced();
        }

        if (i >= k - 1) {
            prune_small();
            prune_large();
            if (k % 2 == 1) printf("%.6f\n", (double)small.top().val);
            else printf("%.6f\n", (double)(small.top().val + large.top().val) / 2.0);
        }
    }

    return 0;
}
