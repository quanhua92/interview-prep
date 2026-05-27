"""
P455: Assign Cookies (Easy)
https://leetcode.com/problems/assign-cookies/
Topics: Array, Two Pointers, Greedy, Sorting

Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.
Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.

Example 1:
    Input: g = [1,2,3], s = [1,1]
    Output: 1
    Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
    And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
    You need to output 1.

Example 2:
    Input: g = [1,2], s = [1,2,3]
    Output: 2
    Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
    You have 3 cookies and their sizes are big enough to gratify all of the children,
    You need to output 2.

Constraints:
    - 1 <= g.length <= 3 * 104
    - 0 <= s.length <= 3 * 104
    - 1 <= g[i], s[j] <= 231 - 1

Template (python3):
    class Solution:
        def findContentChildren(self, g: List[int], s: List[int]) -> int:

Hint: Sort both arrays and use two pointers to greedily assign the smallest sufficient cookie.
"""

from src.wasm_libs.py.io import *


def solve(g: list[int], s: list[int]) -> int:
    g.sort()
    s.sort()
    child = cookie = 0
    while child < len(g) and cookie < len(s):
        if s[cookie] >= g[child]:
            child += 1
        cookie += 1
    return child


if __name__ == "__main__":
    g = read_ints()
    s = read_ints()
    result = solve(g, s)
    write_int(result)
