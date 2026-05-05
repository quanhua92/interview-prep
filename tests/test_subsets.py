"""Tests for tier3_advanced/subsets"""
import sys
sys.path.insert(0, ".")
from tier3_advanced.subsets.solutions.p046_permutations import Solution as P046
from tier3_advanced.subsets.solutions.p090_subsets_ii import Solution as P090

class TestP046Permutations:
    def test_example1(self):
        result = P046().solve([1,2,3])
        assert len(result) == 6
        assert sorted(result) == [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    def test_example2(self):
        result = P046().solve([0,1])
        assert sorted(result) == [[0,1],[1,0]]
    def test_single(self): assert P046().solve([1]) == [[1]]

class TestP090SubsetsII:
    def test_example1(self):
        result = P090().solve([1,2,2])
        assert sorted([sorted(x) for x in result]) == [[],[1],[1,2],[1,2,2],[2],[2,2]]
    def test_example2(self):
        result = P090().solve([0])
        assert sorted(result) == [[], [0]]
