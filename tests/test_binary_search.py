"""Tests for tier2_intermediate/binary_search"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.binary_search.solutions.p704_binary_search import Solution as P704
from tier2_intermediate.binary_search.solutions.p153_find_min_rotated import Solution as P153

class TestP704BinarySearch:
    def test_example1(self): assert P704().solve([-1,0,3,5,9,12], 9) == 4
    def test_example2(self): assert P704().solve([-1,0,3,5,9,12], 2) == -1
    def test_single(self): assert P704().solve([5], 5) == 0

class TestP153FindMinRotated:
    def test_example1(self): assert P153().solve([3,4,5,1,2]) == 1
    def test_example2(self): assert P153().solve([4,5,6,7,0,1,2]) == 0
    def test_single(self): assert P153().solve([1]) == 1
