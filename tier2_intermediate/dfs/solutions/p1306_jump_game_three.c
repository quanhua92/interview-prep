/*
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 *
 * Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
 * Notice that you can not jump outside of the array at any time.
 *
 * Example 1:
 *     Input: arr = [4,2,3,0,3,1,2], start = 5
 *     Output: true
 *     Explanation:
 *     All possible ways to reach at index 3 with value 0 are:
 *     index 5 -> index 4 -> index 1 -> index 3
 *     index 5 -> index 6 -> index 4 -> index 1 -> index 3
 *
 * Example 2:
 *     Input: arr = [4,2,3,0,3,1,2], start = 0
 *     Output: true
 *     Explanation:
 *     One possible way to reach at index 3 with value 0 is:
 *     index 0 -> index 4 -> index 1 -> index 3
 *
 * Example 3:
 *     Input: arr = [3,0,2,1,2], start = 2
 *     Output: false
 *     Explanation: There is no way to reach at index 1 with value 0.
 *
 * Constraints:
 *     - 1 <= arr.length <= 5 * 104
 *     - 0 <= arr[i] < arr.length
 *     - 0 <= start < arr.length
 *
 * Hints:
 *     - Think of BFS to solve the problem.
 *     - When you reach a position with a value = 0 then return true.
 *
 * Template (python3):
 *     class Solution:
 *         def canReach(self, arr: List[int], start: int) -> bool:
 *
 * Hint: DFS with a visited set; explore start+arr[start] and start-arr[start], checking bounds and visited.
 */


#include "ctest.h"

static char visited[50001];

static int dfs(const int *arr, int n, int i) {
    if (i < 0 || i >= n || visited[i]) return 0;
    if (arr[i] == 0) return 1;
    visited[i] = 1;
    return dfs(arr, n, i + arr[i]) || dfs(arr, n, i - arr[i]);
}

static int canReach(const int *arr, int n, int start) {
    memset(visited, 0, sizeof(visited));
    return dfs(arr, n, start);
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    struct { const char *label; int input[8]; int input_n; int start; int expected; } tests[] = {
        {"example 1", {4, 2, 3, 0, 3, 1, 2}, 7, 5, 1},
        {"start at index 0", {4, 2, 3, 0, 3, 1, 2}, 7, 0, 1},
        {"cannot reach zero", {3, 0, 2, 1, 2}, 5, 2, 0},
        {"single element zero", {0}, 1, 0, 1},
        {"single element non-zero", {2}, 1, 0, 0},
        {"start next to zero", {0, 1}, 2, 1, 1},
        {"linear path to zero", {1, 1, 1, 1, 0}, 5, 0, 1},
        {"jump directly to zero", {7, 0, 0, 0, 0, 0, 0, 0}, 8, 0, 1},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  1306. Jump Game III\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        int got = canReach(tests[i].input, tests[i].input_n, tests[i].start);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");

    return passed == n ? 0 : 1;
}
