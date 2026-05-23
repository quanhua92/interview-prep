"""
P380: Insert Delete GetRandom O(1) [PREMIUM] (Medium)
https://leetcode.com/problems/insert-delete-getrandom-o1/
Topics: Array, Hash Table, Math, Design, Randomized

Implement the RandomizedSet class:
You must implement the functions of the class such that each function works in average O(1) time complexity.
Example 1:
    Input
Example 1:
    ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
    [[], [1], [2], [2], [], [1], [2], []]
    Output
    [null, true, false, true, 2, true, false, 2]

    Explanation
    RandomizedSet randomizedSet = new RandomizedSet();
    randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
    randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
    randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
    randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
    randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
    randomizedSet.insert(2); // 2 was already in the set, so return false.
    randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.

Constraints:
    - -231 <= val <= 231 - 1
    - At most 2 * 105 calls will be made to insert, remove, and getRandom.
    - There will be at least one element in the data structure when getRandom is called.

Template (python3):
    class RandomizedSet:

        def __init__(self):


        def insert(self, val: int) -> bool:


        def remove(self, val: int) -> bool:


        def getRandom(self) -> int:



    # Your RandomizedSet object will be instantiated and called as such:
    # obj = RandomizedSet()
    # param_1 = obj.insert(val)
    # param_2 = obj.remove(val)
    # param_3 = obj.getRandom()
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "380. Insert Delete GetRandom O(1)"
    test_cases = [
        TestCase(
            input={
                "ops": ["insert", "remove", "insert", "remove", "insert", "getRandom"],
                "args": [[1], [2], [2], [1], [2], []],
            },
            expected=[True, False, True, True, False, 2],
            label="example 1",
        ),
        TestCase(
            input={
                "ops": ["insert", "insert", "insert", "getRandom", "remove", "getRandom"],
                "args": [[10], [20], [30], [], [20], []],
            },
            expected=[True, True, True, 30, True, 10],
            label="insert multiple then remove middle",
        ),
        TestCase(
            input={
                "ops": ["insert", "getRandom", "remove", "insert", "getRandom"],
                "args": [[5], [], [5], [5], []],
            },
            expected=[True, 5, True, True, 5],
            label="single element cycle",
        ),
        TestCase(
            input={
                "ops": ["insert", "insert", "remove", "remove", "insert", "getRandom"],
                "args": [[1], [2], [1], [2], [3], []],
            },
            expected=[True, True, True, True, True, 3],
            label="remove all then insert new",
        ),
    ]

    def solve(self, ops: list[str], args: list) -> list:
        import random

        random.seed(42)
        vals: list[int] = []
        idx_map: dict[int, int] = {}

        results = []
        for op, arg in zip(ops, args):
            if op == "insert":
                val = arg[0]
                if val in idx_map:
                    results.append(False)
                else:
                    idx_map[val] = len(vals)
                    vals.append(val)
                    results.append(True)
            elif op == "remove":
                val = arg[0]
                if val not in idx_map:
                    results.append(False)
                else:
                    idx = idx_map[val]
                    last = vals[-1]
                    vals[idx] = last
                    idx_map[last] = idx
                    vals.pop()
                    del idx_map[val]
                    results.append(True)
            elif op == "getRandom":
                results.append(random.choice(vals))
        return results


if __name__ == "__main__":
    Solution().run()
