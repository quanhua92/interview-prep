/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 *
 * Constraints:
 *     - 1 <= k <= 105
 *     - 0 <= w <= 109
 *     - 1 <= n <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
 */


#include "io.h"
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital) {
    int n = (int)profits.size();
    vector<pair<int, int>> proj(n);
    for (int i = 0; i < n; i++) proj[i] = {capital[i], profits[i]};
    sort(proj.begin(), proj.end());
    priority_queue<int> pq;
    int idx = 0;
    for (int _ = 0; _ < k; _++) {
        while (idx < n && proj[idx].first <= w) pq.push(proj[idx++].second);
        if (pq.empty()) break;
        w += pq.top(); pq.pop();
    }
    return w;
}

int main() {
    vector<int> k_vec = read_ints();
    vector<int> w_vec = read_ints();
    vector<int> profits = read_ints();
    vector<int> capital = read_ints();
    int result = findMaximizedCapital(k_vec[0], w_vec[0], profits, capital);
    write_int(result);
    return 0;
}
