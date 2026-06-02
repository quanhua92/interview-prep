"""
P134: Gas Station (Medium)
https://leetcode.com/problems/gas-station/
Topics: Array, Greedy

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.

Constraints:
    - n == gas.length == cost.length
    - 1 <= n <= 10^5
    - 0 <= gas[i], cost[i] <= 10^4

Hint: Track total_surplus and current_surplus. If current_surplus < 0, reset start to next station.
"""

from src.wasm_libs.py.io import *


def solve(gas: list[int], cost: list[int]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    gas = read_ints()
    cost = read_ints()
    result = solve(gas, cost)
    write_int(result)
