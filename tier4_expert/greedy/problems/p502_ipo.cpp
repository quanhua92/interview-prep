/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 * 
 * Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most k distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.
 * You are given n projects where the ith project has a pure profit profits[i] and a minimum capital of capital[i] is needed to start it.
 * Initially, you have w capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.
 * Pick a list of at most k distinct projects from given projects to maximize your final capital, and return the final maximized capital.
 * The answer is guaranteed to fit in a 32-bit signed integer.
 * Example 1:
 *     Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
 *     Output: 4
 *     Explanation: Since your initial capital is 0, you can only start the project indexed 0.
 *     After finishing it you will obtain profit 1 and your capital becomes 1.
 *     With capital 1, you can either start the project indexed 1 or the project indexed 2.
 *     Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
 *     Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
 * 
 * Example 2:
 *     Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
 *     Output: 6
 * 
 * Constraints:
 *     - 1 <= k <= 105
 *     - 0 <= w <= 109
 *     - n == profits.length
 *     - n == capital.length
 *     - 1 <= n <= 105
 *     - 0 <= profits[i] <= 104
 *     - 0 <= capital[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <queue>

using namespace std;

int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital) {
    abort();
}

int main() {
    printf("\n============================================================\n");
    printf("  502. IPO\n");
    printf("============================================================\n");
    struct T { const char *label; int k, w; vector<int> profits, capital; int expected; };
    vector<T> tests = {
        {"example 1", 2, 0, {1,2,3}, {0,1,1}, 4},
        {"example 2", 3, 0, {1,2,3}, {0,1,2}, 6},
        {"k less than projects", 1, 0, {1,2,3}, {0,0,0}, 3},
        {"k more than projects", 10, 0, {1,2}, {0,0}, 3},
        {"single project", 1, 1, {5}, {1}, 6},
        {"all affordable", 2, 5, {3,4}, {1,2}, 12},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        int got = findMaximizedCapital(tests[i].k, tests[i].w, tests[i].profits, tests[i].capital);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d, Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n\n");
    return passed == (int)tests.size() ? 0 : 1;
}
