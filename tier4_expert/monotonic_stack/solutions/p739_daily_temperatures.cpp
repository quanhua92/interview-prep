/*
 * P739: Daily Temperatures (Medium)
 * https://leetcode.com/problems/daily-temperatures/
 * Topics: Array, Stack, Monotonic Stack
 *
 * Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
 *
 * Example 1:
 *     Input: temperatures = [73,74,75,71,69,72,76,73]
 *     Output: [1,1,4,2,1,1,0,0]
 *
 * Example 2:
 *     Input: temperatures = [30,40,50,60]
 *     Output: [1,1,1,0]
 *
 * Example 3:
 *     Input: temperatures = [30,60,90]
 *     Output: [1,1,0]
 *
 * Constraints:
 *     - 1 <= temperatures.length <= 10^5
 *     - 30 <= temperatures[i] <= 100
 *
 * Hints:
 *     - If the temperature is say, 70 today, then in the future a warmer temperature must be either 71, 72, 73, ..., 99, or 100.  We could remember when all of them occur next.
 *
 * Template (python3):
 *     class Solution:
 *         def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
 *
 * Hint: Use a monotonic decreasing stack to track indices of warmer days.
 */

#include "io.h"
#include <vector>

std::vector<int> dailyTemperatures(const std::vector<int> &temperatures)
{
    int n = (int)temperatures.size();
    std::vector<int> answer(n, 0);
    std::vector<int> stack;
    for (int i = 0; i < n; i++) {
        while (!stack.empty() && temperatures[i] > temperatures[stack.back()]) {
            int j = stack.back();
            stack.pop_back();
            answer[j] = i - j;
        }
        stack.push_back(i);
    }
    return answer;
}

int main(void)
{
    std::vector<int> temperatures = read_ints();
    write_ints(dailyTemperatures(temperatures));
    return 0;
}
