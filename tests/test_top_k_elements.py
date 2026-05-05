"""Tests for tier2_intermediate/top_k_elements"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.top_k_elements.solutions.p215_kth_largest import Solution as P215
from tier2_intermediate.top_k_elements.solutions.p347_top_k_frequent import Solution as P347

class TestP215KthLargest:
    def test_example1(self): assert P215().solve([3,2,1,5,6,4], 2) == 5
    def test_example2(self): assert P215().solve([3,2,3,1,2,4,5,5,6], 4) == 4
    def test_single(self): assert P215().solve([1], 1) == 1

class TestP347TopKFrequent:
    def test_example1(self):
        result = P347().solve([1,1,1,2,2,3], 2)
        assert sorted(result) == [1, 2]
    def test_example2(self): assert P347().solve([1], 1) == [1]
