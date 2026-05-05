"""Tests for tier3_advanced/modified_binary_search"""
import sys
sys.path.insert(0, ".")
from tier3_advanced.modified_binary_search.solutions.p033_search_rotated import Solution as P033
from tier3_advanced.modified_binary_search.solutions.p875_koko_bananas import Solution as P875

class TestP033SearchRotated:
    def test_example1(self): assert P033().solve([4,5,6,7,0,1,2], 0) == 4
    def test_example2(self): assert P033().solve([4,5,6,7,0,1,2], 3) == -1
    def test_single(self): assert P033().solve([1], 0) == -1

class TestP875KokoBananas:
    def test_example1(self): assert P875().solve([3,6,7,11], 8) == 4
    def test_example2(self): assert P875().solve([30,11,23,4,20], 5) == 30
    def test_example3(self): assert P875().solve([30,11,23,4,20], 6) == 23
