/*
 * P498: Diagonal Traverse (Medium)
 * https://leetcode.com/problems/diagonal-traverse/
 * Topics: Array, Matrix, Simulation
 *
 * Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
 *
 * Example 1:
 *     Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [1,2,4,7,5,3,6,8,9]
 *
 * Example 2:
 *     Input: mat = [[1,2],[3,4]]
 *     Output: [1,2,3,4]
 *
 * Constraints:
 *     - m == mat.length
 *     - n == mat[i].length
 *     - 1 <= m, n <= 104
 *     - 1 <= m * n <= 104
 *     - -105 <= mat[i][j] <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
 *
 * Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
 */


#include "io.h"
#include <algorithm>

static std::vector<int> findDiagonalOrder(const std::vector<std::vector<int>> &mat)
{
    if (mat.empty() || mat[0].empty()) return {};
    int m = mat.size(), n = mat[0].size();
    std::vector<int> result;
    result.reserve(m * n);

    for (int d = 0; d < m + n - 1; d++) {
        std::vector<int> diag;
        int r = d < n ? 0 : d - n + 1;
        int c = d < n ? d : n - 1;
        while (r < m && c >= 0) {
            diag.push_back(mat[r][c]);
            r++; c--;
        }
        if (d % 2 == 0)
            std::reverse(diag.begin(), diag.end());
        for (int v : diag)
            result.push_back(v);
    }
    return result;
}

int main(void)
{
    std::vector<int> header = read_ints();
    int cols = header[0];
    int rows = cols;
    std::vector<std::vector<int>> mat;
    for (int i = 0; i < rows; i++)
        mat.push_back(read_ints());
    auto result = findDiagonalOrder(mat);
    write_ints(result);
    return 0;
}
