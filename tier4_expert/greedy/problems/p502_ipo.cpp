/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 *
 * Constraints:
 *     - 1 <= k <= 10^5
 *     - 0 <= w <= 10^9
 *     - 1 <= n <= 10^5
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
    abort();
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
