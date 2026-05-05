"""Tests for tier3_advanced/cyclic_sort"""
import sys
sys.path.insert(0, ".")
from tier3_advanced.cyclic_sort.solutions.p442_find_duplicates import Solution as P442
from tier3_advanced.cyclic_sort.solutions.p268_missing_number import Solution as P268
from tier3_advanced.cyclic_sort.solutions.p448_find_disappeared import Solution as P448

class TestP442FindDuplicates:
    def test_example1(self):
        assert sorted(P442().solve([4,3,2,7,8,2,3,1])) == [2, 3]
    def test_example2(self): assert P442().solve([1,1,2]) == [1]
    def test_single(self): assert P442().solve([1]) == []

class TestP268MissingNumber:
    def test_example1(self): assert P268().solve([3,0,1]) == 2
    def test_example2(self): assert P268().solve([0,1]) == 2
    def test_example3(self): assert P268().solve([9,6,4,2,3,5,7,0,1]) == 8

class TestP448FindDisappeared:
    def test_example1(self):
        assert sorted(P448().solve([4,3,2,7,8,2,3,1])) == [5, 6]
    def test_example2(self):
        assert P448().solve([1,1]) == [2]
    def test_example3(self):
        assert P448().solve([2,2]) == [1]
