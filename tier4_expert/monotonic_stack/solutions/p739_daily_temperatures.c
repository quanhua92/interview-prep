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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *dailyTemperatures(int *temperatures, int n, int *return_size)
{
    int *answer = calloc(n, sizeof(int));
    int *stack = malloc(n * sizeof(int));
    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top >= 0 && temperatures[i] > temperatures[stack[top]]) {
            int j = stack[top--];
            answer[j] = i - j;
        }
        stack[++top] = i;
    }
    free(stack);
    *return_size = n;
    return answer;
}

static int arr_eq(const int *a, int an, const int *b, int bn)
{
    if (an != bn) return 0;
    for (int i = 0; i < an; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}

static void print_arr(const int *a, int n)
{
    printf("[");
    for (int i = 0; i < n; i++) {
        if (i) printf(",");
        printf("%d", a[i]);
    }
    printf("]");
}

int main(void)
{
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  739. Daily Temperatures\n");
    printf("============================================================\n");

    {
        int t[] = {73, 74, 75, 71, 69, 72, 76, 73};
        int exp[] = {1, 1, 4, 2, 1, 1, 0, 0};
        int ret = 0;
        int *got = dailyTemperatures(t, 8, &ret);
        if (arr_eq(got, ret, exp, 8)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: "); print_arr(exp, 8); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int t[] = {30, 40, 50, 60};
        int exp[] = {1, 1, 1, 0};
        int ret = 0;
        int *got = dailyTemperatures(t, 4, &ret);
        if (arr_eq(got, ret, exp, 4)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: "); print_arr(exp, 4); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int t[] = {30, 60, 90};
        int exp[] = {1, 1, 0};
        int ret = 0;
        int *got = dailyTemperatures(t, 3, &ret);
        if (arr_eq(got, ret, exp, 3)) { passed++; printf("  Test 3 (example 3): PASS\n"); }
        else { printf("  Test 3 (example 3): FAIL\n  Expected: "); print_arr(exp, 3); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int t[] = {50};
        int exp[] = {0};
        int ret = 0;
        int *got = dailyTemperatures(t, 1, &ret);
        if (arr_eq(got, ret, exp, 1)) { passed++; printf("  Test 4 (single element): PASS\n"); }
        else { printf("  Test 4 (single element): FAIL\n  Expected: "); print_arr(exp, 1); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int t[] = {50, 50, 50};
        int exp[] = {0, 0, 0};
        int ret = 0;
        int *got = dailyTemperatures(t, 3, &ret);
        if (arr_eq(got, ret, exp, 3)) { passed++; printf("  Test 5 (all same temps): PASS\n"); }
        else { printf("  Test 5 (all same temps): FAIL\n  Expected: "); print_arr(exp, 3); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int t[] = {90, 80, 70, 60};
        int exp[] = {0, 0, 0, 0};
        int ret = 0;
        int *got = dailyTemperatures(t, 4, &ret);
        if (arr_eq(got, ret, exp, 4)) { passed++; printf("  Test 6 (strictly decreasing): PASS\n"); }
        else { printf("  Test 6 (strictly decreasing): FAIL\n  Expected: "); print_arr(exp, 4); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }
    {
        int t[] = {50, 50, 50, 60};
        int exp[] = {3, 2, 1, 0};
        int ret = 0;
        int *got = dailyTemperatures(t, 4, &ret);
        if (arr_eq(got, ret, exp, 4)) { passed++; printf("  Test 7 (all same then warmer): PASS\n"); }
        else { printf("  Test 7 (all same then warmer): FAIL\n  Expected: "); print_arr(exp, 4); printf(", Got: "); print_arr(got, ret); printf("\n"); }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
