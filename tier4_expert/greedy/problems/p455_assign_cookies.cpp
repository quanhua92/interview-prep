/*
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 *
 * Each child i has a greed factor g[i], and each cookie j has a size s[j].
 * Return the maximum number of content children.
 *
 * Constraints:
 *     - 1 <= g.length <= 3 * 10^4
 *     - 0 <= s.length <= 3 * 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def findContentChildren(self, g: List[int], s: List[int]) -> int:
 */


#include "io.h"
#include <algorithm>

int findContentChildren(std::vector<int> g, std::vector<int> s) {
    abort();
}

int main() {
    std::vector<int> g = read_ints();
    std::vector<int> s = read_ints();
    int result = findContentChildren(g, s);
    write_int(result);
    return 0;
}
