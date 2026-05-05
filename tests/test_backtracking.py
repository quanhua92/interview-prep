"""Tests for tier3_advanced/backtracking"""
import sys
sys.path.insert(0, ".")
from tier3_advanced.backtracking.solutions.p078_subsets import Solution as P078
from tier3_advanced.backtracking.solutions.p039_combination_sum import Solution as P039

class TestP078Subsets:
    def test_example1(self):
        result = P078().solve([1,2,3])
        assert len(result) == 8
        assert sorted([sorted(x) for x in result]) == [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
    def test_example2(self):
        result = P078().solve([0])
        assert sorted(result) == [[], [0]]

class TestP039CombinationSum:
    def test_example1(self):
        result = P039().solve([2,3,6,7], 7)
        assert sorted(result) == [[2,2,3],[7]]
    def test_example2(self):
        result = P039().solve([2,3,5], 8)
        assert sorted(result) == [[2,2,2,2],[2,3,3],[3,5]]
    def test_no_solution(self): assert P039().solve([2], 1) == []
