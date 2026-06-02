"""
P997: Find the Town Judge (Easy)
https://leetcode.com/problems/find-the-town-judge/
Topics: Array, Hash Table, Graph

In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.
If the town judge exists, then:
You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi. If a trust relationship does not exist in trust array, then such a trust relationship does not exist.
Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.

Example 1:
    Input: n = 2, trust = [[1,2]]
    Output: 2

Example 2:
    Input: n = 3, trust = [[1,3],[2,3]]
    Output: 3

Example 3:
    Input: n = 3, trust = [[1,3],[2,3],[3,1]]
    Output: -1

Constraints:
    - 1 <= n <= 1000
    - 0 <= trust.length <= 10^4
    - trust[i].length == 2
    - All the pairs of trust are unique.
    - ai != bi
    - 1 <= ai, bi <= n

Template (python3):
    class Solution:
        def findJudge(self, n: int, trust: List[List[int]]) -> int:

Hint: Trust score array: for each [a,b], scores[a]-=1 and scores[b]+=1. Judge has score n-1.
"""

from src.wasm_libs.py.io import *


def solve(n: int, trust: list[list[int]]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    header = read_ints()
    n, pair_count = header[0], header[1]
    trust = [read_ints() for _ in range(pair_count)]
    result = solve(n, trust)
    write_int(result)
