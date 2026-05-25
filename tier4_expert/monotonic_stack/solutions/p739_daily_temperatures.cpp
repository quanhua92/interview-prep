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
 *     - 1 <= temperatures.length <= 105
 *     - 30 <= temperatures[i] <= 100
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


#include <cstdio>
#include <cstdlib>
#include <cstring>
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

static void print_arr(const std::vector<int> &a)
{
    printf("[");
    for (size_t i = 0; i < a.size(); i++) {
        if (i) printf(",");
        printf("%d", a[i]);
    }
    printf("]");
}

int main(void)
{
    struct TC { const char *label; std::vector<int> input; std::vector<int> expected; };
    TC tests[] = {
        {"example 1", {73, 74, 75, 71, 69, 72, 76, 73}, {1, 1, 4, 2, 1, 1, 0, 0}},
        {"example 2", {30, 40, 50, 60}, {1, 1, 1, 0}},
        {"example 3", {30, 60, 90}, {1, 1, 0}},
        {"single element", {50}, {0}},
        {"all same temps", {50, 50, 50}, {0, 0, 0}},
        {"strictly decreasing", {90, 80, 70, 60}, {0, 0, 0, 0}},
        {"all same then warmer", {50, 50, 50, 60}, {3, 2, 1, 0}},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  739. Daily Temperatures\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        auto got = dailyTemperatures(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: "); print_arr(tests[i].expected); printf("\n");
            printf("    Got:      "); print_arr(got); printf("\n");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
