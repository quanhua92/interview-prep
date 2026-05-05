"""Tests for tier1_foundation/two_pointers"""
import sys
sys.path.insert(0, ".")
from tier1_foundation.two_pointers.solutions.p167_two_sum import Solution as P167
from tier1_foundation.two_pointers.solutions.p011_container_water import Solution as P011
from tier1_foundation.two_pointers.solutions.p015_three_sum import Solution as P015

class TestP167TwoSum:
    def test_example1(self): assert P167().solve([2,7,11,15], 9) == [1, 2]
    def test_example2(self): assert P167().solve([2,3,4], 6) == [1, 3]
    def test_example3(self): assert P167().solve([-1,0], -1) == [1, 2]

class TestP011ContainerWater:
    def test_example1(self): assert P011().solve([1,8,6,2,5,4,8,3,7]) == 49
    def test_example2(self): assert P011().solve([1,1]) == 1
    def test_symmetric(self): assert P011().solve([4,3,2,1,4]) == 16

class TestP015ThreeSum:
    def test_example1(self):
        result = P015().solve([-1,0,1,2,-1,-4])
        assert sorted([sorted(t) for t in result]) == [[-1,-1,2],[-1,0,1]]
    def test_example2(self): assert P015().solve([0,1,1]) == []
    def test_all_zeros(self): assert P015().solve([0,0,0]) == [[0,0,0]]
    def test_empty(self): assert P015().solve([]) == []
