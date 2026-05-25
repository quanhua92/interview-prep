/*
 * P77: Combinations (Medium)
 * https://leetcode.com/problems/combinations/
 * Topics: Backtracking
 * 
 * Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
 * You may return the answer in any order.
 * 
 * Example 1:
 *     Input: n = 4, k = 2
 *     Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 *     Explanation: There are 4 choose 2 = 6 total combinations.
 *     Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
 * 
 * Example 2:
 *     Input: n = 1, k = 1
 *     Output: [[1]]
 *     Explanation: There is 1 choose 1 = 1 total combination.
 * 
 * Constraints:
 *     - 1 <= n <= 20
 *     - 1 <= k <= n
 * 
 * Template (python3):
 *     class Solution:
 *         def combine(self, n: int, k: int) -> List[List[int]]:
 * 
 * Hint: Use backtracking with a start index to generate all k-length combinations from 1..n.
 */
#include "cpptest.h"
#include <vector>

static void backtrack(int start, int n, int k, std::vector<int>& path, std::vector<std::vector<int>>& res) {
    /* TODO: Implement */
    return 0;
}

static std::vector<std::vector<int>> combine(int n, int k) {
    /* TODO: Implement */
    return 0;
}

static bool check(const std::vector<std::vector<int>>& got, const std::vector<std::vector<int>>& exp) {
    /* TODO: Implement */
    return 0;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  77. Combinations\n");
    printf("============================================================\n");

    int passed = 0;

    {
        auto got = combine(4, 2);
        std::vector<std::vector<int>> exp = {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}};
        if (check(got, exp)) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        auto got = combine(1, 1);
        std::vector<std::vector<int>> exp = {{1}};
        if (check(got, exp)) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n"); }
    }
    {
        auto got = combine(3, 1);
        std::vector<std::vector<int>> exp = {{1},{2},{3}};
        if (check(got, exp)) { passed++; printf("  Test 3 (example 3): PASS\n"); }
        else { printf("  Test 3 (example 3): FAIL\n"); }
    }
    {
        auto got = combine(5, 5);
        std::vector<std::vector<int>> exp = {{1,2,3,4,5}};
        if (check(got, exp)) { passed++; printf("  Test 4 (k equals n): PASS\n"); }
        else { printf("  Test 4 (k equals n): FAIL\n"); }
    }
    {
        auto got = combine(5, 3);
        std::vector<std::vector<int>> exp = {
            {1,2,3},{1,2,4},{1,2,5},{1,3,4},{1,3,5},{1,4,5},
            {2,3,4},{2,3,5},{2,4,5},{3,4,5},
        };
        if (check(got, exp)) { passed++; printf("  Test 5 (mid range): PASS\n"); }
        else { printf("  Test 5 (mid range): FAIL\n"); }
    }
    {
        auto got = combine(2, 2);
        std::vector<std::vector<int>> exp = {{1,2}};
        if (check(got, exp)) { passed++; printf("  Test 6 (smallest k equals n): PASS\n"); }
        else { printf("  Test 6 (smallest k equals n): FAIL\n"); }
    }
    {
        auto got = combine(6, 1);
        std::vector<std::vector<int>> exp = {{1},{2},{3},{4},{5},{6}};
        if (check(got, exp)) { passed++; printf("  Test 7 (k equals 1 larger n): PASS\n"); }
        else { printf("  Test 7 (k equals 1 larger n): FAIL\n"); }
    }

    printf("\n  %d/7 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 7 ? 0 : 1;
}
